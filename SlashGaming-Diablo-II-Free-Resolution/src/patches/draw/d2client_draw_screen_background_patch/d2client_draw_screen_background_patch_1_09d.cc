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

#include "d2client_draw_screen_background_patch_1_09d.hpp"

#include "d2client_draw_screen_background.hpp"

extern "C" {

void __cdecl
D2Client_DrawScreenBackgroundPatch_1_09D_InterceptionFunc01();

} // extern "C"

namespace sgd2fr::patches::d2client {

DrawScreenBackgroundPatch_1_09D::DrawScreenBackgroundPatch_1_09D()
    : patches_(MakePatches()) {
}

void DrawScreenBackgroundPatch_1_09D::Apply() {
  for (auto& patch : this->patches_) {
    patch.Apply();
  }
}

void DrawScreenBackgroundPatch_1_09D::Remove() {
  for (auto& patch : this->patches_) {
    patch.Remove();
  }
}

std::vector<mapi::GamePatch>
DrawScreenBackgroundPatch_1_09D::MakePatches() {
  std::vector<mapi::GamePatch> patches;

  ::d2::GameVersion running_game_version = d2::game_version::GetRunning();

  // Draw the new screen background.
  PatchAddressAndSize patch_address_and_size_01 = GetPatchAddressAndSize01();
  patches.push_back(
      mapi::GamePatch::MakeGameBranchPatch(
          patch_address_and_size_01.first,
          mapi::BranchType::kCall,
          &D2Client_DrawScreenBackgroundPatch_1_09D_InterceptionFunc01,
          patch_address_and_size_01.second
      )
  );

  // Disable the left screen background.
  PatchAddressAndSize patch_address_and_size_02 = GetPatchAddressAndSize02();
  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          patch_address_and_size_02.first,
          patch_address_and_size_02.second
      )
  );

  // Disable the right screen background.
  PatchAddressAndSize patch_address_and_size_03 = GetPatchAddressAndSize03();
  patches.push_back(
      mapi::GamePatch::MakeGameNopPatch(
          patch_address_and_size_03.first,
          patch_address_and_size_03.second
      )
  );

  return patches;
}

DrawScreenBackgroundPatch_1_09D::PatchAddressAndSize
DrawScreenBackgroundPatch_1_09D::GetPatchAddressAndSize01() {
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

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
        ::mapi::GameAddress::FromOffset(
            ::d2::DefaultLibrary::kD2Client,
            0xC3AA6
        ),
        0xC3AAB - 0xC3AA6
      );
    }
  }
}

DrawScreenBackgroundPatch_1_09D::PatchAddressAndSize
DrawScreenBackgroundPatch_1_09D::GetPatchAddressAndSize02() {
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

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
        ::mapi::GameAddress::FromOffset(
            ::d2::DefaultLibrary::kD2Client,
            0x271ED
        ),
        0x27287 - 0x271ED
      );
    }
  }
}

DrawScreenBackgroundPatch_1_09D::PatchAddressAndSize
DrawScreenBackgroundPatch_1_09D::GetPatchAddressAndSize03() {
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

    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
        ::mapi::GameAddress::FromOffset(
            ::d2::DefaultLibrary::kD2Client,
            0x270F1
        ),
        0x271AE - 0x270F1
      );
    }
  }
}

} // namespace sgd2fr::patches::d2client
