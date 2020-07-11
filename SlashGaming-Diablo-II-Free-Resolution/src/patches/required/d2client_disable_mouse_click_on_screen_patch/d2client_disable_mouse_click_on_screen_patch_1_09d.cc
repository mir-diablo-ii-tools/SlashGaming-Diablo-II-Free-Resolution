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

#include "d2client_disable_mouse_click_on_screen_patch_1_09d.hpp"

#include "../../../asm_x86_macro.h"

namespace sgd2fr::patches {

std::vector<mapi::GamePatch> MakeD2ClientDisableMouseClickOnScreenPatch_1_09D() {
  std::vector<mapi::GamePatch> patches;

  // Disable left screen click-through.
  mapi::GameAddress game_address_01 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x2AB1A
  );

  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          std::move(game_address_01),
          0x2AB24 - 0x2AB1A
      )
  );

  // Disable left screen click-through while character is moving.
  mapi::GameAddress game_address_02 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x2AD1A
  );

  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          std::move(game_address_02),
          0x2AD24 - 0x2AD1A
      )
  );

  // Disable right screen click-through.
  mapi::GameAddress game_address_03 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x40873
  );

  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          std::move(game_address_03),
          0x40881 - 0x40873
      )
  );

  return patches;
}

} // namespace sgd2fr::patches
