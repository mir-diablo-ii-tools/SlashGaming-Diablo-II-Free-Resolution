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

#include "d2glide_set_display_width_and_height.hpp"

#include <sgd2mapi.hpp>

#include "../../../helper/game_resolution.hpp"
#include "../../../helper/glide3x_d2dx.hpp"
#include "../../../helper/glide3x_version.hpp"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_D2Glide_SetDisplayWidthAndHeight(
    std::uint32_t resolution_mode,
    std::int32_t* width,
    std::int32_t* height,
    std::uint32_t* glide_res_id
) {
  std::tuple<int, int> resolution = GetIngameResolutionFromId(resolution_mode);

  *width = std::get<0>(resolution);
  *height = std::get<1>(resolution);

  ::d2::d2glide::SetDisplayWidth(*width);
  ::d2::d2glide::SetDisplayHeight(*height);

  switch (resolution_mode) {
    case 0: {
      *glide_res_id = 7;
      break;
    }

    case 1:
    case 2: {
      *glide_res_id = 8;
      break;
    }

    default: {
      *glide_res_id = 0x1000 + (resolution_mode - 3);
      break;
    }
  }

  if (glide3x_version::GetRunning() == Glide3xVersion::kD2dx) {
    d2dx_glide::SetCustomResolution(*width, *height);
  }
}

} // namespace sgd2fr::patches
