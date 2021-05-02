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

#include "d2common_get_global_belt_slot_position.hpp"

#include <windows.h>

#include <sgd2mapi.hpp>
#include "../../../config.hpp"
#include "../../../helper/cel_file_collection.hpp"
#include "../../../helper/game_resolution.hpp"
#include "../../../helper/position_realignment.hpp"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_D2Common_GetGlobalBeltSlotPosition(
    std::uint32_t belt_record_index,
    std::uint32_t inventory_arrange_mode,
    ::d2::PositionalRectangle* out_belt_slot,
    std::uint32_t belt_slot_index
) {
  // Original code, copies the values of the specified Global Belt Slot
  // into the output Belt Slot.
  unsigned int source_inventory_arrange_mode =
      GetSourceInventoryArrangeMode();

  ::d2::BeltRecord_View global_belt_txt_view(d2::d2common::GetGlobalBeltsTxt());

  ::d2::PositionalRectangle_View global_belt_slot_position(
      global_belt_txt_view[belt_record_index + (source_inventory_arrange_mode * 7)]
          .GetSlotPositions()[belt_slot_index]
  );

  ::d2::PositionalRectangle_Wrapper out_belt_slot_wrapper(out_belt_slot);
  out_belt_slot_wrapper.AssignMembers(global_belt_slot_position);

  // Do not adjust positions if the entries are empty, which use value 0.
  constexpr int entry_empty_value = 0;

  if (out_belt_slot_wrapper.GetLeft() == entry_empty_value
      && out_belt_slot_wrapper.GetRight() == entry_empty_value
      && out_belt_slot_wrapper.GetTop() == entry_empty_value
      && out_belt_slot_wrapper.GetBottom() == entry_empty_value
  ) {
    return;
  }

  // Adjustment code to ensure that the objects appear in the correct
  // position.
  RealignPositionFromBottomCenter(
      out_belt_slot_wrapper
  );
}

} // namespace sgd2fr::patches
