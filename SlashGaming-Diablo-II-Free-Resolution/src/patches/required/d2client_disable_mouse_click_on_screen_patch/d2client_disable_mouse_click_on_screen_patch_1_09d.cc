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

#include "d2client_disable_mouse_click_on_screen_patch_1_09d.hpp"

namespace sgd2fr::patches::d2client {

DisableMouseClickOnScreenPatch_1_09D::DisableMouseClickOnScreenPatch_1_09D()
  : patches_(MakePatches()) {
}

void DisableMouseClickOnScreenPatch_1_09D::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void DisableMouseClickOnScreenPatch_1_09D::Remove() {
  for (auto& patch : this->patches_) {
    patch.Remove();
  }
}

std::vector<mapi::GamePatch>
DisableMouseClickOnScreenPatch_1_09D::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  // Disable left screen click-through.
  PatchAddressAndSize patch_address_and_size_01 = GetPatchAddressAndSize01();
  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          patch_address_and_size_01.first,
          patch_address_and_size_01.second
      )
  );

  // Disable left screen click-through while character is moving.
  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          patch_address_and_size_02.first,
          patch_address_and_size_02.second
      )
  );

  // Disable right screen click-through.
  PatchAddressAndSize patch_address_and_size_03 = GetPatchAddressAndSize03();
  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          patch_address_and_size_03.first,
          patch_address_and_size_03.second
      )
  );

  return patches;
}

DisableMouseClickOnScreenPatch_1_09D::PatchAddressAndSize
DisableMouseClickOnScreenPatch_1_09D::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x2AB1A
          ),
          0x2AB24 - 0x2AB1A
      );
    }
  }
}

DisableMouseClickOnScreenPatch_1_09D::PatchAddressAndSize
DisableMouseClickOnScreenPatch_1_09D::GetPatchAddressAndSize02() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x2AD1A
          ),
          0x2AD24 - 0x2AD1A
      );
    }
  }
}

DisableMouseClickOnScreenPatch_1_09D::PatchAddressAndSize
DisableMouseClickOnScreenPatch_1_09D::GetPatchAddressAndSize03() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_09D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2Client,
              0x40873
          ),
          0x40881 - 0x40873
      );
    }
  }
}

} // namespace sgd2fr::patches::d2client
