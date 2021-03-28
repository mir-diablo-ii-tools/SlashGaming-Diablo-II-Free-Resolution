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

#include "d2glide_set_display_width_and_height_patch_1_09d.hpp"

#include <array>

extern "C" {

void __cdecl
D2Glide_SetDisplayWidthAndHeightPatch_1_09D_InterceptionFunc01();

} // extern "C"

namespace sgd2fr::patches::d2glide {
namespace {

/**
 * nop
 * nop
 * nop
 * nop
 * nop
 * cmp eax, 1
 * jne D2Glide.dll+1BD1
 */
static constexpr std::array<std::uint8_t, 10> kPatchBuffer02 = {
    0x90, 0x90, 0x90, 0x90, 0x90, 0x83, 0xF8, 0x01, 0x75, 0x11
};

} // namespace

SetDisplayWidthAndHeightPatch_1_09D::SetDisplayWidthAndHeightPatch_1_09D()
  : patches_(MakePatches()) {
}

void SetDisplayWidthAndHeightPatch_1_09D::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void SetDisplayWidthAndHeightPatch_1_09D::Remove() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

std::vector<mapi::GamePatch>
SetDisplayWidthAndHeightPatch_1_09D::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_01.first,
          mapi::BranchType::kCall,
          &D2Glide_SetDisplayWidthAndHeightPatch_1_09D_InterceptionFunc01,
          patch_address_and_size_01.second
      )
  );

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  patches.push_back(
      mapi::GamePatch::MakeGameBufferPatch(
          patch_address_and_size_02.first,
          kPatchBuffer02.data(),
          patch_address_and_size_02.second
      )
  );

  return patches;
}

SetDisplayWidthAndHeightPatch_1_09D::PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_09D::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1B8B
          ),
          0x1B9F - 0x1B8B
      );
    }
  }
}

SetDisplayWidthAndHeightPatch_1_09D::PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_09D::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1BB6
          ),
          kPatchBuffer02.size()
      );
    }
  }
}

} // namespace sgd2fr::patches::d2glide
