/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2021  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Free Resolution.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with Diablo II (or a modified version of that game and its
 *  libraries), containing parts covered by the terms of Blizzard End User
 *  License Agreement, the licensors of this Program grant you additional
 *  permission to convey the resulting work. This additional permission is
 *  also extended to any combination of expansions, mods, and remasters of
 *  the game.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
 *  Glide, OpenGL, or Rave wrapper (or modified versions of those
 *  libraries), containing parts not covered by a compatible license, the
 *  licensors of this Program grant you additional permission to convey the
 *  resulting work.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any library (or a modified version of that library) that links
 *  to Diablo II (or a modified version of that game and its libraries),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "game_resolution_global.h"

#include <string.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/wchar_t/filew.h>
#include <sgd2mapi.h>
#include "../compile_time_switch.h"
#include "../sgd2mapi_extension/sgd2mapi_extension.h"
#include "../user_config.h"
#include "game_resolution_gateway_ipv4.h"

#ifndef COMPILE_TIME_IS_SOURCE_INVENTORY_ARRANGE_800
#error COMPILE_TIME_IS_SOURCE_INVENTORY_ARRANGE_800 is not defined.
#endif /* COMPILE_TIME_IS_SOURCE_INVENTORY_ARRANGE_800 */

static const struct IngameResolutions*
SelectUserConfigOrGatewayResolutions(void) {
  if (D2_D2Client_GetGameType() == D2_ClientGameType_kBattleNetJoin) {
    return GatewayIpv4_GetIngameResolutions(
        D2_BNClient_GetGatewayIpV4Address()
    );
  } else {
    return &UserConfig_Get()->ingame_resolutions;
  }
}

static int IsNeedNonCrashingResolutions(void) {
  static int is_init = 0;
  static int is_resolutions_filtered;

  if (is_init) {
    return is_resolutions_filtered;
  }

  switch (D2_D2GFX_GetVideoMode()) {
    case D2_VideoMode_kDirectDraw: {
      is_resolutions_filtered = D2_DDrawLibraryVersion_GetRunning()
          == D2_DDrawLibraryVersion_kCnC;
      break;
    }

    case D2_VideoMode_kDirect3D: {
      is_resolutions_filtered = 1;
      break;
    }

    default: {
      is_resolutions_filtered = 0;
      break;
    }
  }

  is_init = 1;
  return is_resolutions_filtered;
}

static const struct IngameResolutions* GetNonCrashingResolutions(void) {
  enum {
    kIpV4Capacity = sizeof("000.000.000.000") * sizeof(char),
  };

  static int is_init = 0;
  static struct IngameResolutions non_crashing_resolutions = {
      0,
      NULL
  };

  static enum D2_ClientGameType known_client_game_type = -1;
  static char known_gateway_ipv4_address[kIpV4Capacity] = "";

  size_t i;

  enum D2_ClientGameType client_game_type;
  const char* gateway_ipv4_address;
  size_t gateway_ipv4_address_length;

  const struct IngameResolutions* selected_resolutions;

  client_game_type = D2_D2Client_GetGameType();
  gateway_ipv4_address = D2_BNClient_GetGatewayIpV4Address();

  if (known_client_game_type != client_game_type
      || strcmp(known_gateway_ipv4_address, gateway_ipv4_address) != 0) {
    is_init = 0;
  }

  if (is_init) {
    return &non_crashing_resolutions;
  }

  selected_resolutions = SelectUserConfigOrGatewayResolutions();

  if (IsNeedNonCrashingResolutions()) {
    Mdc_free(non_crashing_resolutions.resolutions);

    non_crashing_resolutions.resolutions = Mdc_malloc(
        selected_resolutions->count
            * sizeof(non_crashing_resolutions.resolutions[0])
    );

    if (non_crashing_resolutions.resolutions == NULL) {
      Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
      goto return_bad;
    }

    non_crashing_resolutions.count = 0;

    for (i = 0; i < selected_resolutions->count; i += 1) {
      int is_standard_resolution;

      is_standard_resolution = GameResolution_IsStandardResolution(
          &selected_resolutions->resolutions[i]
      );

      if (!is_standard_resolution) {
        continue;
      }

      non_crashing_resolutions.resolutions[non_crashing_resolutions.count] =
          selected_resolutions->resolutions[i];
      non_crashing_resolutions.count += 1;
    }
  } else {
    non_crashing_resolutions = *selected_resolutions;
  }

  known_client_game_type = client_game_type;
  strcpy(known_gateway_ipv4_address, gateway_ipv4_address);

  is_init = 1;

  return &non_crashing_resolutions;

return_bad:
  return NULL;
}

/**
 * External
 */

size_t Global_GetIngameResolutionMode(void) {
  return UserConfig_Get()->ingame_resolution_mode;
}

void Global_SetIngameResolutionMode(size_t mode) {
  UserConfig_Get()->ingame_resolution_mode = mode;
  UserConfig_Write();
}

size_t Global_GetMinConfigResolutionMode(void) {
  const struct IngameResolutions* non_crashing_resolutions;
  int compare_result;

  non_crashing_resolutions = GetNonCrashingResolutions();
  compare_result = GameResolution_Compare(
      &non_crashing_resolutions->resolutions[0],
      &GameResolution_k640x480
  );

  return (compare_result == 0)
      ? 0
      : 1;
}

size_t Global_GetMaxConfigResolutionMode(void) {
  return Global_GetMinConfigResolutionMode()
      + Global_GetNumIngameResolutions();
}

size_t Global_GetMinIngameResolutionMode(void) {
  const struct IngameResolutions* non_crashing_resolutions;
  int compare_result;

  non_crashing_resolutions = GetNonCrashingResolutions();
  compare_result = GameResolution_Compare(
      &non_crashing_resolutions->resolutions[0],
      &GameResolution_k640x480
  );

  return (compare_result == 0)
      ? 0
      : 2;
}

size_t Global_GetMaxIngameResolutionMode(void) {
  return Global_GetMinIngameResolutionMode()
      + Global_GetNumIngameResolutions();
}

size_t Global_GetNumIngameResolutions(void) {
  return GetNonCrashingResolutions()->count;
}

void Global_GetIngameResolution(
    struct GameResolution* resolution,
    size_t mode
) {
  const struct IngameResolutions* non_crashing_resolutions;
  size_t non_crashing_resolution_mode;

  if (mode == 0) {
    *resolution = GameResolution_k640x480;
    return;
  } else if (mode == 1) {
    *resolution = UserConfig_Get()->main_menu_resolution;
    return;
  }

  non_crashing_resolutions = GetNonCrashingResolutions();
  non_crashing_resolution_mode = (Global_GetMinIngameResolutionMode() == 0)
      ? mode - 1
      : mode - 2;

  *resolution =
      non_crashing_resolutions->resolutions[non_crashing_resolution_mode];
}

void Global_GetVideoModeDisplayResolution(
    struct GameResolution* resolution
) {
  enum D2_VideoMode running_video_mode;

  running_video_mode = D2_D2GFX_GetVideoMode();

  switch (running_video_mode) {
    case D2_VideoMode_kGdi: {
      resolution->width = D2_D2GDI_GetBitBlockWidth();
      resolution->height = D2_D2GDI_GetBitBlockHeight();
      return;
    }

    case D2_VideoMode_kDirectDraw: {
      resolution->width = D2_D2DDraw_GetDisplayWidth();
      resolution->height = D2_D2DDraw_GetDisplayHeight();
      return;
    }

    case D2_VideoMode_kGlide: {
      resolution->width = D2_D2Glide_GetDisplayWidth();
      resolution->height = D2_D2Glide_GetDisplayHeight();
      return;
    }

    case D2_VideoMode_kDirect3D: {
      resolution->width = D2_D2Direct3D_GetDisplayWidth();
      resolution->height = D2_D2Direct3D_GetDisplayHeight();
      return;
    }

    default: {
      Mdc_Error_ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          running_video_mode
      );

      goto return_bad;
    }
  }

return_bad:
  return;
}

unsigned int Global_GetSourceInventoryArrangeMode(void) {
  static const unsigned int kDefaultSourceInventoryArrangeMode =
      COMPILE_TIME_IS_SOURCE_INVENTORY_ARRANGE_800
          ? 1
          : 0;

  unsigned int resolution_mode;
  struct GameResolution current_resolution;
  int compare_result;

  resolution_mode = D2_D2GFX_GetResolutionMode();
  Global_GetIngameResolution(&current_resolution, resolution_mode);

  compare_result = GameResolution_Compare(
      &current_resolution,
      &GameResolution_k640x480
  );

  if (compare_result == 0) {
    return 0;
  }

  compare_result = GameResolution_Compare(
      &current_resolution,
      &GameResolution_k800x600
  );

  if (compare_result == 0) {
    return 1;
  }

  return kDefaultSourceInventoryArrangeMode;
}

const struct GameResolution*
Global_GetSourceInventoryArrangeResolution(void) {
  unsigned int resolution_mode;
  struct GameResolution current_resolution;
  int compare_result;

  resolution_mode = D2_D2GFX_GetResolutionMode();
  Global_GetIngameResolution(&current_resolution, resolution_mode);

  compare_result = GameResolution_Compare(
      &current_resolution,
      &GameResolution_k640x480
  );

  if (compare_result == 0) {
    return &GameResolution_k640x480;
  }

  compare_result = GameResolution_Compare(
      &current_resolution,
      &GameResolution_k800x600
  );

  if (compare_result == 0) {
    return &GameResolution_k800x600;
  }

#if COMPILE_TIME_IS_SOURCE_INVENTORY_ARRANGE_800
  return &GameResolution_k800x600;
#else
  return &GameResolution_k640x480;
#endif /* COMPILE_TIME_IS_SOURCE_INVENTORY_ARRANGE_800 */
}
