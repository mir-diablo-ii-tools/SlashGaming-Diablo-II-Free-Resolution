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

#include "set_d2ddraw_bit_block_width_and_height_patch_1_09d.hpp"

#include "../../../asm_x86_macro.h"
#include "set_d2ddraw_bit_block_width_and_height.hpp"

namespace sgd2fr::patches {
namespace {

__declspec(naked) void __cdecl InterceptionFunc_01() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(sub esp, 8);
  ASM_X86(lea eax, [ebp - 4]);
  ASM_X86(lea ecx, [ebp - 8]);

  ASM_X86(push ecx);
  ASM_X86(push eax);
  ASM_X86(push esi);
  ASM_X86(call ASM_X86_FUNC(SGD2FR_SetD2DDrawBitBlockWidthAndHeight));
  ASM_X86(add esp, 12);

  ASM_X86(pop ecx);
  ASM_X86(pop eax);

  ASM_X86(leave);
  ASM_X86(ret);
}

} // namespace

std::vector<mapi::GamePatch> MakeSetD2DDrawBitBlockWidthAndHeightPatch_1_09D() {
  std::vector<mapi::GamePatch> patches;

  mapi::GameAddress game_address_01 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2DDraw,
      0x17DF
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_01),
          mapi::BranchType::kCall,
          &InterceptionFunc_01,
          0x1803 - 0x17DF
      )
  );

  mapi::GameAddress game_address_02 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2DDraw,
      0x180A
  );

  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          std::move(game_address_02),
          0x1810 - 0x180A
      )
  );

  return patches;
}

} // namespace sgd2fr::patches
