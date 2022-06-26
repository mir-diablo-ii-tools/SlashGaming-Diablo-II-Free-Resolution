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

#include "d2gdi_set_bit_block_width_and_height.hpp"

#include <sgd2mapi.hpp>

#include "../../../helper/game_resolution.hpp"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_D2GDI_GetBitBlockWidthAndHeight(
    ::std::size_t resolution_mode,
    ::std::int32_t* width,
    ::std::int32_t* height
) {
  ::std::tuple<int, int> resolution = GetIngameResolutionFromId(
      resolution_mode
  );

  *width = ::std::get<0>(resolution);
  *height = ::std::get<1>(resolution);
}

void __cdecl Sgd2fr_D2GDI_SetBitBlockWidthAndHeight(
    ::std::size_t resolution_mode
) {
  ::std::tuple<int, int> resolution = GetIngameResolutionFromId(
      resolution_mode
  );

  int bit_block_width = ::std::get<0>(resolution);
  int bit_block_height = ::std::get<1>(resolution);

  ::d2::d2gdi::SetBitBlockWidth(bit_block_width);
  ::d2::d2gdi::SetBitBlockHeight(bit_block_height);
}

} // namespace sgd2fr::patches
