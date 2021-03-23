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

#include "d2client_set_general_display_width_and_height.hpp"

#include <sgd2mapi.hpp>

#include "../../../helper/game_resolution.hpp"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_D2Client_SetGeneralDisplayWidthAndHeight(
    std::size_t resolution_mode
) {
  std::tuple<int, int> resolution = GetIngameResolutionFromId(
      resolution_mode
  );

  int width = std::get<0>(resolution);
  int height = std::get<1>(resolution);

  d2::d2client::SetGeneralDisplayWidth(width);
  d2::d2client::SetGeneralDisplayHeight(height);

  // Workaround to prevent inventory arrangement from "transferring"
  // between SP and MP resolutions.
  unsigned int inventory_arrange_mode;

  if (::d2::d2client::GetGameType() == ::d2::ClientGameType::kBattleNetJoin) {
    inventory_arrange_mode = (resolution_mode == 0)
        ? ::std::numeric_limits<::std::size_t>::max()
        : ::std::numeric_limits<::std::size_t>::max() - (resolution_mode + 1);
  } else {
    inventory_arrange_mode = (resolution_mode == 0)
        ? 0
        : resolution_mode - 1;
  }

  d2::d2client::SetInventoryArrangeMode(inventory_arrange_mode);
}

} // namespace sgd2fr::patches
