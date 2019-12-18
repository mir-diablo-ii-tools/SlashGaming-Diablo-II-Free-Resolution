/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019  Mir Drualga
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

#include "d2client_click_new_stats_button_patch_1_09d.hpp"

#include "../../../asm_x86_macro.h"
#include "d2client_click_new_stats_button.hpp"

namespace sgd2fr::patches {
namespace {

__declspec(naked) void __cdecl InterceptionFunc_01() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_Enable800NewStatsButton));

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc_02() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_IsMouseOverNewStatsButton));

  ASM_X86(pop edx);

  // Affects the instructions:
  // cmp eax, ecx
  // jge
  ASM_X86(mov ecx, eax);
  ASM_X86(mov eax, 0);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc_03() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push eax);
  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_SetNewStatsPopUpText));

  ASM_X86(pop edx);
  ASM_X86(pop ecx);
  ASM_X86(pop eax);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc_04() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  // Pushes the CelContext for the Level button.
  ASM_X86(lea eax, dword ptr [ebp + 20]);
  ASM_X86(push eax);
  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_DrawNewStatsButton));
  ASM_X86(add esp, 4);

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

} // namespace

std::vector<mapi::GamePatch> Make_D2Client_ClickNewStatsButtonPatch_1_09D() {
  std::vector<mapi::GamePatch> patches;

  // Enable the click on 800x600 New Stats button sound.
  mapi::GameAddress game_address_01 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48264
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_01),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48269 - 0x48264
      )
  );

  mapi::GameAddress game_address_02 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48283
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_02),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48288 - 0x48283
      )
  );

  // Adjust the click detection of the New Stats button sound.
  mapi::GameAddress game_address_03 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x4831C
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_03),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x4834C - 0x4831C
      )
  );

  // Enable displaying of the (Lying) Character Screen when the 800x600 New
  // Stats button is clicked.
  mapi::GameAddress game_address_04 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48524
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_04),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48529 - 0x48524
      )
  );

  mapi::GameAddress game_address_05 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48542
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_05),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48547 - 0x48542
      )
  );

  // Adjust the click detection of the New Stats button for opening the
  // (Lying) Character Screen.
  mapi::GameAddress game_address_06 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48608
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_06),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x48640 - 0x48608
      )
  );

  // Enable setting the 800x600 New Stats button image frame on mouse over.
  mapi::GameAddress game_address_07 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48A19
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_07),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48A1E - 0x48A19
      )
  );

  // Set the 800x600 New Stats button image frame on mouse over.
  mapi::GameAddress game_address_08 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48B08
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_08),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x48B40 - 0x48B08
      )
  );

  // Enable repositioning 800x600 "New Stats" text and New Stats button.
  mapi::GameAddress game_address_09 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48AA3
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_09),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48AA8 - 0x48AA3
      )
  );

  // Realign the mouse over detection for 800x600 New Stats text.
  mapi::GameAddress game_address_10 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48B5C
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_10),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x48B81 - 0x48B5C
      )
  );

  // Draw the "New Stats" text.
  mapi::GameAddress game_address_11 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48B93
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_11),
          mapi::BranchType::kCall,
          &InterceptionFunc_03,
          0x48BB1 - 0x48B93
      )
  );

  // Draw the New Stats button.
  mapi::GameAddress game_address_12 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48BB1
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_12),
          mapi::BranchType::kCall,
          &InterceptionFunc_04,
          0x48BCF - 0x48BB1
      )
  );

  return patches;
}

} // namespace sgd2fr::patches
