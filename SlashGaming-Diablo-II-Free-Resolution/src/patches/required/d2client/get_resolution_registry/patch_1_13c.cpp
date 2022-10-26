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

extern "C" {

void __cdecl
D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01();

void __cdecl
D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc03();

void __cdecl
D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc04();

} // extern "C"

namespace sgd2fr {
namespace d2client {

GetResolutionRegistryPatch_1_13C::GetResolutionRegistryPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_02.first,
      ::mapi::BranchType::kCall,
      &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);

  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  ::mapi::GamePatch patch_03 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_03.first,
      ::mapi::BranchType::kCall,
      &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc03,
      patch_address_and_size_03.second
  );
  this->patches_[2].Swap(patch_03);

  PatchAddressAndSize patch_address_and_size_04 =
      GetPatchAddressAndSize04();
  ::mapi::GamePatch patch_04 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_04.first,
      ::mapi::BranchType::kCall,
      &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc04,
      patch_address_and_size_04.second
  );
  this->patches_[3].Swap(patch_04);
}

PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Search for the location of the 7-bit null-terminated ASCII text
  *    "Resolution". This text should be in a Read Only section.
  * 2. Search for the locations where "Resolution" is used. There will
  *    be 5 results.
  * 3. Choose the patch location with the matching interception shim.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x55CF6
          ),
          0x55D16 - 0x55CF6
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x44453
          ),
          0x44472 - 0x44453
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x454A3
          ),
          0x454C2 - 0x454A3
      );
    }
  }
}

PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize02() {
  /*
  * How to find patch locations:
  * 1. Search for the location of the 7-bit null-terminated ASCII text
  *    "Resolution". This text should be in a Read Only section.
  * 2. Search for the locations where "Resolution" is used. There will
  *    be 5 results.
  * 3. Choose the patch location with the matching interception shim.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x55CF6
          ),
          0x55D16 - 0x55CF6
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x65E46
          ),
          0x65E66 - 0x65E46
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xC40E6
          ),
          0xC4106 - 0xC40E6
      );
    }
  }
}

PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize03() {
  /*
  * How to find patch locations:
  * 1. Search for the location of the 7-bit null-terminated ASCII text
  *    "Resolution". This text should be in a Read Only section.
  * 2. Search for the locations where "Resolution" is used. There will
  *    be 5 results.
  * 3. Choose the patch location with the matching interception shim.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x56128
          ),
          0x56146 - 0x56128
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x66278
          ),
          0x66296 - 0x66278
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xC4518
          ),
          0xC4536 - 0xC4518
      );
    }
  }
}

PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize04() {
  /*
  * How to find patch locations:
  * 1. Search for the location of the 7-bit null-terminated ASCII text
  *    "Resolution". This text should be in a Read Only section.
  * 2. Search for the locations where "Resolution" is used. There will
  *    be 5 results.
  * 3. Choose the patch location with the matching interception shim.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x67EC0
          ),
          0x67EE0 - 0x67EC0
      );
    }

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xAF950
          ),
          0xAF970 - 0xAF950
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x85F60
          ),
          0x85F80 - 0x85F60
      );
    }
  }
}

} // namespace d2client
} // namespace sgd2fr
