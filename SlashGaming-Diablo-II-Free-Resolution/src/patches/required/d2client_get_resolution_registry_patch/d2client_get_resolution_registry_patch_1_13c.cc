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

#include "d2client_get_resolution_registry_patch_1_13c.hpp"

extern "C" {

void __cdecl
D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01();

void __cdecl
D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc03();

void __cdecl
D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc04();

} // extern "C"

namespace sgd2fr::patches::d2client {

GetResolutionRegistryPatch_1_13C::GetResolutionRegistryPatch_1_13C()
  : patches_(MakePatches()) {
}

void GetResolutionRegistryPatch_1_13C::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void GetResolutionRegistryPatch_1_13C::Remove() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

std::vector<mapi::GamePatch>
GetResolutionRegistryPatch_1_13C::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_01.first,
          mapi::BranchType::kCall,
          &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01,
          patch_address_and_size_01.second
      )
  );

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_02.first,
          mapi::BranchType::kCall,
          &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01,
          patch_address_and_size_02.second
      )
  );

  PatchAddressAndSize patch_address_and_size_03 =
      GetPatchAddressAndSize03();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_03.first,
          mapi::BranchType::kCall,
          &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc03,
          patch_address_and_size_03.second
      )
  );

  PatchAddressAndSize patch_address_and_size_04 =
      GetPatchAddressAndSize04();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_04.first,
          mapi::BranchType::kCall,
          &D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc04,
          patch_address_and_size_04.second
      )
  );

  return patches;
}

GetResolutionRegistryPatch_1_13C::PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x44453
          ),
          0x44472 - 0x44453
      );
    }
  }
}

GetResolutionRegistryPatch_1_13C::PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x65E46
          ),
          0x65E66 - 0x65E46
      );
    }
  }
}

GetResolutionRegistryPatch_1_13C::PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x66278
          ),
          0x66296 - 0x66278
      );
    }
  }
}

GetResolutionRegistryPatch_1_13C::PatchAddressAndSize
GetResolutionRegistryPatch_1_13C::GetPatchAddressAndSize04() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0xAF950
          ),
          0xAF970 - 0xAF950
      );
    }
  }
}

} // namespace sgd2fr::patches::d2client
