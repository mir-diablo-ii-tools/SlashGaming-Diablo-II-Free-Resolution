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

  ASM_X86(call ASM_X86_FUNC(SGD2FR_D2Client_EnableClick800NewStatsButton));

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(ret);
}

__declspec(naked) void __cdecl InterceptionFunc_02() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push eax);

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

} // namespace

std::vector<mapi::GamePatch> Make_D2Client_ClickNewStatsButtonPatch_1_09D() {
  std::vector<mapi::GamePatch> patches;

  // Enable the click on 800x600 New Stats button logic.
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

  // Adjust the click detection of the New Stats button.
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

  return patches;
}

} // namespace sgd2fr::patches
