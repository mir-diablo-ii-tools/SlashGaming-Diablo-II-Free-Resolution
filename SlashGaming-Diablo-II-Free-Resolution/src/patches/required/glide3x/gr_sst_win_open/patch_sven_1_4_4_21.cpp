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

#include "patch_sven_1_4_4_21.hpp"

#include <stddef.h>

#include "../../../../helper/glide3x_version.hpp"

extern "C" {

void __cdecl Glide3x_GrSstWinOpenPatch_Sven_1_4_4_21_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace glide3x {

GrSstWinOpenPatch_Sven_1_4_4_21::GrSstWinOpenPatch_Sven_1_4_4_21()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &Glide3x_GrSstWinOpenPatch_Sven_1_4_4_21_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);
}

PatchAddressAndSize
GrSstWinOpenPatch_Sven_1_4_4_21::GetPatchAddressAndSize01() {
  Glide3xVersion running_glide3x_version = glide3x_version::GetRunning();

  switch (running_glide3x_version) {
    case Glide3xVersion::kSven1_4_4_21: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              L"glide3x.dll",
              0xCBA9
          ),
          0xCBB0 - 0xCBA9
      );
    }

    case Glide3xVersion::kSven1_4_6_1: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              L"glide3x.dll",
              0xCAD5
          ),
          0xCADC - 0xCAD5
      );
    }
  }
}

} // namespace glide3x
} // namespace sgd2fr
