/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2023  Mir Drualga
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

#include "patch_1_09d.hpp"

#include <stddef.h>

extern "C" {

void __cdecl
D2Client_DrawScreenBackgroundPatch_1_09D_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace d2client {

DrawScreenBackgroundPatch_1_09D::DrawScreenBackgroundPatch_1_09D()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  // Draw the new screen background.
  PatchAddressAndSize patch_address_and_size_01 = GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_DrawScreenBackgroundPatch_1_09D_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  // Disable the left screen background.
  PatchAddressAndSize patch_address_and_size_02 = GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameNopPatch(
      patch_address_and_size_02.first,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);

  // Disable the right screen background.
  PatchAddressAndSize patch_address_and_size_03 = GetPatchAddressAndSize03();
  ::mapi::GamePatch patch_03 = ::mapi::GamePatch::MakeGameNopPatch(
      patch_address_and_size_03.first,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);
}

PatchAddressAndSize
DrawScreenBackgroundPatch_1_09D::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Start a game with any character.
  * 2. Search for the locations where the 7-bit null-terminated ASCII
  *    text "ACT%d" is used.
  * 3. Breakpoint in the function and follow the code to the return.
  * 4. The return address is the patch location.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x8696B
          ),
          0x86970 - 0x8696B
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x81F08
          ),
          0x81F0D - 0x81F08
      );
    }

    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x90216
          ),
          0x9021B - 0x90216
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xC3AA6
          ),
          0xC3AAB - 0xC3AA6
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x1D4A6
          ),
          0x1D4AB - 0x1D4A6
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x5264D
          ),
          0x52652 - 0x5264D
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x56FAF
          ),
          0x56FB4 - 0x56FAF
      );
    }
  }
}

PatchAddressAndSize
DrawScreenBackgroundPatch_1_09D::GetPatchAddressAndSize02() {
  /*
  * How to find patch locations:
  * 1. Search for the locations where the 7-bit null-terminated ASCII
  *    text "Panel\800BorderFrame" is used. There will be two
  *    addresses.
  * 2. Determine which one of the addresses is used for the left
  *    screen.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x58F1B
          ),
          0x58FB1 - 0x58F1B
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x5F4EB
          ),
          0x5F586 - 0x5F4EB
      );
    }

    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x8218D
          ),
          0x82227 - 0x8218D
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x271ED
          ),
          0x27287 - 0x271ED
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x6D2DD
          ),
          0x6D377 - 0x6D2DD
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x94B0C
          ),
          0x94BB6 - 0x94B0C
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x9865E
          ),
          0x986FC - 0x9865E
      );
    }
  }
}

PatchAddressAndSize
DrawScreenBackgroundPatch_1_09D::GetPatchAddressAndSize03() {
  /*
  * How to find patch locations:
  * 1. Search for the locations where the 7-bit null-terminated ASCII
  *    text "Panel\800BorderFrame" is used. There will be two
  *    addresses.
  * 2. Determine which one of the addresses is used for the right
  *    screen.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x58FF0
          ),
          0x5909C - 0x58FF0
      );
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x5F5C0
          ),
          0x5F66C - 0x5F5C0
      );
    }

    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x82094
          ),
          0x8214D - 0x82094
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x270F1
          ),
          0x271AE - 0x270F1
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x6D1E1
          ),
          0x6D29E - 0x6D1E1
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x94BF1
          ),
          0x94CA4 - 0x94BF1
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x98733
          ),
          0x987DA - 0x98733
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
