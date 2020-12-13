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

#include "d2client_draw_screen_background_patch_1_09d.hpp"

#include <unordered_map>

#include "../../../asm_x86_macro.h"
#include "d2client_draw_screen_background.hpp"

namespace sgd2fr::patches::d2client {
namespace {

extern "C" static std::intptr_t __cdecl
Sgd2fr_D2Client_DrawScreenBackground_GetJumpAddress_1_09D() {
  mapi::GameAddress address = mapi::GameAddress::FromOffset(
      mapi::DefaultLibrary::kD2Client,
      0x35750
  );

  return address.raw_address();
}

static __declspec(naked) void __cdecl InterceptionFunc01() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(Sgd2fr_D2Client_DrawScreenBackground));
  ASM_X86(call ASM_X86_FUNC(
      Sgd2fr_D2Client_DrawScreenBackground_GetJumpAddress_1_09D
  ));

  ASM_X86(pop edx);
  ASM_X86(pop ecx);

  ASM_X86(leave);
  ASM_X86(jmp eax);
}

} // namespace

DrawScreenBackgroundPatch_1_09D::DrawScreenBackgroundPatch_1_09D()
    : patches_(MakePatches()) {
}

void DrawScreenBackgroundPatch_1_09D::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void DrawScreenBackgroundPatch_1_09D::Remove() {
  for (auto& patch : this->patches_) {
    patch.Remove();
  }
}

std::vector<mapi::GamePatch>
DrawScreenBackgroundPatch_1_09D::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  d2::GameVersion running_game_version_id = d2::GetRunningGameVersionId();

  // Draw the new screen background.
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          GetPatchAddress01(),
          mapi::BranchType::kCall,
          &InterceptionFunc01,
          0x86970 - 0x8696B
      )
  );

  // Disable the left screen background.
  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          GetPatchAddress02(),
          0x58FB1 - 0x58F1B
      )
  );

  // Disable the right screen background.
  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          GetPatchAddress03(),
          0x5909C - 0x58FF0
      )
  );

  return patches;
}

const mapi::GameAddress& 
DrawScreenBackgroundPatch_1_09D::GetPatchAddress01() {
  static const std::unordered_map<
      d2::GameVersion,
      mapi::GameAddress
  > kPatchAddresses01 = {
      {
          d2::GameVersion::k1_09D,
          mapi::GameAddress::FromOffset(
              mapi::DefaultLibrary::kD2Client,
              0x8696B
          )
      }
  };

  return kPatchAddresses01.at(d2::GetRunningGameVersionId());
}

const mapi::GameAddress&
DrawScreenBackgroundPatch_1_09D::GetPatchAddress02() {
  static const std::unordered_map<
      d2::GameVersion,
      mapi::GameAddress
  > kPatchAddresses02 = {
      {
          d2::GameVersion::k1_09D,
          mapi::GameAddress::FromOffset(
              mapi::DefaultLibrary::kD2Client,
              0x58F1B
          )
      }
  };

  return kPatchAddresses02.at(d2::GetRunningGameVersionId());
}

const mapi::GameAddress&
DrawScreenBackgroundPatch_1_09D::GetPatchAddress03() {
  static const std::unordered_map<
      d2::GameVersion,
      mapi::GameAddress
  > kPatchAddresses03 = {
      {
          d2::GameVersion::k1_09D,
          mapi::GameAddress::FromOffset(
              mapi::DefaultLibrary::kD2Client,
              0x58FF0
          )
      }
  };

  return kPatchAddresses03.at(d2::GetRunningGameVersionId());
}

} // namespace sgd2fr::patches::d2client
