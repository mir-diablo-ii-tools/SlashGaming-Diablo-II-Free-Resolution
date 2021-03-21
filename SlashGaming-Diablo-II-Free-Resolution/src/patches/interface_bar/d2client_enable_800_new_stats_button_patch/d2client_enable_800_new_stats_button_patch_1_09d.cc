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

#include "d2client_enable_800_new_stats_button_patch_1_09d.hpp"

#include "../../../asm_x86_macro.h"
#include "d2client_enable_800_new_stats_button.hpp"

namespace sgd2fr::patches::d2client {
namespace {

__declspec(naked) void __cdecl InterceptionFunc01() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Client_Enable800NewStatsButton));

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc02() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Client_IsMouseOver800NewStatsButton));

  ASM_X86(pop edx);

  // Affects the instructions:
  // cmp eax, ecx
  // jge
  ASM_X86(mov ecx, eax);
  ASM_X86(mov eax, 0);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc03() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push eax);
  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Client_Set800NewStatsPopupText));

  ASM_X86(pop edx);
  ASM_X86(pop ecx);
  ASM_X86(pop eax);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc04() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  // Pushes the CelContext for the Level button.
  ASM_X86(lea eax, dword ptr [ebp + 20]);
  ASM_X86(push eax);
  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Client_Draw800NewStatsButton));
  ASM_X86(add esp, 4);

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc05() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  // Pushes the CelContext for the Level button.
  ASM_X86(lea eax, dword ptr [ebp + 16]);
  ASM_X86(push eax);
  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Client_Draw800NewStatsButton));
  ASM_X86(add esp, 4);

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

} // namespace

Enable800NewStatsButtonPatch_1_09D::Enable800NewStatsButtonPatch_1_09D()
  : patches_(MakePatches()) {
}

void Enable800NewStatsButtonPatch_1_09D::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void Enable800NewStatsButtonPatch_1_09D::Remove() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

std::vector<mapi::GamePatch>
Enable800NewStatsButtonPatch_1_09D::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  // Enable the click on 800x600 New Stats button sound.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_01.first,
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          patch_address_and_size_01.second
      )
  );

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_02.first,
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          patch_address_and_size_02.second
      )
  );

  // Adjust the click detection of the New Stats button sound.
  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_03.first,
          mapi::BranchType::kCall,
          &InterceptionFunc02,
          patch_address_and_size_03.second
      )
  );

  // Enable displaying of the (Lying) Character Screen when the 800x600 New
  // Stats button is clicked.
  PatchAddressAndSize patch_address_and_size_04 =
      GetPatchAddressAndSize04();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_04.first,
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          patch_address_and_size_04.second
      )
  );

  mapi::GameAddress game_address_05 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48542
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_05),
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          0x48547 - 0x48542
      )
  );

  // Adjust the click detection of the New Stats button for opening the
  // (Lying) Character Screen.
  mapi::GameAddress game_address_06 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48608
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_06),
          mapi::BranchType::kCall,
          &InterceptionFunc02,
          0x48640 - 0x48608
      )
  );

  // Enable setting the 800x600 New Stats button image frame on mouse over.
  mapi::GameAddress game_address_07 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48A19
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_07),
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          0x48A1E - 0x48A19
      )
  );

  // Set the 800x600 New Stats button image frame on mouse over.
  mapi::GameAddress game_address_08 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48B08
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_08),
          mapi::BranchType::kCall,
          &InterceptionFunc02,
          0x48B40 - 0x48B08
      )
  );

  // Enable all repositioning of 800x600 text and level up buttons.
  mapi::GameAddress game_address_09 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x488CD
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_09),
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          0x488D2 - 0x488CD
      )
  );

  mapi::GameAddress game_address_10 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x489A1
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_10),
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          0x489A6 - 0x489A1
      )
  );

  // Enable repositioning 800x600 "New Stats" text and New Stats button.
  mapi::GameAddress game_address_11 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48AA3
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_11),
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          0x48AA8 - 0x48AA3
      )
  );

  // Realign the mouse over detection for 800x600 New Stats text.
  mapi::GameAddress game_address_12 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48B5C
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_12),
          mapi::BranchType::kCall,
          &InterceptionFunc02,
          0x48B81 - 0x48B5C
      )
  );

  // Draw the "New Stats" text.
  mapi::GameAddress game_address_13 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48B93
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_13),
          mapi::BranchType::kCall,
          &InterceptionFunc03,
          0x48BB1 - 0x48B93
      )
  );

  // Draw the New Stats button.
  mapi::GameAddress game_address_14 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48BB1
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_14),
          mapi::BranchType::kCall,
          &InterceptionFunc04,
          0x48BCF - 0x48BB1
      )
  );

  // Enable repositioning of 800x600 inactive text and level up buttons.
  mapi::GameAddress game_address_15 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48803
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_15),
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          0x48808 - 0x48803
      )
  );

  // Realign the mouse over detection for 800x600 inactive New Stats text.
  mapi::GameAddress game_address_16 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48835
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_16),
          mapi::BranchType::kCall,
          &InterceptionFunc02,
          0x48861 - 0x48835
      )
  );

  // Draw the inactive "New Stats" text.
  mapi::GameAddress game_address_17 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48873
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_17),
          mapi::BranchType::kCall,
          &InterceptionFunc03,
          0x48891 - 0x48873
      )
  );

  // Draw the inactive New Stats button.
  mapi::GameAddress game_address_18 = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x48891
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_18),
          mapi::BranchType::kCall,
          &InterceptionFunc05,
          0x488AF - 0x48891
      )
  );

  return patches;
}

Enable800NewStatsButtonPatch_1_09D::PatchAddressAndSize
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
  }
}

Enable800NewStatsButtonPatch_1_09D::PatchAddressAndSize
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
  }
}

Enable800NewStatsButtonPatch_1_09D::PatchAddressAndSize
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
  }
}

Enable800NewStatsButtonPatch_1_09D::PatchAddressAndSize
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
  }
}

} // namespace sgd2fr::patches::d2client
