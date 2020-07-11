/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2020  Mir Drualga
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

#include "../../../asm_x86_macro.h"
#include "d2client_enable_800_new_skill_button.hpp"

namespace sgd2fr::patches {
namespace {

__declspec(naked) void __cdecl InterceptionFunc_01() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_Enable800NewSkillButton));

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc_02() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_IsMouseOver800NewSkillButton));

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

  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_Set800NewSkillPopupText));

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
  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_Draw800NewSkillButton));
  ASM_X86(add esp, 4);

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc_05() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  // Pushes the CelContext for the Level button.
  ASM_X86(lea eax, dword ptr [ebp + 16]);
  ASM_X86(push eax);
  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_Draw800NewSkillButton));
  ASM_X86(add esp, 4);

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

} // namespace

std::vector<mapi::GamePatch> Make_D2Client_Click800NewSkillButtonPatch_1_09D() {
  std::vector<mapi::GamePatch> patches;

  // Enable the click on 800x600 New Skill button sound.
  mapi::GameAddress game_address_01 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x483B4
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_01),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x483B9 - 0x483B4
      )
  );

  mapi::GameAddress game_address_02 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x483D3
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_02),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x483D8 - 0x483D3
      )
  );

  // Adjust the click detection of the New Stats button sound.
  mapi::GameAddress game_address_03 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x4847D
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_03),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x484B5 - 0x4847D
      )
  );

  // Enable displaying of the Skill Tree Screen when the 800x600 New
  // Stats button is clicked.
  mapi::GameAddress game_address_04 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48694
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_04),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48699 - 0x48694
      )
  );

  mapi::GameAddress game_address_05 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x486B2
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_05),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x486B7 - 0x486B2
      )
  );

  // Adjust the click detection of the New Skill button for opening the
  // Skill Tree Screen.
  mapi::GameAddress game_address_06 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x4878C
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_06),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x487C4 - 0x4878C
      )
  );

  // Enable setting the 800x600 New Skill button image frame on mouse over.
  mapi::GameAddress game_address_07 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48DE5
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_07),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48DEA - 0x48DE5
      )
  );

  // Set the 800x600 New Skill button image frame on mouse over.
  mapi::GameAddress game_address_08 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48EF1
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_08),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x48F29 - 0x48EF1
      )
  );

  // Enable all repositioning of 800x600 text and level up buttons.
  mapi::GameAddress game_address_09 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48CAD
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_09),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48CB2 - 0x48CAD
      )
  );

  mapi::GameAddress game_address_10 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48D6D
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_10),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48D72 - 0x48D6D
      )
  );

  // Enable repositioning 800x600 "New Stats" text and New Stats button.
  mapi::GameAddress game_address_11 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48E69
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_11),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48E6E - 0x48E69
      )
  );

  // Realign the mouse over detection for 800x600 New Skill text.
  mapi::GameAddress game_address_12 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48F3E
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_12),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x48F6A - 0x48F3E
      )
  );

  // Draw the "New Skill" text.
  mapi::GameAddress game_address_13 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48F7C
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_13),
          mapi::BranchType::kCall,
          &InterceptionFunc_03,
          0x48F9A - 0x48F7C
      )
  );

  // Draw the New Skill button.
  mapi::GameAddress game_address_14 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48F9A
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_14),
          mapi::BranchType::kCall,
          &InterceptionFunc_04,
          0x48FB8 - 0x48F9A
      )
  );

  // Enable repositioning 800x600 inactive "New Stats" text and New Stats button.
  mapi::GameAddress game_address_15 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48BE3
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_15),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x48BE8 - 0x48BE3
      )
  );

  // Realign the mouse over detection for 800x600 inactive New Skill text.
  mapi::GameAddress game_address_16 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48C15
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_16),
          mapi::BranchType::kCall,
          &InterceptionFunc_02,
          0x48C41 - 0x48C15
      )
  );

  // Draw the inactive "New Skill" text.
  mapi::GameAddress game_address_17 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48C53
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_17),
          mapi::BranchType::kCall,
          &InterceptionFunc_03,
          0x48C71 - 0x48C53
      )
  );

  // Draw the inactive New Skill button.
  mapi::GameAddress game_address_18 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x48C71
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_18),
          mapi::BranchType::kCall,
          &InterceptionFunc_05,
          0x48C8F - 0x48C71
      )
  );

  return patches;
}

} // namespace sgd2fr::patches
