/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019  Mir Drualga
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

#include "d2common_get_global_belt_record.hpp"

#include <windows.h>

#include <fmt/format.h>
#include <sgd2mapi.hpp>
#include "../../../config.hpp"
#include "../../../helper/cel_file_collection.hpp"
#include "../../../helper/get_resolution_from_id.hpp"

namespace sgd2fr::patches {

void __cdecl SGD2FR_D2Common_GetGlobalBeltRecord(
    std::uint32_t belt_record_index,
    std::uint32_t inventory_arrange_mode,
    d2::BeltRecord* out_belt_record
) {
  // Original code, copies the values of the specified Global Belt Slot
  // into the output Belt Slot.
  unsigned int source_inventory_arrange_mode = (inventory_arrange_mode < 2)
      ? inventory_arrange_mode
      : 0;

  d2::BeltRecord_View global_belt_txt_view(d2::d2common::GetGlobalBeltsTxt());
  d2::BeltRecord_View global_belt_record_view(
      global_belt_txt_view[belt_record_index + (source_inventory_arrange_mode * 7)]
  );

  d2::BeltRecord_Wrapper out_belt_record_wrapper(out_belt_record);
  out_belt_record_wrapper.Copy(global_belt_record_view);

  // Adjustment code to ensure that the objects appear in the correct location.
  for (std::size_t belt_slot_index = 0;
       belt_slot_index < out_belt_record_wrapper.GetNumSlots();
       belt_slot_index += 1) {
    d2::d2common::GetGlobalBeltSlotPosition(
        belt_record_index,
        inventory_arrange_mode,
        out_belt_record_wrapper.GetSlotPosition(belt_slot_index),
        belt_slot_index
    );
  }
}

} // namespace sgd2fr::patches
