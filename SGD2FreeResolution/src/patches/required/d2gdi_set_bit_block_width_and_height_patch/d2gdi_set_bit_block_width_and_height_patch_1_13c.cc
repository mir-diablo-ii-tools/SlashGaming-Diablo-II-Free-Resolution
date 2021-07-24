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

#include "d2gdi_set_bit_block_width_and_height_patch_1_13c.hpp"

#include <stddef.h>

extern "C" {

void __cdecl
D2GDI_SetBitBlockWidthAndHeightPatch_1_13C_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace d2gdi {

SetBitBlockWidthAndHeightPatch_1_13C::SetBitBlockWidthAndHeightPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2GDI_SetBitBlockWidthAndHeightPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);
}

PatchAddressAndSize
SetBitBlockWidthAndHeightPatch_1_13C::GetPatchAddressAndSize01() {
  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::game_version::k1_11: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::default_library::kD2GDI,
              0x6214
          ),
          0x623F - 0x6214
      );
    }

    case ::d2::game_version::k1_11B: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::default_library::kD2GDI,
              0x6F24
          ),
          0x6F4F - 0x6F24
      );
    }

    case ::d2::game_version::k1_12A: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::default_library::kD2GDI,
              0x6284
          ),
          0x62AF - 0x6284
      );
    }

    case ::d2::game_version::k1_13ABeta: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::default_library::kD2GDI,
              0x62E4
          ),
          0x630F - 0x62E4
      );
    }

    case ::d2::game_version::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::default_library::kD2GDI,
              0x6D34
          ),
          0x6D5F - 0x6D34
      );
    }

    case ::d2::game_version::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::default_library::kD2GDI,
              0x7B84
          ),
          0x7BAF - 0x7B84
      );
    }
  }
}

} // namespace d2gdi
} // namespace sgd2fr
