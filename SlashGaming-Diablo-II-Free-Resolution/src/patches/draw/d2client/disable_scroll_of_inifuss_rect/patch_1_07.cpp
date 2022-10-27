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

#include "patch_1_07.hpp"

#include <stddef.h>

namespace sgd2fr {
namespace d2client {

DisableScrollOfInifussRectPatch_1_07::DisableScrollOfInifussRectPatch_1_07()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  // Disable the black rectangle in the Scoll of Inifuss screen.
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameNopPatch(
      patch_address_and_size_01.first,
      patch_address_and_size_01.second);

  this->patches_[0].Swap(patch_01);
}

PatchAddressAndSize
DisableScrollOfInifussRectPatch_1_07::GetPatchAddressAndSize01() {
  /*
   * How to find patch locations:
   * 1. Search for the locations where the 7-bit null-terminated ASCII
   *    text "%s\UI\MENU\scroin" is used. This text should be in a Read
   *    Only section.
   * 2. Scroll up to find a call to D2GFX.DrawRectangle. Patch out that
   *    function call.
   */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_07Beta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x87D9C),
              0x87DC9 - 0x87D9C);
    }

    case ::d2::GameVersion::k1_07: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x889EC),
              0x88A19 - 0x889EC);
    }

    case ::d2::GameVersion::k1_08: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x83B2C),
              0x83B59 - 0x83B2C);
    }

    case ::d2::GameVersion::k1_09:
    case ::d2::GameVersion::k1_09B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x8407C),
              0x840A9 - 0x8407C);
    }

    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x8330C),
              0x83339 - 0x8330C);
    }

    case ::d2::GameVersion::k1_10Beta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x7B73C),
              0x7B769 - 0x7B73C);
    }

    case ::d2::GameVersion::k1_10SBeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x7BA4C),
              0x7BA79 - 0x7BA4C);
    }

    case ::d2::GameVersion::k1_10: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x7E9EC),
              0x7EA19 - 0x7E9EC);
    }

    case ::d2::GameVersion::k1_11: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x9333D),
              0x9336A - 0x9333D);
    }

    case ::d2::GameVersion::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x1597D),
              0x159AA - 0x1597D);
    }

    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x70FBD),
              0x70FEA - 0x70FBD);
    }

    case ::d2::GameVersion::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x56D4D),
              0x56D7A - 0x56D4D);
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x7C38D),
              0x7C3BA - 0x7C38D);
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x7516D),
              0x7519A - 0x7516D);
    }

    case ::d2::GameVersion::kClassic1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0xA6E5D),
              0xA6E8A - 0xA6E5D);
    }

    case ::d2::GameVersion::kLod1_14A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0xA6F3D),
              0xA6F6A - 0xA6F3D);
    }

    case ::d2::GameVersion::kClassic1_14B:
    case ::d2::GameVersion::kClassic1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x8DDFD),
              0x8DE2A - 0x8DDFD);
    }

    case ::d2::GameVersion::kLod1_14B:
    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x9C20D),
              0x9C23A - 0x9C20D);
    }

    case ::d2::GameVersion::kClassic1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x91280),
              0x912AD - 0x91280);
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client, 0x9FA20),
              0x9FA4D - 0x9FA20);
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
