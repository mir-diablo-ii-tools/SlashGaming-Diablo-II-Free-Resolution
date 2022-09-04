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

#include "d2client_enable_800_new_stats_button_patch_1_09d.hpp"

#include <stddef.h>

extern "C" {

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01();

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc03();

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc13();

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc14();

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc18();

} // extern "C"

namespace sgd2fr {
namespace d2client {

Enable800NewStatsButtonPatch_1_09D::Enable800NewStatsButtonPatch_1_09D()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  // Enable the click on 800x600 New Stats button sound.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_02.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);

  // Adjust the click detection of the New Stats button sound.
  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  ::mapi::GamePatch patch_03 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_03.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);

  // Enable displaying of the (Lying) Character Screen when the 800x600 New
  // Stats button is clicked.
  PatchAddressAndSize patch_address_and_size_04 =
      GetPatchAddressAndSize04();
  ::mapi::GamePatch patch_04 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_04.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_04.second
  );
  this->patches_[3].Swap(patch_04);

  PatchAddressAndSize patch_address_and_size_05 =
      GetPatchAddressAndSize05();
  ::mapi::GamePatch patch_05 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_05.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_05.second
  );
  this->patches_[4].Swap(patch_05);

  // Adjust the click detection of the New Stats button for opening the
  // (Lying) Character Screen.
  PatchAddressAndSize patch_address_and_size_06 =
      GetPatchAddressAndSize06();
  ::mapi::GamePatch patch_06 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_06.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_06.second
  );
  this->patches_[5].Swap(patch_06);

  // Enable setting the 800x600 New Stats button image frame on mouse over.
  PatchAddressAndSize patch_address_and_size_07 =
      GetPatchAddressAndSize07();
  ::mapi::GamePatch patch_07 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_07.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_07.second
  );
  this->patches_[6].Swap(patch_07);

  // Set the 800x600 New Stats button image frame on mouse over.
  PatchAddressAndSize patch_address_and_size_08 =
      GetPatchAddressAndSize08();
  ::mapi::GamePatch patch_08 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_08.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_08.second
  );
  this->patches_[7].Swap(patch_08);

  // Enable all repositioning of 800x600 text and level up buttons.
  PatchAddressAndSize patch_address_and_size_09 =
      GetPatchAddressAndSize09();
  ::mapi::GamePatch patch_09 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_09.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_09.second
  );
  this->patches_[8].Swap(patch_09);

  PatchAddressAndSize patch_address_and_size_10 =
      GetPatchAddressAndSize10();
  ::mapi::GamePatch patch_10 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_10.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_10.second
  );
  this->patches_[9].Swap(patch_10);

  // Enable repositioning 800x600 "New Stats" text and New Stats button.
  PatchAddressAndSize patch_address_and_size_11 =
      GetPatchAddressAndSize11();
  ::mapi::GamePatch patch_11 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_11.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_11.second
  );
  this->patches_[10].Swap(patch_11);

  // Realign the mouse over detection for 800x600 New Stats text.
  PatchAddressAndSize patch_address_and_size_12 =
      GetPatchAddressAndSize12();
  ::mapi::GamePatch patch_12 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_12.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_12.second
  );
  this->patches_[11].Swap(patch_12);

  // Draw the "New Stats" text.
  PatchAddressAndSize patch_address_and_size_13 =
      GetPatchAddressAndSize13();
  ::mapi::GamePatch patch_13 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_13.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc13,
      patch_address_and_size_13.second
  );
  this->patches_[12].Swap(patch_13);

  // Draw the New Stats button.
  PatchAddressAndSize patch_address_and_size_14 =
      GetPatchAddressAndSize14();
  ::mapi::GamePatch patch_14 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_14.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc14,
      patch_address_and_size_14.second
  );
  this->patches_[13].Swap(patch_14);

  // Enable repositioning of 800x600 inactive text and level up buttons.
  PatchAddressAndSize patch_address_and_size_15 =
      GetPatchAddressAndSize15();
  ::mapi::GamePatch patch_15 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_15.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_15.second
  );
  this->patches_[14].Swap(patch_15);

  // Realign the mouse over detection for 800x600 inactive New Stats text.
  PatchAddressAndSize patch_address_and_size_16 =
      GetPatchAddressAndSize16();
  ::mapi::GamePatch patch_16 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_16.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc03,
      patch_address_and_size_16.second
  );
  this->patches_[15].Swap(patch_16);

  // Draw the inactive "New Stats" text.
  PatchAddressAndSize patch_address_and_size_17 =
      GetPatchAddressAndSize17();
  ::mapi::GamePatch patch_17 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_17.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc13,
      patch_address_and_size_17.second
  );
  this->patches_[16].Swap(patch_17);

  // Draw the inactive New Stats button.
  PatchAddressAndSize patch_address_and_size_18 =
      GetPatchAddressAndSize18();
  ::mapi::GamePatch patch_18 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_18.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_09D_InterceptionFunc18,
      patch_address_and_size_18.second
  );
  this->patches_[17].Swap(patch_18);
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48264
          ),
          0x48269 - 0x48264
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4ED94
          ),
          0x4ED99 - 0x4ED94
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48283
          ),
          0x48288 - 0x48283
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4EDB3
          ),
          0x4EDB8 - 0x4EDB3
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4831C
          ),
          0x4834C - 0x4831C
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4EE1E
          ),
          0x4EE4A - 0x4EE1E
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize04() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48524
          ),
          0x48529 - 0x48524
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4EFE4
          ),
          0x4EFE9 - 0x4EFE4
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize05() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48542
          ),
          0x48547 - 0x48542
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F002
          ),
          0x4F007 - 0x4F002
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize06() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48608
          ),
          0x48640 - 0x48608
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F0C1
          ),
          0x4F0F9 - 0x4F0C1
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize07() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48A19
          ),
          0x48A1E - 0x48A19
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F4B9
          ),
          0x4F4BE - 0x4F4B9
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize08() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48B08
          ),
          0x48B40 - 0x48B08
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F59A
          ),
          0x4F5D2 - 0x4F59A
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize09() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x488CD
          ),
          0x488D2 - 0x488CD
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F36D
          ),
          0x4F372 - 0x4F36D
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize10() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x489A1
          ),
          0x489A6 - 0x489A1
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F441
          ),
          0x4F446 - 0x4F441
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize11() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48AA3
          ),
          0x48AA8 - 0x48AA3
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F543
          ),
          0x4F548 - 0x4F543
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize12() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48B5C
          ),
          0x48B81 - 0x48B5C
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F5E7
          ),
          0x4F613 - 0x4F5E7
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize13() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48B93
          ),
          0x48BB1 - 0x48B93
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F625
          ),
          0x4F643 - 0x4F625
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize14() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48BB1
          ),
          0x48BCF - 0x48BB1
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F643
          ),
          0x4F661 - 0x4F643
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize15() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48803
          ),
          0x48808 - 0x48803
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F2A3
          ),
          0x4F2A8 - 0x4F2A3
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize16() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48835
          ),
          0x48861 - 0x48835
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F2D5
          ),
          0x4F301 - 0x4F2D5
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize17() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48873
          ),
          0x48891 - 0x48873
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F313
          ),
          0x4F331 - 0x4F313
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_09D::GetPatchAddressAndSize18() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x48891
          ),
          0x488AF - 0x48891
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4F331
          ),
          0x4F34F - 0x4F331
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
