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

#include "d2client_draw_resolution_text_patch_1_13c.hpp"

#include <stddef.h>

extern "C" {

void __cdecl
D2Client_DrawResolutionTextPatch_1_13C_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace d2client {

DrawResolutionTextPatch_1_13C::DrawResolutionTextPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_DrawResolutionTextPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);
}

PatchAddressAndSize
DrawResolutionTextPatch_1_13C::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Start a game with any character. Do not open the Game Menu.
  * 2. Set a read breakpoint on D2Client's GeneralDisplayWidth
  *    variable.
  * 3. Move the mouse, click, and interact with as many things as
  *    possible on the screen to trigger code that will be added to
  *    the top of the list. Any breakpoint triggers in this list are
  *    to be ignored.
  * 4. Open the game menu.
  * 5. Select the Options menu. Next, select the Video Options menu.
  * 6. Wait for a bit and then leave the Video Options menu by
  *    selecting the Previous Menu. Do not press the ESC key.
  * 7. At the very bottom of the breakpoint trigger list are 5
  *    opcodes. 3 of them belong to a "set" because they trigger at
  *    the same rate. In other words, their trigger counter value is
  *    the same. There is a second "set" containing the other 2
  *    opcodes.
  * 8. In the second "set", go to the address of the second opcode.
  * 9. Follow the sequence of opcodes to a function call. The patch
  *    address is the opcode immediately preceding the function call.
  * 10. The patch also requires the use of a pointer. This pointer is
  *     determined by the value of one or more of the stack and
  *     registers' values at that point in the code. Open the Video
  *     Options menu and set a breakpoint at the function call.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x65407
          ),
          0x6540D - 0x65407
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xC36A7
          ),
          0xC36AD - 0xC36A7
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
