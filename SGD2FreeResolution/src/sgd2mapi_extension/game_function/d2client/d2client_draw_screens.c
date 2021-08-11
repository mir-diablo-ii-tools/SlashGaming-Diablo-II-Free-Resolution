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

#include "d2client_draw_screens.h"

#include <mdc/error/exit_on_error.h>
#include <mdc/wchar_t/filew.h>
#include <sgd2mapi.h>

typedef void (*FuncType)(void);

static struct Mapi_GameAddress game_address;

static void InitGameAddress(void) {
  static int is_init = 0;

  enum D2_GameVersion running_game_version;

  if (is_init) {
    return;
  }

  running_game_version = D2_GameVersion_GetRunning();

  switch (running_game_version) {
    case D2_GameVersion_k1_09D: {
      game_address = Mapi_GameAddress_InitFromLibraryAndOffset(
          D2_DefaultLibrary_kD2Client,
          0x35750
      );

      break;
    }

    case D2_GameVersion_k1_13C: {
      game_address = Mapi_GameAddress_InitFromLibraryAndOffset(
          D2_DefaultLibrary_kD2Client,
          0x5C5C0
      );

      break;
    }

    case D2_GameVersion_k1_13D: {
      game_address = Mapi_GameAddress_InitFromLibraryAndOffset(
          D2_DefaultLibrary_kD2Client,
          0x8A970
      );

      break;
    }

    case D2_GameVersion_kLod1_14C: {
      game_address = Mapi_GameAddress_InitFromLibraryAndOffset(
          D2_DefaultLibrary_kD2Client,
          0x8F800
      );

      break;
    }

    case D2_GameVersion_kLod1_14D: {
      game_address = Mapi_GameAddress_InitFromLibraryAndOffset(
          D2_DefaultLibrary_kD2Client,
          0x93340
      );

      break;
    }

    default: {
      Mdc_Error_ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          running_game_version
      );

      goto return_bad;
    }
  }

  is_init = 1;
  return;

return_bad:
  is_init = 0;
}

/**
 * External
 */

void D2_D2Client_DrawScreens(void) {
  InitGameAddress();

  ((FuncType)game_address.raw_address)();
}
