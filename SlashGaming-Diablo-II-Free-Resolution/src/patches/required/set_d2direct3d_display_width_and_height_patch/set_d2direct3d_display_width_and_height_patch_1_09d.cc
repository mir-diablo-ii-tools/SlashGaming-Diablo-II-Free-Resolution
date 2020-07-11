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

#include "set_d2direct3d_display_width_and_height_patch_1_09d.hpp"

#include <array>

#include "../../../asm_x86_macro.h"
#include "set_d2direct3d_display_width_and_height.hpp"

namespace sgd2fr::patches {
namespace {

__declspec(naked) void __cdecl InterceptionFunc() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx); 
  ASM_X86(push edx);

  ASM_X86(push edi);
  ASM_X86(call ASM_X86_FUNC(SGD2FR_SetD2Direct3DDisplayWidthAndHeight));
  ASM_X86(add esp, 4);

  ASM_X86(pop edx); 
  ASM_X86(pop ecx);

  ASM_X86(mov eax, edi);

  ASM_X86(leave);
  ASM_X86(ret);
}

/**
 * nop
 * nop
 * nop
 * nop
 * cmp eax, 1
 * jne D2D2Direct3D.dll+20DB
 */
constexpr std::array<std::uint8_t, 9> kPatchBuffer_02 = {
    0x90, 0x90, 0x90, 0x90, 0x83, 0xF8, 0x01, 0x75, 0x0D
};

} // namespace

std::vector<mapi::GamePatch> MakeSetD2Direct3DDisplayWidthAndHeightPatch_1_09D() {
  std::vector<mapi::GamePatch> patches;

  mapi::GameAddress game_address_01 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Direct3D,
      0x2085
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          std::move(game_address_01),
          mapi::BranchType::kCall,
          &InterceptionFunc,
          0x20C5 - 0x2085
      )
  );

  mapi::GameAddress game_address_02 = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Direct3D,
      0x20C5
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBufferPatch(
          std::move(game_address_02),
          kPatchBuffer_02.cbegin(),
          kPatchBuffer_02.cend()
      )
  );

  return patches;
}

} // namespace sgd2fr::patches
