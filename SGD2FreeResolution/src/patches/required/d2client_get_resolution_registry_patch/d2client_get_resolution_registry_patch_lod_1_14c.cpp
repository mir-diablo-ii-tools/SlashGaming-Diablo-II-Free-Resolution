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

#include "d2client_get_resolution_registry_patch_lod_1_14c.hpp"

#include <stddef.h>

extern "C" {

void __cdecl
D2Client_GetResolutionRegistryPatch_Lod1_14C_InterceptionFunc01();

void __cdecl
D2Client_GetResolutionRegistryPatch_Lod1_14C_InterceptionFunc02();

} // extern "C"

namespace sgd2fr {
namespace d2client {

GetResolutionRegistryPatch_Lod1_14C::GetResolutionRegistryPatch_Lod1_14C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_GetResolutionRegistryPatch_Lod1_14C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_02.first,
      ::mapi::BranchType::kCall,
      &D2Client_GetResolutionRegistryPatch_Lod1_14C_InterceptionFunc02,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);
}

PatchAddressAndSize
GetResolutionRegistryPatch_Lod1_14C::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Search for the location of the 7-bit null-terminated ASCII text
  *    "Resolution". This text should be in a Read Only section.
  * 2. Search for the locations where "Resolution" is used. There will
  *    be 3 results.
  * 3. Choose the patch location with the matching interception shim.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x78ED0
          ),
          0x78F00 - 0x78ED0
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x7D0E0
          ),
          0x7D110 - 0x7D0E0
      );
    }
  }
}

PatchAddressAndSize
GetResolutionRegistryPatch_Lod1_14C::GetPatchAddressAndSize02() {
  /*
  * How to find patch locations:
  * 1. Search for the location of the 7-bit null-terminated ASCII text
  *    "Resolution". This text should be in a Read Only section.
  * 2. Search for the locations where "Resolution" is used. There will
  *    be 3 results.
  * 3. Choose the patch location with the matching interception shim.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x7AFE4
          ),
          0x7B00E - 0x7AFE4
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x7F1D7
          ),
          0x7F201 - 0x7F1D7
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
