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

#include "d2client_set_resolution_from_options_menu_patch_1_09.hpp"

#include "../../../asm_x86_macro.h"
#include "d2client_set_resolution_from_options_menu.hpp"

namespace sgd2fr::patches::d2client {
namespace {

__declspec(naked) void __cdecl InterceptionFunc() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push eax);
  ASM_X86(push edx);

  ASM_X86(lea ecx, [eax + 0x124])

  ASM_X86(push ecx);
  ASM_X86(push [ecx]);
  ASM_X86(push eax);
  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Client_SetResolutionFromOptionsMenu));
  ASM_X86(add esp, 12);

  ASM_X86(pop edx);
  ASM_X86(pop eax);

  ASM_X86(leave);
  ASM_X86(ret);
}

} // namespace

SetResolutionFromOptionsMenuPatch_1_09D
::SetResolutionFromOptionsMenuPatch_1_09D()
  : patches_(MakePatches()) {
}

void SetResolutionFromOptionsMenuPatch_1_09D::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void SetResolutionFromOptionsMenuPatch_1_09D::Remove() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

std::vector<mapi::GamePatch>
SetResolutionFromOptionsMenuPatch_1_09D::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  mapi::GameAddress game_address = mapi::GameAddress::FromOffset(
      ::d2::DefaultLibrary::kD2Client,
      0x61929
  );

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          game_address,
          mapi::BranchType::kCall,
          &InterceptionFunc,
          0x61933 - 0x61929
      )
  );

  return patches;
}

} // namespace sgd2fr::patches::d2client
