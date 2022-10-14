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

#include "d2client_set_tile_culling_bound_patch_1_11.hpp"

#include <stddef.h>

#include <sgd2mapi.hpp>

#include "../../../helper/abstract_version_patch.hpp"
#include "../../../helper/patch_address_and_size.hpp"
#include "d2client_set_tile_culling_bound_patch_1_11_shim.h"

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

SetTileCullingBoundPatch_1_11::SetTileCullingBoundPatch_1_11()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  GamePatch patch_01 = GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      BranchType::kJump,
      &D2Client_SetTileCullingBoundPatch_1_11_InterceptionFunc01,
      patch_address_and_size_01.second);
  this->patches_[0].Swap(patch_01);
}

PatchAddressAndSize SetTileCullingBoundPatch_1_11::GetPatchAddressAndSize01() {
  /*
   * How to find patch locations:
   * 1. Start a game with any character.
   * 2. Search for the address of the string "Perspective" in
   *    D2Client.dll.
   * 3. Search for all usages of the string "Perspective". If there is
   *    more than one string, try all of them.
   * 3. Go to the code location where the string is used.
   * 4. Enter the first called function that is in D2Client.dll
   *    address space. That is the target address.
   */

  GameVersion running_game_version = GetRunning();

  ptrdiff_t offset;
  size_t size;

  switch (running_game_version) {
    case GameVersion::k1_11: {
      offset = 0x5B560;
      size = 0x5B565 - 0x5B560;
      break;
    }

    case GameVersion::k1_11B: {
      offset = 0x927A0;
      size = 0x927A5 - 0x927A0;
      break;
    }

    case GameVersion::k1_12A: {
      offset = 0xBA990;
      size = 0xBA995 - 0xBA990;
      break;
    }

    case GameVersion::k1_13ABeta: {
      offset = 0x3F490;
      size = 0x3F495 - 0x3F490;
      break;
    }

    case GameVersion::k1_13C: {
      offset = 0x8A4D0;
      size = 0x8A4D5 - 0x8A4D0;
      break;
    }

    case GameVersion::k1_13D: {
      offset = 0xB5330;
      size = 0xB5335 - 0xB5330;
      break;
    }

    case GameVersion::kLod1_14A: {
      offset = 0xB5330;
      size = 0xB5335 - 0xB5330;
      break;
    }
  }

  return PatchAddressAndSize(
      GameAddress::FromOffset(DefaultLibrary::kD2Client, offset), size);
}

}  // namespace sgd2fr
}  // namespace d2client
