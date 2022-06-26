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

#include "d2client_enable_800_new_skill_button_patch_1_13c.hpp"

#include <stddef.h>

extern "C" {

void __cdecl
D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01();

void __cdecl
D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc02();

} // extern "C"

namespace sgd2fr {
namespace d2client {

Enable800NewSkillButtonPatch_1_13C::Enable800NewSkillButtonPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  // Enable drawing the New Skill button on the interface bar when the
  // Skill Tree Screen is open or screens on both sides are open.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  // Disable drawing the 640x480 "New Skill" text and New Skill button
  // underlay on the left side.
  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_02.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);

  // Enable drawing the New Skill button animation when button is
  // pressed.
  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  ::mapi::GamePatch patch_03 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_03.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);

  // Enable drawing the New Skill button when there are skill points to
  // spend.
  PatchAddressAndSize patch_address_and_size_04 =
      GetPatchAddressAndSize04();
  ::mapi::GamePatch patch_04 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_04.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_04.second
  );
  this->patches_[3].Swap(patch_04);

  // Adjust the mouse position detection for New Skill button.
  PatchAddressAndSize patch_address_and_size_05 =
      GetPatchAddressAndSize05();
  ::mapi::GamePatch patch_05 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_05.first,
      ::mapi::BranchType::kJump,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc02,
      patch_address_and_size_05.second
  );
  this->patches_[4].Swap(patch_05);

  // Enable additional New Skill button pressed check for mouse
  // position detection for New Skill button press.
  PatchAddressAndSize patch_address_and_size_06 =
      GetPatchAddressAndSize06();
  ::mapi::GamePatch patch_06 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_06.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_06.second
  );
  this->patches_[5].Swap(patch_06);

  // Enable use of 800x600 mouse positon detection code for New Skill
  // button press.
  PatchAddressAndSize patch_address_and_size_07 =
      GetPatchAddressAndSize07();
  ::mapi::GamePatch patch_07 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_07.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_07.second
  );
  this->patches_[6].Swap(patch_07);

  // Enable additional New Skill button pressed check for mouse
  // position detection for New Skill button press and opening the
  // Skill Tree Screen.
  PatchAddressAndSize patch_address_and_size_08 =
      GetPatchAddressAndSize08();
  ::mapi::GamePatch patch_08 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_08.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_08.second
  );
  this->patches_[7].Swap(patch_08);

  // Enable use of 800x600 mouse positon detection code for New Skill
  // button press and opening the Skill Tree Screen.
  PatchAddressAndSize patch_address_and_size_09 =
      GetPatchAddressAndSize09();
  ::mapi::GamePatch patch_09 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_09.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_09.second
  );
  this->patches_[8].Swap(patch_09);

  // Enable drawing the New Skill button press when there are no skill
  // points.
  PatchAddressAndSize patch_address_and_size_10 =
      GetPatchAddressAndSize10();
  ::mapi::GamePatch patch_10 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_10.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_10.second
  );
  this->patches_[9].Swap(patch_10);
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read breakpoint on D2Client's IsNewSkillButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50207
          ),
          0x5020C - 0x50207
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20B77
          ),
          0x20B7C - 0x20B77
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA352F
          ),
          0xA3534 - 0xA352F
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6E71
          ),
          0xA6E76 - 0xA6E71
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize02() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read breakpoint on D2Client's IsNewSkillButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x502A5
          ),
          0x502AA - 0x502A5
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20C15
          ),
          0x20C1A - 0x20C15
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA35BA
          ),
          0xA35BF - 0xA35BA
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6EF6
          ),
          0xA6EFB - 0xA6EF6
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize03() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read breakpoint on D2Client's IsNewSkillButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x5031C
          ),
          0x50321 - 0x5031C
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20C8C
          ),
          0x20C91 - 0x20C8C
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA3632
          ),
          0xA3637 - 0xA3632
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6F72
          ),
          0xA6F77 - 0xA6F72
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize04() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read breakpoint on D2Client's IsNewSkillButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50380
          ),
          0x50385 - 0x50380
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20CF0
          ),
          0x20CF5 - 0x20CF0
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA369A
          ),
          0xA369F - 0xA369A
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6FD6
          ),
          0xA6FDB - 0xA6FD6
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize05() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read breakpoint on D2Client's IsNewSkillButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list. Note that this is only the function that calls
  *    the actual function containing the patch location.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4FE70
          ),
          0x4FEB4 - 0x4FE70
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20A10
          ),
          0x20A54 - 0x20A10
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA2D60
          ),
          0xA2DA9 - 0xA2D60
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6690
          ),
          0xA66D9 - 0xA6690
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize06() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewSkillButtonPressed variable.
  * 3. Click on the New Skill button.
  * 4. In the read and write breakpoint trigger list, select the
  *    2nd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x506AF
          ),
          0x506B4 - 0x506AF
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x211DF
          ),
          0x211E4 - 0x211DF
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA2E5F
          ),
          0xA2E64 - 0xA2E5F
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA67A3
          ),
          0xA67A8 - 0xA67A3
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize07() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewSkillButtonPressed variable.
  * 3. Click on the New Skill button.
  * 4. In the read and write breakpoint trigger list, select the
  *    2nd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x506C9
          ),
          0x506CE - 0x506C9
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x211F9
          ),
          0x211FE - 0x211F9
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA2E7D
          ),
          0xA2E82 - 0xA2E7D
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA67C1
          ),
          0xA67C6 - 0xA67C1
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize08() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewSkillButtonPressed variable.
  * 3. Click on the New Skill button.
  * 4. In the read and write breakpoint trigger list, select the
  *    3rd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50810
          ),
          0x50815 - 0x50810
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x21340
          ),
          0x21345 - 0x21340
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA2FDF
          ),
          0xA2FE4 - 0xA2FDF
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6931
          ),
          0xA6936 - 0xA6931
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize09() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 skill point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewSkillButtonPressed variable.
  * 3. Click on the New Skill button.
  * 4. In the read and write breakpoint trigger list, select the
  *    3rd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x5082E
          ),
          0x50833 - 0x5082E
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x2135E
          ),
          0x21363 - 0x2135E
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA3000
          ),
          0xA3005 - 0xA3000
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6951
          ),
          0xA6956 - 0xA6951
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize10() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with no skill points.
  * 2. Set a read breakpoint on D2Client's GeneralDisplayWidth
  *    variable.
  * 3. Allow the read breakpoint list to fill up.
  * 4. Mouse over the New Skill button.
  * 5. In the read breakpoint trigger list, scroll down and select the
  *    last result. Go to that code location.
  * 6. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50023
          ),
          0x50028 - 0x50023
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20DA3
          ),
          0x20DA8 - 0x20DA3
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA3463
          ),
          0xA3468 - 0xA3463
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xA6DA6
          ),
          0xA6DAB - 0xA6DA6
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
