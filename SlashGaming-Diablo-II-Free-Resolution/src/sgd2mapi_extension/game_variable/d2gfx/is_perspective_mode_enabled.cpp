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

#include "is_perspective_mode_enabled.hpp"

#include <stddef.h>

#include <mdc/std/stdint.h>
#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.hpp>
#include <sgd2mapi.hpp>

namespace d2 {
namespace d2gfx {
namespace {

using ::d2::DefaultLibrary;
using ::d2::GameVersion;
using ::d2::game_version::GetRunning;
using ::mapi::GameAddress;
using ::mdc::error::ExitOnConstantMappingError;

static intptr_t GetGameAddress() {
  ptrdiff_t offset;
  GameVersion running_game_version = GetRunning();
  switch (running_game_version) {
    case GameVersion::k1_00:
    case GameVersion::k1_02:
    case GameVersion::k1_03: {
      offset = 0x19EA8;
      break;
    }

    case GameVersion::k1_04B_C:
    case GameVersion::k1_05:
    case GameVersion::k1_05B:
    case GameVersion::k1_06: {
      offset = 0xE180;
      break;
    }

    case GameVersion::k1_06B: {
      offset = 0xE190;
      break;
    }

    case GameVersion::k1_07Beta: {
      offset = 0xD180;
      break;
    }

    case GameVersion::k1_07:
    case GameVersion::k1_08:
    case GameVersion::k1_09:
    case GameVersion::k1_09B: {
      offset = 0xE190;
      break;
    }

    case GameVersion::k1_09D:
    case GameVersion::k1_10Beta:
    case GameVersion::k1_10SBeta: {
      offset = 0xE188;
      break;
    }

    case GameVersion::k1_10: {
      offset = 0xE198;
      break;
    }

    case GameVersion::k1_11: {
      offset = 0x10C94;
      break;
    }

    case GameVersion::k1_11B: {
      offset = 0x10C30;
      break;
    }

    case GameVersion::k1_12A: {
      offset = 0x10C8C;
      break;
    }

    case GameVersion::k1_13ABeta: {
      offset = 0x10CA8;
      break;
    }

    case GameVersion::k1_13C: {
      offset = 0x10BE0;
      break;
    }

    case GameVersion::k1_13D: {
      offset = 0x10BE4;
      break;
    }

    case GameVersion::kClassic1_14A:
    case GameVersion::kLod1_14A: {
      offset = 0x307598;
      break;
    }

    case GameVersion::kClassic1_14B: {
      offset = 0x328334;
      break;
    }

    case GameVersion::kLod1_14B: {
      offset = 0x32C098;
      break;
    }

    case GameVersion::kClassic1_14C: {
      offset = 0x327334;
      break;
    }

    case GameVersion::kLod1_14C: {
      offset = 0x32B098;
      break;
    }

    case GameVersion::kClassic1_14D: {
      offset = 0x329B44;
      break;
    }

    case GameVersion::kLod1_14D: {
      offset = 0x32DA48;
      break;
    }

    default: {
      ExitOnConstantMappingError(
          __FILEW__, __LINE__, static_cast<int>(running_game_version));
      return NULL;
    }
  }

  return GameAddress::FromOffset(DefaultLibrary::kD2GFX, offset)
      .raw_address();
}

}  // namespace

mapi::bool32 GetIsPerspectiveModeEnabled() {
  static mapi::bool32* is_perspective_enabled =
      reinterpret_cast<mapi::bool32*>(GetGameAddress());

  return *is_perspective_enabled;
}

void SetIsPerspectiveModeEnabled(mapi::bool32 is_perspective_mode_enabled_) {
  static mapi::bool32* is_perspective_enabled =
      reinterpret_cast<mapi::bool32*>(GetGameAddress());

  *is_perspective_enabled = is_perspective_mode_enabled_;
}

}  // namespace d2gfx
}  // namespace d2
