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

#include "patch_1_07.hpp"

#include <stddef.h>

#include <sgd2mapi.hpp>

#include "../../../../helper/abstract_version_patch.hpp"
#include "../../../../helper/patch_address_and_size.hpp"
#include "patch_1_07_shim.h"

namespace sgd2fr {
namespace d2client {
namespace {

using ::d2::DefaultLibrary;
using ::d2::GameVersion;
using ::d2::game_version::GetRunning;
using ::mapi::BranchType;
using ::mapi::GameAddress;
using ::mapi::GamePatch;
using ::sgd2fr::PatchAddressAndSize;

}  // namespace

SetTileCullingBoundPatch_1_07::SetTileCullingBoundPatch_1_07()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  GamePatch patch_01 = GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      BranchType::kJump,
      &D2Client_SetTileCullingBoundPatch_1_07_InterceptionFunc01,
      patch_address_and_size_01.second);
  this->patches_[0].Swap(patch_01);
}

PatchAddressAndSize SetTileCullingBoundPatch_1_07::GetPatchAddressAndSize01() {
  /*
   * How to find patch locations:
   * 1. Start a game with any character.
   * 2. Search for the address of the string "Perspective" in
   *    D2Client.dll.
   * 3. Search for all usages of the string "Perspective". There will
   *    be more than one. Choose the one surrounded by other text that
   *    is related to the Video Options.
   * 3. Go to the code location where the string is used.
   * 4. Enter the first called function that is in D2Client.dll
   *    address space. That is the target address.
   */

  GameVersion running_game_version = GetRunning();

  ptrdiff_t offset;
  size_t size;

  switch (running_game_version) {
    case GameVersion::k1_07Beta: {
      offset = 0x15EE0;
      size = 0x15EE5 - 0x15EE0;
      break;
    }

    case GameVersion::k1_07: {
      offset = 0x165C0;
      size = 0x165C5 - 0x165C0;
      break;
    }

    case GameVersion::k1_08: {
      offset = 0x15E70;
      size = 0x15E75 - 0x15E70;
      break;
    }

    case GameVersion::k1_09:
    case GameVersion::k1_09B: {
      offset = 0x16010;
      size = 0x16015 - 0x16010;
      break;
    }

    case GameVersion::k1_09D: {
      offset = 0x16000;
      size = 0x16005 - 0x16000;
      break;
    }

    case GameVersion::k1_10Beta: {
      offset = 0x16CE0;
      size = 0x16CE5 - 0x16CE0;
      break;
    }

    case GameVersion::k1_10SBeta: {
      offset = 0x16C80;
      size = 0x16C85 - 0x16C80;
      break;
    }

    case GameVersion::k1_10: {
      offset = 0x17100;
      size = 0x17105 - 0x17100;
      break;
    }

    case GameVersion::kClassic1_14A: {
      offset = 0x4C7F0;
      size = 0x4C7F5 - 0x4C7F0;
      break;
    }

    case GameVersion::kLod1_14A: {
      offset = 0x4C8D0;
      size = 0x4C8D5 - 0x4C8D0;
      break;
    }

    case GameVersion::kClassic1_14B:
    case GameVersion::kClassic1_14C: {
      offset = 0x63910;
      size = 0x63915 - 0x63910;
      break;
    }

    case GameVersion::kLod1_14B:
    case GameVersion::kLod1_14C: {
      offset = 0x71D30;
      size = 0x71D35 - 0x71D30;
      break;
    }

    case GameVersion::kClassic1_14D: {
      offset = 0x67850;
      size = 0x67855 - 0x67850;
      break;
    }

    case GameVersion::kLod1_14D: {
      offset = 0x76000;
      size = 0x76005 - 0x76000;
      break;
    }
  }

  return PatchAddressAndSize(
      GameAddress::FromOffset(DefaultLibrary::kD2Client, offset), size);
}

}  // namespace sgd2fr
}  // namespace d2client
