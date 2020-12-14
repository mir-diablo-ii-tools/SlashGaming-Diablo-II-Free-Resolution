/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2020  Mir Drualga
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

#include "d2client_draw_resolution_text.hpp"

#include <limits>
#include <string>

#include <fmt/format.h>
#include <sgd2mapi.hpp>
#include "../../../helper/game_resolution.hpp"

namespace sgd2fr::patches {

mapi::bool32 __cdecl Sgd2fr_D2Client_DrawResolutionText(
    const d2::CelFile* cel_file_base_address,
    std::int32_t offset_value,
    std::int32_t right,
    std::int32_t top
) {
  const d2::CelFile* comparing_cel_file_base_address;

  // Get the address of the cel file base.
  d2::GameVersion running_game_version_id = d2::GetRunningGameVersionId();
  switch (running_game_version_id) {
    case d2::GameVersion::k1_09D: {
      std::intptr_t raw_address = mapi::GameAddress::FromOffset(
          mapi::DefaultLibrary::kD2Client,
          0xE5F18
      ).raw_address();

      comparing_cel_file_base_address = reinterpret_cast<d2::CelFile*>(
          raw_address
      );
      break;
    }

    default: {
      // TODO (Mir Drualga): Get rid of this default case!
      comparing_cel_file_base_address = nullptr;
    }
  }

  // Determine if there needs to be a draw call or not.
  if (cel_file_base_address != comparing_cel_file_base_address) {
    return false;
  }
  
  if (offset_value != 0x154) {
    return false;
  }

  // Draw text based on the resolution mode.
  unsigned int resolution_mode = d2::d2gfx::GetResolutionMode();
  std::tuple resolution = GetIngameResolutionFromId(resolution_mode);

  std::u8string text_fmt = fmt::format(
      u8"{}x{}",
      std::get<0>(resolution),
      std::get<1>(resolution)
  );

  d2::UnicodeString_Api text_unicode = d2::UnicodeString_Api::FromUtf8String(text_fmt);

  d2::TextFont old_text_font = d2::d2win::SetTextFont(d2::TextFont::kDiabloMenu_30);

  d2::DrawTextOptions options;
  options.position_x_behavior = d2::DrawPositionXBehavior::kRight;
  options.text_color = d2::TextColor::kWhite;

  text_unicode.Draw(right, top, options);

  d2::d2win::SetTextFont(old_text_font);

  return true;
}

} // namespace sgd2fr::patches
