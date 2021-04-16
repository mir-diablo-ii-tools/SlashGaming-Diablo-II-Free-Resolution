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

#include <stddef.h>

#include <mdc/std/stdint.h>

/*
* How to find patch locations:
* 1. Search for the locations where the text
*    "Opening Glide window failed!" is used.
* 2. Scroll up until values 640, 480, 800, and 600 are seen.
*/

extern "C" {

void __cdecl
D2Glide_SetDisplayWidthAndHeightPatch_1_09D_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace d2glide {
namespace {

static const uint8_t kShortJneByteOpcodes[] = { 
    0x75
};

static const uint8_t k0x01Byte = 0x01;

} // namespace

SetDisplayWidthAndHeightPatch_1_09D::SetDisplayWidthAndHeightPatch_1_09D()
    : patches_() {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Glide_SetDisplayWidthAndHeightPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBufferPatch(
      patch_address_and_size_02.first,
      &k0x01Byte,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);

  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  ::mapi::GamePatch patch_03 = ::mapi::GamePatch::MakeGameBufferPatch(
      patch_address_and_size_03.first,
      kShortJneByteOpcodes,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);
}

void SetDisplayWidthAndHeightPatch_1_09D::Apply() {
  for (size_t i = 0; i < kPatchesCount; i += 1) {
    this->patches_[i].Apply();
  }
}

void SetDisplayWidthAndHeightPatch_1_09D::Remove() {
  for (size_t i = kPatchesCount - 1; (i + 1) > 0; i -= 1) {
    this->patches_[i].Remove();
  }
}

PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_09D::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_07Beta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1B3B
          ),
          0x1B4F - 0x1B3B
      );
    }

    case ::d2::GameVersion::k1_07:
    case ::d2::GameVersion::k1_08:
    case ::d2::GameVersion::k1_09:
    case ::d2::GameVersion::k1_09B:
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1B8B
          ),
          0x1B9F - 0x1B8B
      );
    }

    case ::d2::GameVersion::k1_10Beta:
    case ::d2::GameVersion::k1_10SBeta:
    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1B96
          ),
          0x1BA5 - 0x1B96
      );
    }
  }
}

PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_09D::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_07Beta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1B66 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::k1_07:
    case ::d2::GameVersion::k1_08:
    case ::d2::GameVersion::k1_09:
    case ::d2::GameVersion::k1_09B:
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1BB6 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::k1_10Beta:
    case ::d2::GameVersion::k1_10SBeta:
    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1BC1 + 2
          ),
          sizeof(k0x01Byte)
      );
    }
  }
}

PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_09D::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_07Beta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1B69
          ),
          sizeof(kShortJneByteOpcodes)
      );
    }

    case ::d2::GameVersion::k1_07:
    case ::d2::GameVersion::k1_08:
    case ::d2::GameVersion::k1_09:
    case ::d2::GameVersion::k1_09B:
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1BB9
          ),
          sizeof(kShortJneByteOpcodes)
      );
    }

    case ::d2::GameVersion::k1_10Beta:
    case ::d2::GameVersion::k1_10SBeta:
    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1BC4
          ),
          sizeof(kShortJneByteOpcodes)
      );
    }
  }
}

} // namespace d2glide
} // namespace sgd2fr
