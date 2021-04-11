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

#include "d2client_enable_800_new_skill_button_patch_1_09d.hpp"

extern "C" {

void __cdecl
D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01();

void __cdecl
D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc03();

void __cdecl
D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc13();

void __cdecl
D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc14();

void __cdecl
D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc18();

} // extern "C"

namespace sgd2fr {
namespace d2client {

Enable800NewSkillButtonPatch_1_09D::Enable800NewSkillButtonPatch_1_09D()
    : patches_() {
  // Enable the click on 800x600 New Skill button sound.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_02.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);

  // Adjust the click detection of the New Stats button sound.
  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  ::mapi::GamePatch patch_03 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_03.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);

  // Enable displaying of the Skill Tree Screen when the 800x600 New
  // Stats button is clicked.
  PatchAddressAndSize patch_address_and_size_04 =
      GetPatchAddressAndSize04();
  ::mapi::GamePatch patch_04 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_04.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_04.second
  );
  this->patches_[3].Swap(patch_04);

  PatchAddressAndSize patch_address_and_size_05 =
      GetPatchAddressAndSize05();
  ::mapi::GamePatch patch_05 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_05.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_05.second
  );
  this->patches_[4].Swap(patch_05);

  // Adjust the click detection of the New Skill button for opening the
  // Skill Tree Screen.
  PatchAddressAndSize patch_address_and_size_06 =
      GetPatchAddressAndSize06();
  ::mapi::GamePatch patch_06 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_06.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_06.second
  );
  this->patches_[5].Swap(patch_06);

  // Enable setting the 800x600 New Skill button image frame on mouse over.
  PatchAddressAndSize patch_address_and_size_07 =
      GetPatchAddressAndSize07();
  ::mapi::GamePatch patch_07 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_07.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_07.second
  );
  this->patches_[6].Swap(patch_07);

  // Set the 800x600 New Skill button image frame on mouse over.
  PatchAddressAndSize patch_address_and_size_08 =
      GetPatchAddressAndSize08();
  ::mapi::GamePatch patch_08 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_08.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_08.second
  );
  this->patches_[7].Swap(patch_08);

  // Enable all repositioning of 800x600 text and level up buttons.
  PatchAddressAndSize patch_address_and_size_09 =
      GetPatchAddressAndSize09();
  ::mapi::GamePatch patch_09 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_09.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_09.second
  );
  this->patches_[8].Swap(patch_09);

  PatchAddressAndSize patch_address_and_size_10 =
      GetPatchAddressAndSize10();
  ::mapi::GamePatch patch_10 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_10.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_10.second
  );
  this->patches_[9].Swap(patch_10);

  // Enable repositioning 800x600 "New Stats" text and New Stats button.
  PatchAddressAndSize patch_address_and_size_11 =
      GetPatchAddressAndSize11();
  ::mapi::GamePatch patch_11 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_11.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_11.second
  );
  ::mapi::GameAddress game_address_11 = ::mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48E69
  );
  this->patches_[10].Swap(patch_11);

  // Realign the mouse over detection for 800x600 New Skill text.
  PatchAddressAndSize patch_address_and_size_12 =
      GetPatchAddressAndSize12();
  ::mapi::GamePatch patch_12 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_12.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_12.second
  );
  this->patches_[11].Swap(patch_12);

  // Draw the "New Skill" text.
  PatchAddressAndSize patch_address_and_size_13 =
      GetPatchAddressAndSize13();
  ::mapi::GamePatch patch_13 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_13.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc13,
      patch_address_and_size_13.second
  );
  this->patches_[12].Swap(patch_13);

  // Draw the New Skill button.
  PatchAddressAndSize patch_address_and_size_14 =
      GetPatchAddressAndSize14();
  ::mapi::GamePatch patch_14 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_14.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc14,
      patch_address_and_size_14.second
  );
  this->patches_[13].Swap(patch_14);

  // Enable repositioning 800x600 inactive "New Stats" text and New Stats button.
  PatchAddressAndSize patch_address_and_size_15 =
      GetPatchAddressAndSize15();
  ::mapi::GamePatch patch_15 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_15.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_15.second
  );
  this->patches_[14].Swap(patch_15);

  // Realign the mouse over detection for 800x600 inactive New Skill text.
  PatchAddressAndSize patch_address_and_size_16 =
      GetPatchAddressAndSize16();
  ::mapi::GamePatch patch_16 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_16.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_16.second
  );
  this->patches_[15].Swap(patch_16);

  // Draw the inactive "New Skill" text.
  PatchAddressAndSize patch_address_and_size_17 =
      GetPatchAddressAndSize17();
  ::mapi::GamePatch patch_17 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_17.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc13,
      patch_address_and_size_17.second
  );
  this->patches_[16].Swap(patch_17);

  // Draw the inactive New Skill button.
  PatchAddressAndSize patch_address_and_size_18 =
      GetPatchAddressAndSize18();
  ::mapi::GamePatch patch_18 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_18.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewSkillButtonPatch_1_09D_InterceptionFunc18,
      patch_address_and_size_18.second
  );
  this->patches_[17].Swap(patch_18);
}

void Enable800NewSkillButtonPatch_1_09D::Apply() {
  for (size_t i = 0; i < kPatchesCount; i += 1) {
    this->patches_[i].Apply();
  }
}

void Enable800NewSkillButtonPatch_1_09D::Remove() {
  for (size_t i = kPatchesCount - 1; (i + 1) > 0; i -= 1) {
    this->patches_[i].Remove();
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x483B4
          ),
          0x483B9 - 0x483B4
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x483D3
          ),
          0x483D8 - 0x483D3
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4847D
          ),
          0x484B5 - 0x4847D
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize04() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48694
          ),
          0x48699 - 0x48694
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize05() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x486B2
          ),
          0x486B7 - 0x486B2
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize06() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4878C
          ),
          0x487C4 - 0x4878C
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize07() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48DE5
          ),
          0x48DEA - 0x48DE5
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize08() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48EF1
          ),
          0x48F29 - 0x48EF1
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize09() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48CAD
          ),
          0x48CB2 - 0x48CAD
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize10() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48D6D
          ),
          0x48D72 - 0x48D6D
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize11() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48E69
          ),
          0x48E6E - 0x48E69
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize12() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48F3E
          ),
          0x48F6A - 0x48F3E
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize13() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48F7C
          ),
          0x48F9A - 0x48F7C
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize14() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48F9A
          ),
          0x48FB8 - 0x48F9A
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize15() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48BE3
          ),
          0x48BE8 - 0x48BE3
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize16() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48C15
          ),
          0x48C41 - 0x48C15
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize17() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48C53
          ),
          0x48C71 - 0x48C53
      );
    }
  }
}

PatchAddressAndSize
Enable800NewSkillButtonPatch_1_09D::GetPatchAddressAndSize18() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48C71
          ),
          0x48C8F - 0x48C71
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
