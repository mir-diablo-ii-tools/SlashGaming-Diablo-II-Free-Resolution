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

#include "d2client_enable_800_new_stats_button_patch_1_12a.hpp"

#include <stddef.h>

namespace sgd2fr {
namespace d2client {

extern "C" {

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01();

void __cdecl
D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc02();

} // extern "C"

Enable800NewStatsButtonPatch_1_12A::Enable800NewStatsButtonPatch_1_12A()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  // Enable drawing the New Stats button on the interface bar when the
  // (Lying) Character Screen is open or screens on both sides are
  // open.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
      patch_address_and_size_04.second
  );
  this->patches_[3].Swap(patch_04);

  // Adjust the mouse position detection for New Stats button.
  PatchAddressAndSize patch_address_and_size_05 =
      GetPatchAddressAndSize05();
  ::mapi::GamePatch patch_05 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_05.first,
      ::mapi::BranchType::kJump,
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc02,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
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
      &D2Client_Enable800NewStatsButtonPatch_1_12A_InterceptionFunc01,
      patch_address_and_size_10.second
  );
  this->patches_[9].Swap(patch_10);
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read breakpoint on D2Client's IsNewStatsButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3C2B7
          ),
          0x3C2BC - 0x3C2B7
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize02() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read breakpoint on D2Client's IsNewStatsButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3C35C
          ),
          0x3C361 - 0x3C35C
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize03() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read breakpoint on D2Client's IsNewStatsButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3C3D3
          ),
          0x3C3D8 - 0x3C3D3
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize04() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read breakpoint on D2Client's IsNewStatsButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3C438
          ),
          0x3C43D - 0x3C438
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize05() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read breakpoint on D2Client's IsNewStatsButtonPressed
  *    variable. Only 1 result should show.
  * 3. Go to the code location that is listed in the breakpoint
  *    trigger list. Note that this is only the function that calls
  *    the actual function containing the patch location.
  * 4. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3BF10
          ),
          0x3BF45 - 0x3BF10
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize06() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewStatButtonPressed variable.
  * 3. Click on the New Stats button.
  * 4. In the read and write breakpoint trigger list, select the
  *    2nd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3C66F
          ),
          0x3C674 - 0x3C66F
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize07() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewStatButtonPressed variable.
  * 3. Click on the New Stats button.
  * 4. In the read and write breakpoint trigger list, select the
  *    2nd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3C68D
          ),
          0x3C692 - 0x3C68D
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize08() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewStatsButtonPressed variable.
  * 3. Click on the New Stats button.
  * 4. In the read and write breakpoint trigger list, select the
  *    3rd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3CAE0
          ),
          0x3CAE5 - 0x3CAE0
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize09() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with at least 1 stat point.
  * 2. Set a read and write breakpoint on D2Client's
  *    IsNewStatsButtonPressed variable.
  * 3. Click on the New Stats button.
  * 4. In the read and write breakpoint trigger list, select the
  *    3rd result and go to that code location.
  * 5. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3CAFE
          ),
          0x3CB03 - 0x3CAFE
      );
    }
  }
}

PatchAddressAndSize
Enable800NewStatsButtonPatch_1_12A::GetPatchAddressAndSize10() {
  /*
  * How to find patch locations:
  * 1. Start a game with a character with no stat points.
  * 2. Set a read breakpoint on D2Client's GeneralDisplayWidth
  *    variable.
  * 3. Allow the read breakpoint list to fill up.
  * 4. Mouse over the New Stats button.
  * 5. In the read breakpoint trigger list, scroll down and select the
  *    last result. Go to that code location.
  * 6. Scroll up to the top of the function and find the patch
  *    location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x3C4E3
          ),
          0x3C4E8 - 0x3C4E3
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
