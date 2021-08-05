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

#include "game_resolution.hpp"

#include <string.h>

#include <array>
#include <algorithm>
#include <mutex>
#include <set>
#include <utility>

#include <mdc/error/exit_on_error.hpp>
#include <mdc/wchar_t/filew.h>
#include <sgd2mapi.hpp>
#include "../config.h"
#include "../compile_time_switch.hpp"
#include "../sgd2mapi_extension/sgd2mapi_extension.hpp"
#include "game_resolution_gateway_ipv4.h"

namespace sgd2fr {
namespace {

const struct IngameResolutions* SelectLocalOrOnlineResolutions(void) {
  if (D2_D2Client_GetGameType() == D2_ClientGameType_kBattleNetJoin) {
    return GatewayIpv4_GetIngameResolutions(
        D2_BNClient_GetGatewayIpV4Address()
    );
  } else {
    return &GetConfig()->ingame_resolutions;
  }
}

const std::set<GameResolution>& GetStandardResolutions() {
  static int is_init = 0;
  static std::set<GameResolution> standard_resolutions;

  if (is_init) {
    return standard_resolutions;
  }

  DEVMODEW dev_mode;
  dev_mode.dmSize = sizeof(dev_mode);

  for (DWORD i = 0; EnumDisplaySettingsW(nullptr, i, &dev_mode); i += 1) {
    standard_resolutions.insert(
        {
            static_cast<int>(dev_mode.dmPelsWidth),
            static_cast<int>(dev_mode.dmPelsHeight)
        }
    );
  }

  is_init = 1;

  return standard_resolutions;
}

const IngameResolutions& GetNonCrashingIngameResolutions(void) {
  static int is_init = 0;
  static ::d2::ClientGameType selected_game_type =
      ::d2::d2client::GetGameType();
  static IngameResolutions non_crashing_ingame_resolutions = { 0 };
  static ::std::string gateway_ipv4_address;

  if (selected_game_type != ::d2::d2client::GetGameType()
      || gateway_ipv4_address != ::d2::bnclient::GetGatewayIpV4Address()) {
    is_init = 0;
  }

  if (is_init) {
    return non_crashing_ingame_resolutions;
  }

  ::d2::VideoMode current_video_mode = ::d2::d2gfx::GetVideoMode();
  const struct IngameResolutions* selected_ingame_resolutions =
      SelectLocalOrOnlineResolutions();

  if (current_video_mode == ::d2::VideoMode::kDirect3D
      || (current_video_mode == ::d2::VideoMode::kDirectDraw
          && ::d2::ddraw_library_version::GetRunning()
              != ::d2::ddraw_library_version::kCnC)) {
    if (non_crashing_ingame_resolutions.resolutions != NULL) {
      delete[] non_crashing_ingame_resolutions.resolutions;
    }

    non_crashing_ingame_resolutions.resolutions =
        new GameResolution[selected_ingame_resolutions->count];
    non_crashing_ingame_resolutions.count = 0;

    for (size_t i = 0; i < selected_ingame_resolutions->count; i += 1) {
      const GameResolution* resolution =
          &selected_ingame_resolutions->resolutions[i];
      if (IsStandardResolution(*resolution)) {
        non_crashing_ingame_resolutions.resolutions[
            non_crashing_ingame_resolutions.count
        ] = *resolution;

        non_crashing_ingame_resolutions.count += 1;
      }
    }
  } else {
    non_crashing_ingame_resolutions = *selected_ingame_resolutions;
  }

  selected_game_type = ::d2::d2client::GetGameType();
  gateway_ipv4_address = ::d2::bnclient::GetGatewayIpV4Address();

  is_init = 1;

  return non_crashing_ingame_resolutions;
}

} // namespace

size_t GetIngameResolutionMode() {
  return GetConfig()->ingame_resolution_mode;
}

void SetIngameResolutionMode(size_t resolution_mode) {
  GetConfig()->ingame_resolution_mode = resolution_mode;
  WriteConfig();
}

std::size_t GetMinConfigResolutionId() {
  return GetNonCrashingIngameResolutions().resolutions[0]
      == GameResolution_k640x480
          ? 0
          : 1;
}

std::size_t GetMaxConfigResolutionId() {
  return GetNumIngameResolutions() + GetMinConfigResolutionId();
}

std::size_t GetMinIngameResolutionId() {
  return GetNonCrashingIngameResolutions().resolutions[0]
      == GameResolution_k640x480
          ? 0
          : 2;
}

std::size_t GetMaxIngameResolutionId() {
  return GetNumIngameResolutions() + GetMinIngameResolutionId();
}

std::size_t GetNumIngameResolutions() {
  return GetNonCrashingIngameResolutions().count;
}

GameResolution GetIngameResolutionFromId(std::size_t id) {
  if (id == 0) {
    return GameResolution_k640x480;
  } else if (id == 1) {
    return GetConfig()->main_menu_resolution;
  }

  const auto& ingame_resolutions = GetNonCrashingIngameResolutions();

  std::size_t ingame_resolution_index = (GetMinIngameResolutionId() == 0)
      ? id - 1
      : id - 2;

  return ingame_resolutions.resolutions[ingame_resolution_index];
}

bool IsStandardResolution(const GameResolution& width_and_height) {
  return GetStandardResolutions().contains(width_and_height);
}

GameResolution GetVideoModeDisplayResolution() {
  ::d2::VideoMode running_video_mode = ::d2::d2gfx::GetVideoMode();

  switch (running_video_mode) {
    case ::d2::VideoMode::kGdi: {
      return {
          ::d2::d2gdi::GetBitBlockWidth(),
          ::d2::d2gdi::GetBitBlockHeight()
      };
    }

    case ::d2::VideoMode::kDirectDraw: {
      return {
          ::d2::d2ddraw::GetDisplayWidth(),
          ::d2::d2ddraw::GetDisplayHeight()
      };
    }

    case ::d2::VideoMode::kGlide: {
      return {
          ::d2::d2glide::GetDisplayWidth(),
          ::d2::d2glide::GetDisplayHeight()
      };
    }

    case ::d2::VideoMode::kDirect3D: {
      return {
          ::d2::d2direct3d::GetDisplayWidth(),
          ::d2::d2direct3d::GetDisplayHeight()
      };
    }

    default: {
      ::mdc::error::ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          static_cast<int>(running_video_mode)
      );

      return { 0, 0 };
    }
  }
}

unsigned int GetSourceInventoryArrangeMode() {
  static constexpr unsigned int kDefaultSourceInventoryArrangeMode =
      (kIsSourceInventoryArrange800)
          ? 1
          : 0;

  unsigned int resolution_mode = ::d2::d2gfx::GetResolutionMode();

  GameResolution current_resolution = GetIngameResolutionFromId(
      resolution_mode
  );

  if (current_resolution == GameResolution_k640x480) {
    return 0;
  } else if (current_resolution == GameResolution_k800x600) {
    return 1;
  } else {
    return kDefaultSourceInventoryArrangeMode;
  }
}

const GameResolution& GetSourceInventoryArrangeResolution() {
  unsigned int resolution_mode = ::d2::d2gfx::GetResolutionMode();

  GameResolution current_resolution = GetIngameResolutionFromId(
      resolution_mode
  );

  if (current_resolution == GameResolution_k640x480) {
    return GameResolution_k640x480;
  } else if (current_resolution == GameResolution_k800x600) {
    return GameResolution_k800x600;
  }

  if constexpr (kIsSourceInventoryArrange800) {
    return GameResolution_k800x600;
  } else {
    return GameResolution_k640x480;
  }
}

} // namespace sgd2fr
