/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2022  Mir Drualga
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

#include "d2client_draw_screens.hpp"

#include <stddef.h>

#include <mdc/std/stdint.h>
#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.hpp>
#include <sgd2mapi.hpp>

namespace d2 {
namespace d2client {
namespace {

static ::std::intptr_t GetGameAddress() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return ::mapi::GameAddress::FromOffset(
          ::d2::DefaultLibrary::kD2Client,
          0x35750
      ).raw_address();

      break;
    }

    case ::d2::GameVersion::k1_13C: {
      return ::mapi::GameAddress::FromOffset(
          ::d2::DefaultLibrary::kD2Client,
          0x5C5C0
      ).raw_address();
    }

    case ::d2::GameVersion::k1_13D: {
      return ::mapi::GameAddress::FromOffset(
          ::d2::DefaultLibrary::kD2Client,
          0x8A970
      ).raw_address();
    }

    case ::d2::GameVersion::kLod1_14C: {
      return ::mapi::GameAddress::FromOffset(
          ::d2::DefaultLibrary::kD2Client,
          0x8F800
      ).raw_address();
    }

    case ::d2::GameVersion::kLod1_14D: {
      return ::mapi::GameAddress::FromOffset(
          ::d2::DefaultLibrary::kD2Client,
          0x93340
      ).raw_address();
    }

    default: {
      ::mdc::error::ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          static_cast<int>(running_game_version)
      );

      return NULL;
    }
  }
}

using FuncType = void (*)();

} // namespace

void DrawScreens() {
  static intptr_t game_address = GetGameAddress();

  reinterpret_cast<FuncType>(game_address)();
}

} // namespace d2client
} // namespace d2
