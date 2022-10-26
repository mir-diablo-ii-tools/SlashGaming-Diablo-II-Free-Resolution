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
*    "Failed to create D3D device!" is used.
* 2. Scroll up until values 640, 480, 800, and 600 are seen.
*/

extern "C" {

void __cdecl
D2Direct3D_SetDisplayWidthAndHeightPatch_1_13C_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace d2direct3d {
namespace {

static const uint8_t kShortJneByteOpcodes[] = {
    0x75,
};

enum {
  kShortJneByteOpcodesCount = sizeof(kShortJneByteOpcodes)
      / sizeof(kShortJneByteOpcodes[0])
};

static const uint8_t kShortJmpByteOpcodes[] = {
    0xEB,
};

enum {
  kShortJmpByteOpcodesCount = sizeof(kShortJmpByteOpcodes)
      / sizeof(kShortJmpByteOpcodes[0])
};

} // namespace

SetDisplayWidthAndHeightPatch_1_13C::SetDisplayWidthAndHeightPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patches_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Direct3D_SetDisplayWidthAndHeightPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patches_01);

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patches_02 = ::mapi::GamePatch::MakeGameBufferPatch(
      patch_address_and_size_02.first,
      kShortJneByteOpcodes,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patches_02);

  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  ::mapi::GamePatch patches_03 = ::mapi::GamePatch::MakeGameBufferPatch(
      patch_address_and_size_03.first,
      kShortJmpByteOpcodes,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patches_03);
}

PatchAddressAndSize
SetDisplayWidthAndHeightPatch_1_13C::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_11: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x8F14
          ),
          0x8F42 - 0x8F14
      );
    }

    case ::d2::GameVersion::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x9504
          ),
          0x9532 - 0x9504
      );
    }

    case ::d2::GameVersion::k1_12A:
    case ::d2::GameVersion::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xFCD4
          ),
          0xFD02 - 0xFCD4
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xB9A4
          ),
          0xB9D2 - 0xB9A4
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xBE64
          ),
          0xBE92 - 0xBE64
      );
    }

    case ::d2::GameVersion::kLod1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x11A6F8
          ),
          0x11A726 - 0x11A6F8
      );
    }

    case ::d2::GameVersion::kLod1_14B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B62C8
          ),
          0x2B62F6 - 0x2B62C8
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B5EB8
          ),
          0x2B5EE6 - 0x2B5EB8
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B500B
          ),
          0x2B5039 - 0x2B500B
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
              ::d2::DefaultLibrary::kD2Direct3D,
              0x8F42
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x9532
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_12A:
    case ::d2::GameVersion::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xFD02
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xB9D2
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xBE92
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x11A726
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B62F6
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B5EE6
          ),
          kShortJneByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B5039
          ),
          kShortJneByteOpcodesCount
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
              ::d2::DefaultLibrary::kD2Direct3D,
              0x8F4D
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x953D
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_12A:
    case ::d2::GameVersion::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xFD0D
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xB9DD
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0xBE9D
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x11A731
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B6301
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B5EF1
          ),
          kShortJmpByteOpcodesCount
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Direct3D,
              0x2B5044
          ),
          kShortJmpByteOpcodesCount
      );
    }
  }
}

} // namespace d2direct3d
} // namespace sgd2fr
