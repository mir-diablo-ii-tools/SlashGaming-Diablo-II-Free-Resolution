/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2022  Mir Drualga
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

#include "patch_1_13c.hpp"

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
D2Glide_SetDisplayWidthAndHeightPatch_1_13C_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace d2glide {
namespace {

static const uint8_t kShortJeByteOpcodes[] = {
    0x74
};

static const uint8_t k0x01Byte = 0x01;

} // namespace

SetDisplayWidthAndHeightPatch_1_13C::SetDisplayWidthAndHeightPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Glide_SetDisplayWidthAndHeightPatch_1_13C_InterceptionFunc01,
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
      kShortJeByteOpcodes,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);
}

PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_13C::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_11: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xC051
          ),
          0xC06A - 0xC051
      );
    }

    case ::d2::GameVersion::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x8CD1
          ),
          0x8CEA - 0x8CD1
      );
    }

    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xBD51
          ),
          0xBD6A - 0xBD51
      );
    }

    case ::d2::GameVersion::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x9411
          ),
          0x942A - 0x9411
      );
    }

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

    case ::d2::GameVersion::kLod1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x35CC0
          ),
          0x35CD9 - 0x35CC0
      );
    }

    case ::d2::GameVersion::kLod1_14B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1079B0
          ),
          0x1079C9 - 0x1079B0
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1075A0
          ),
          0x1075B9 - 0x1075A0
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x109C26
          ),
          0x109C3F - 0x109C26
      );
    }
  }
}

PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_13C::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_11: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xC075 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x8CF5 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xBD75 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x9435 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xDD15 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xD625 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::kLod1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x35CE4 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::kLod1_14B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1079D4 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1075C4 + 2
          ),
          sizeof(k0x01Byte)
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x109C4A + 2
          ),
          sizeof(k0x01Byte)
      );
    }
  }
}

PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_13C::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_11: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xC07E
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x8CFE
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xBD7E
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x943E
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xDD1E
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0xD62E
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::kLod1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x35CED
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::kLod1_14B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1079DD
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x1075CD
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Glide,
              0x109C53
          ),
          sizeof(kShortJeByteOpcodes)
      );
    }
  }
}

} // namespace d2glide
} // namespace sgd2fr
