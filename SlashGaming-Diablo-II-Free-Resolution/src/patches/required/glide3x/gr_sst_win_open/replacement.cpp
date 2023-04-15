/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2023  Mir Drualga
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

#include <stddef.h>

#include <tuple>

#include <mdc/std/stdint.h>
#include <sgd2mapi.hpp>

#include "../../../../helper/game_resolution.hpp"
#include "../../../../helper/glide3x_version.hpp"

namespace sgd2fr::patches {
namespace {

using ::mapi::GameAddress;
using ::sgd2fr::Glide3xVersion;
using ::sgd2fr::glide3x_version::GetRunning;

static int32_t* GetHeightPtr() {
  ptrdiff_t offset;
  Glide3xVersion running_glide3x_version = GetRunning();
  switch (running_glide3x_version) {
    case Glide3xVersion::kSven1_4_4_21: {
      offset = 0x1C82C;
      break;
    }

    case Glide3xVersion::kSven1_4_6_1: {
      offset = 0x1C830;
      break;
    }

    case Glide3xVersion::kSven1_4_8_3: {
      offset = 0x1D830;
      break;
    }

    case Glide3xVersion::kNGlide3_10_0_658: {
      offset = 0x169F04;
      break;
    }
  }

  return *reinterpret_cast<int32_t**>(
      GameAddress::FromOffset(L"glide3x.dll", offset).raw_address());
}

static int32_t* GetWidthPtr() {
  ptrdiff_t offset;
  Glide3xVersion running_glide3x_version = GetRunning();
  switch (running_glide3x_version) {
    case Glide3xVersion::kSven1_4_4_21: {
      offset = 0x1C9A0;
      break;
    }

    case Glide3xVersion::kSven1_4_6_1: {
      offset = 0x1C870;
      break;
    }

    case Glide3xVersion::kSven1_4_8_3: {
      offset = 0x1D870;
      break;
    }

    case Glide3xVersion::kNGlide3_10_0_658: {
      offset = 0x169DA4;
      break;
    }
  }

  return *reinterpret_cast<int32_t**>(
      GameAddress::FromOffset(L"glide3x.dll", offset).raw_address());
}

}  // namespace

void __cdecl Sgd2fr_Glide3x_SetWindowWidthAndHeight(
    std::uint32_t glide_resolution_mode,
    std::int32_t* width,
    std::int32_t* height) {
  int32_t* width_ptr = GetWidthPtr();
  int32_t* height_ptr = GetHeightPtr();

  std::tuple<int, int> resolution =
      GetIngameResolutionFromId(glide_resolution_mode - 0x1000);

  std::tie(*width_ptr, *height_ptr) = resolution;
}

}  // namespace sgd2fr::patches
