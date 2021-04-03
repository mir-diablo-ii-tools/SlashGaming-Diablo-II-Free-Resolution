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

#include "d2glide_set_display_width_and_height_patch_1_13c.hpp"

#include <array>

extern "C" {

void __cdecl
D2Glide_SetDisplayWidthAndHeightPatch_1_13C_InterceptionFunc01();

} // extern "C"

namespace sgd2fr::patches::d2glide {
namespace {

constexpr ::std::uint8_t kJeOpcode = 0x74;
constexpr ::std::uint8_t k01Byte = 0x01;

} // namespace

SetDisplayWidthAndHeightPatch_1_13C::SetDisplayWidthAndHeightPatch_1_13C()
  : patches_(MakePatches()) {
}

void SetDisplayWidthAndHeightPatch_1_13C::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void SetDisplayWidthAndHeightPatch_1_13C::Remove() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

std::vector<mapi::GamePatch>
SetDisplayWidthAndHeightPatch_1_13C::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_01.first,
          mapi::BranchType::kCall,
          &D2Glide_SetDisplayWidthAndHeightPatch_1_13C_InterceptionFunc01,
          patch_address_and_size_01.second
      )
  );

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  patches.push_back(
      mapi::GamePatch::MakeGameBufferPatch(
          patch_address_and_size_02.first,
          &k01Byte,
          patch_address_and_size_02.second
      )
  );

  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  patches.push_back(
      mapi::GamePatch::MakeGameBufferPatch(
          patch_address_and_size_03.first,
          &kJeOpcode,
          patch_address_and_size_03.second
      )
  );

  return patches;
}

SetDisplayWidthAndHeightPatch_1_13C::PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_13C::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xDCF1
          ),
          0xDD0A - 0xDCF1
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xD601
          ),
          0xD61A - 0xD601
      );
    }
  }
}

SetDisplayWidthAndHeightPatch_1_13C::PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_13C::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xDD15 + 2
          ),
          sizeof(k01Byte)
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xD625 + 2
          ),
          sizeof(k01Byte)
      );
    }
  }
}

SetDisplayWidthAndHeightPatch_1_13C::PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_13C::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xDD1E
          ),
          sizeof(kJeOpcode)
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xD62E
          ),
          sizeof(kJeOpcode)
      );
    }
  }
}

} // namespace sgd2fr::patches::d2glide
