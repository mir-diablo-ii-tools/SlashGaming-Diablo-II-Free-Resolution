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

#include "d2client_enable_800_new_stats_button_patch_1_13c.hpp"

#include <stddef.h>

namespace sgd2fr {
namespace d2client {

extern "C" {

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01();

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc02();

} // extern "C"

Enable800NewStatsButtonPatch_1_13C::Enable800NewStatsButtonPatch_1_13C()
    : patches_() {
  // Enable drawing the New Stats button on the interface bar when the
  // (Lying) Charater Screen is open or screens on both sides are
  // open.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  // Disable drawing the 640x480 "New Stats" text and New Stats button
  // underlay on the left side.
  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_02.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);

  // Enable drawing the New Stats button animation when button is
  // pressed.
  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  ::mapi::GamePatch patch_03 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_03.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);

  // Enable drawing the New Stats button when there are stat points to
  // spend.
  PatchAddressAndSize patch_address_and_size_04 =
      GetPatchAddressAndSize04();
  ::mapi::GamePatch patch_04 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_04.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_04.second
  );
  this->patches_[3].Swap(patch_04);

  // Adjust the mouse position detection for New Stats button.
  PatchAddressAndSize patch_address_and_size_05 =
      GetPatchAddressAndSize05();
  ::mapi::GamePatch patch_05 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_05.first,
      ::mapi::BranchType::kJump,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc02,
      patch_address_and_size_05.second
  );
  this->patches_[4].Swap(patch_05);

  // Enable additional New Stats button pressed check for mouse
  // position detection for New Stats button press.
  PatchAddressAndSize patch_address_and_size_06 =
      GetPatchAddressAndSize06();
  ::mapi::GamePatch patch_06 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_06.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_06.second
  );
  this->patches_[5].Swap(patch_06);

  // Enable use of 800x600 mouse positon detection code for New Stats
  // button press.
  PatchAddressAndSize patch_address_and_size_07 =
      GetPatchAddressAndSize07();
  ::mapi::GamePatch patch_07 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_07.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_07.second
  );
  this->patches_[6].Swap(patch_07);

  // Enable additional New Stats button pressed check for mouse
  // position detection for New Stats button press and opening the
  // (Lying) Charater Screen.
  PatchAddressAndSize patch_address_and_size_08 =
      GetPatchAddressAndSize08();
  ::mapi::GamePatch patch_08 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_08.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_08.second
  );
  this->patches_[7].Swap(patch_08);

  // Enable use of 800x600 mouse positon detection code for New Stats
  // button press and opening the (Lying) Charater Screen.
  PatchAddressAndSize patch_address_and_size_09 =
      GetPatchAddressAndSize09();
  ::mapi::GamePatch patch_09 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_09.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_09.second
  );
  this->patches_[8].Swap(patch_09);

  // Enable drawing the New Stats button press when there are no Stat
  // points.
  PatchAddressAndSize patch_address_and_size_10 =
      GetPatchAddressAndSize10();
  ::mapi::GamePatch patch_10 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_10.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_10.second
  );
  this->patches_[9].Swap(patch_10);
}

void Enable800NewStatsButtonPatch_1_13C::Apply() {
  for (size_t i = 0; i < kPatchesCount; i += 1) {
    this->patches_[i].Apply();
  }
}

void Enable800NewStatsButtonPatch_1_13C::Remove() {
  for (size_t i = kPatchesCount - 1; (i + 1) > 0; i -= 1) {
    this->patches_[i].Remove();
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50447
          ),
          0x5044C - 0x50447
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20E67
          ),
          0x20E6C - 0x20E67
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x504EC
          ),
          0x504F1 - 0x504EC
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20F0C
          ),
          0x20F11 - 0x20F0C
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50563
          ),
          0x50568 - 0x50563
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20F83
          ),
          0x20F88 - 0x20F83
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize04() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x505C8
          ),
          0x505CD - 0x505C8
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20FE8
          ),
          0x20FED - 0x20FE8
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize05() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x4FF10
          ),
          0x4FF55 - 0x4FF10
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x20AB0
          ),
          0x20AF5 - 0x20AB0
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize06() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x5075F
          ),
          0x50764 - 0x5075F
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x2128F
          ),
          0x21294 - 0x2128F
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize07() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x5077D
          ),
          0x50782 - 0x5077D
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x212AD
          ),
          0x212B2 - 0x212AD
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize08() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50B70
          ),
          0x50B75 - 0x50B70
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x216A0
          ),
          0x216A5 - 0x216A0
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize09() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50B8E
          ),
          0x50B93 - 0x50B8E
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x216BE
          ),
          0x216C3 - 0x216BE
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_13C::GetPatchAddressAndSize10() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x50103
          ),
          0x50108 - 0x50103
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x21093
          ),
          0x21098 - 0x21093
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
