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
    : patches_() {
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

void Enable800NewSkillButtonPatch_1_13C::Apply() {
  for (size_t i = 0; i < kPatchesCount; i += 1) {
    this->patches_[i].Apply();
  }
}

void Enable800NewSkillButtonPatch_1_13C::Remove() {
  for (size_t i = kPatchesCount - 1; (i + 1) > 0; i -= 1) {
    this->patches_[i].Remove();
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize01() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize02() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize03() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize04() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize05() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize06() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize07() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize08() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize09() {
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
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_13C::GetPatchAddressAndSize10() {
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
  }
}

} // namespace d2client
} // namespace sgd2fr
