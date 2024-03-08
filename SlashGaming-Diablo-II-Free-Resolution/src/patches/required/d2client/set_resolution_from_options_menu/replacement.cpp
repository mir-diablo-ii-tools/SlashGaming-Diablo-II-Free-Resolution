/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2024  Mir Drualga
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

#include "replacement.hpp"

#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.hpp>
#include <sgd2mapi.hpp>
#include "../../../../config.hpp"
#include "../../../../helper/game_resolution.hpp"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_D2Client_SetResolutionFromOptionsMenu(
    void* settings,
    std::uint32_t reg_resolution_mode,
    std::uint32_t* reg_resolution_mode_out
) {
  void* resolution_settings_address;

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();
  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      resolution_settings_address = reinterpret_cast<void*>(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xE6468
          ).raw_address()
      );
      break;
    }

    case ::d2::GameVersion::k1_10: {
      resolution_settings_address = reinterpret_cast<void*>(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xE6028
          ).raw_address()
      );
      break;
    }

    case ::d2::GameVersion::k1_12A: {
      resolution_settings_address = reinterpret_cast<void*>(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xECAA0
          ).raw_address()
      );
      break;
    }

    case ::d2::GameVersion::k1_13C: {
      resolution_settings_address = reinterpret_cast<void*>(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xEAAB8
          ).raw_address()
      );
      break;
    }

    case ::d2::GameVersion::k1_13D: {
      resolution_settings_address = reinterpret_cast<void*>(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xE4E20
          ).raw_address()
      );
      break;
    }

    case ::d2::GameVersion::kLod1_14C: {
      resolution_settings_address = reinterpret_cast<void*>(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3197D0
          ).raw_address()
      );
      break;
    }

    case ::d2::GameVersion::kLod1_14D: {
      resolution_settings_address = reinterpret_cast<void*>(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x31B1F0
          ).raw_address()
      );
      break;
    }

    default: {
      ::mdc::error::ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          static_cast<int>(running_game_version)
      );

      return;
    }
  }

  if (settings != resolution_settings_address) {
    *reg_resolution_mode_out = 0;
    return;
  }

  std::size_t max_registry_resolution_id = GetMaxConfigResolutionId();

  if (reg_resolution_mode >= max_registry_resolution_id) {
    *reg_resolution_mode_out = GetMinConfigResolutionId();
  } else {
    *reg_resolution_mode_out = reg_resolution_mode;
  }
}

} // namespace sgd2fr::patches
