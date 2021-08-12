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

#include "glide3x_gr_sst_win_open.hpp"

#include <sgd2mapi.hpp>

#include "../../../helper/game_resolution.hpp"
#include "../../../helper/glide3x_version.hpp"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_Glide3x_SetWindowWidthAndHeight(
    std::uint32_t glide_resolution_mode,
    std::int32_t* width,
    std::int32_t* height
) {
  std::tuple<int, int> resolution = GetIngameResolutionFromId(
      glide_resolution_mode - (0x1000 - 3)
  );

  Glide3xVersion running_glide3x_version = glide3x_version::GetRunning();
  switch (running_glide3x_version) {
    case Glide3xVersion::kSven1_4_4_21: {
      width = *reinterpret_cast<std::int32_t**>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x1C9A0).raw_address()
      );
      height = *reinterpret_cast<std::int32_t**>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x1C82C).raw_address()
      );

      break;
    }

    case Glide3xVersion::kSven1_4_6_1: {
      width = *reinterpret_cast<std::int32_t**>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x1C870).raw_address()
      );
      height = *reinterpret_cast<std::int32_t**>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x1C830).raw_address()
      );

      break;
    }

    case Glide3xVersion::kSven1_4_8_3: {
      width = *reinterpret_cast<std::int32_t**>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x1D870).raw_address()
      );
      height = *reinterpret_cast<std::int32_t**>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x1D830).raw_address()
      );

      break;
    }

    case Glide3xVersion::kNGlide3_10_0_658: {
      width = reinterpret_cast<std::int32_t*>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x169DA4).raw_address()
      );
      height = reinterpret_cast<std::int32_t*>(
          ::mapi::GameAddress::FromOffset(L"glide3x.dll", 0x169F04).raw_address()
      );

      break;
    }
  }

  *width = std::get<0>(resolution);
  *height = std::get<1>(resolution);
}

} // namespace sgd2fr::patches
