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

#include "d2common_get_global_inventory_grid_layout.hpp"

#include <sgd2mapi.hpp>
#include "../../../helper/game_resolution.hpp"
#include "../../../helper/position_realignment.hpp"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_D2Common_GetGlobalInventoryGridLayout(
    std::uint32_t inventory_record_index,
    std::uint32_t inventory_arrange_mode,
    d2::GridLayout* out_grid_layout
) {
  // Original code, copies the values of the specified Global Inventory Grid
  // into the output Inventory Grid.
  unsigned int source_inventory_arrange_mode =
      GetSourceInventoryArrangeMode();

  d2::InventoryRecord_View global_inventory_txt_view(
      d2::d2common::GetGlobalInventoryTxt()
  );
  d2::GridLayout_View global_inventory_grid_layout(
      global_inventory_txt_view[
          inventory_record_index + (source_inventory_arrange_mode * 16)
      ].GetGridLayout()
  );

  d2::GridLayout_Wrapper out_grid_layout_wrapper(out_grid_layout);
  out_grid_layout_wrapper.AssignMembers(global_inventory_grid_layout);

  // Do not adjust positions if the entries are empty, which use value 0.
  constexpr int entry_empty_value = 0;
  if (out_grid_layout_wrapper.GetNumColumns() == entry_empty_value
      || out_grid_layout_wrapper.GetNumRows() == entry_empty_value
  ) {
    return;
  }

  // Adjustment code to ensure that the objects appear in the correct
  // location.
  RealignPositionFromCenter(
      out_grid_layout_wrapper.GetPosition()
  );
}

} // namespace sgd2fr::patches
