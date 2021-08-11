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

#include "d2client_get_resolution_registry.hpp"

#include <stddef.h>

#include <sgd2mapi.hpp>
#include "../../../game_resolution/game_resolution_global.h"

namespace sgd2fr::patches {

void __cdecl Sgd2fr_D2Client_GetResolutionRegistry(
    uint32_t* reg_resolution_mode,
    uint32_t* ingame_resolution_mode
) {
  // Check the user's input to prevent out-of-index selections.
  *reg_resolution_mode = Global_GetIngameResolutionMode();

  size_t min_config_resolution_id = Global_GetMinConfigResolutionMode();

  if (*reg_resolution_mode < min_config_resolution_id
      || *reg_resolution_mode >= Global_GetMaxConfigResolutionMode()) {
    *reg_resolution_mode = min_config_resolution_id;
  }

  if (*reg_resolution_mode == 0) {
    *ingame_resolution_mode = 0;
  } else {
    *ingame_resolution_mode = *reg_resolution_mode + 1;
  }
}

} // namespace sgd2fr::patches
