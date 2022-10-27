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

#include "patch_1_13c.hpp"

#include <stddef.h>

namespace sgd2fr {
namespace d2client {

DisableMouseClickOnScreenPatch_1_13C::DisableMouseClickOnScreenPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  // Disable left screen click-through.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameNopPatch(
      patch_address_and_size_01.first,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  // Disable right screen click-through.
  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameNopPatch(
      patch_address_and_size_02.first,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);
}


PatchAddressAndSize
DisableMouseClickOnScreenPatch_1_13C::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Start a game with any character.
  * 2. Set a read breakpoint for D2Client's GeneralDisplayHeight
  *    variable.
  * 3. Open the (Lying) Character Screen.
  * 4. Click anywhere that is not on the left half of the screen.
  * 5. Click the screen's border frame.
  * 6. If done correctly, the read opcode listed near the bottom
  *    should be inside of the patch location's function. Its counter
  *    only increases when the screen border frame is clicked.
  * 7. Go to the location of this opcode.
  * 8. Select the opcode that calls the getter function for D2GFX's
  *    ResolutionMode variable and compares its value to 2.
  * 9. Scroll up to locate the patch location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x6AF10
          ),
          0x6AF1A - 0x6AF10
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xBCB30
          ),
          0xBCB3A - 0xBCB30
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xBF2D0
          ),
          0xBF2DA - 0xBF2D0
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA3DA0
          ),
          0xA3DAA - 0xA3DA0
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA76C0
          ),
          0xA76CA - 0xA76C0
      );
    }
  }
}

PatchAddressAndSize
DisableMouseClickOnScreenPatch_1_13C::GetPatchAddressAndSize02() {
  /*
  * How to find patch locations:
  * 1. Start a game with any character.
  * 2. Set a read breakpoint for D2Client's GeneralDisplayHeight
  *    variable.
  * 3. Open the Inventory Screen. Although the Skill Tree Screen is a
  *    screen that appear on the right side of the display, clicks in
  *    certain places will not trigger the code that will be patched.
  * 4. Click anywhere that is not on the right half of the screen.
  * 5. Click the screen's border frame.
  * 6. If done correctly, the read opcode listed near the bottom
  *    should be inside of the patch location's function. Its counter
  *    only increases when the screen border frame is clicked.
  * 7. Go to the location of this opcode.
  * 8. Select the opcode that calls the getter function for D2GFX's
  *    ResolutionMode variable and compares its value to 2.
  * 9. Scroll up to locate the patch location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA7040
          ),
          0xA704A - 0xA7040
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x8F880
          ),
          0x8F88A - 0x8F880
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x94820
          ),
          0x9482A - 0x94820
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x82FE0
          ),
          0x82FEA - 0x82FE0
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x86E63
          ),
          0x86E6D - 0x86E63
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
