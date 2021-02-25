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

#include "d2common_get_global_belt_slot_position_patch_1_09d.hpp"

#include <unordered_map>

#include "../../../asm_x86_macro.h"
#include "d2common_get_global_belt_slot_position.hpp"

namespace sgd2fr::patches::d2common {
namespace {

__declspec(naked) void __cdecl InterceptionFunc_01() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push eax);
  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(push dword ptr [ebp + 20]);
  ASM_X86(push dword ptr [ebp + 16]);
  ASM_X86(push dword ptr [ebp + 12]);
  ASM_X86(push dword ptr [ebp + 8]);
  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Common_GetGlobalBeltSlotPosition));
  ASM_X86(add esp, 16);

  ASM_X86(pop edx);
  ASM_X86(pop ecx);
  ASM_X86(pop eax);

  ASM_X86(leave);
  ASM_X86(ret 16);
}

} // namespace

GetGlobalBeltSlotPositionPatch_1_09D::GetGlobalBeltSlotPositionPatch_1_09D()
  : patches_(MakePatches()) {
}

void GetGlobalBeltSlotPositionPatch_1_09D::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void GetGlobalBeltSlotPositionPatch_1_09D::Remove() {
  for (auto& patch : this->patches_) {
    patch.Remove();
  }
}

const mapi::GameAddress&
GetGlobalBeltSlotPositionPatch_1_09D::GetPatchAddress() {
  static const std::unordered_map<
      d2::GameVersion,
      mapi::GameAddress
  > kPatchAddresses = {
      {
          d2::GameVersion::k1_09D,
          mapi::GameAddress::FromOrdinal(
              ::d2::DefaultLibrary::kD2Common,
              10639
          )
      }
  };

  return kPatchAddresses.at(::d2::game_version::GetRunning());
}

std::vector<mapi::GamePatch>
GetGlobalBeltSlotPositionPatch_1_09D::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          GetPatchAddress(),
          mapi::BranchType::kJump,
          &InterceptionFunc_01,
          5
      )
  );

  return patches;
}

} // namespace sgd2fr::patches::d2common
