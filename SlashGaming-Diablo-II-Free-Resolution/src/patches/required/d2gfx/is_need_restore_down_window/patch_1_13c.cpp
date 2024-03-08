/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2024  Mir Drualga
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

#include <mdc/std/stdint.h>

extern "C" {

void __cdecl
D2GFX_IsNeedRestoreDownWindowPatch_1_13C_InterceptionFunc01();

} // extern "C"

namespace sgd2fr {
namespace d2gfx {
namespace {

static const uint8_t kJeOpcodes[] = {
    0x0F, 0x84,
};

} // namespace

IsNeedRestoreDownWindowPatch_1_13C::IsNeedRestoreDownWindowPatch_1_13C()
    : AbstractVersionPatch(this->patches_, kPatchesCount) {
  PatchAddressAndSize patch_address_and_size_01 =
      GetPatchAddressAndSize01();
  ::mapi::GamePatch patch_01 = ::mapi::GamePatch::MakeGameBranchPatch(
      patch_address_and_size_01.first,
      ::mapi::BranchType::kCall,
      &D2GFX_IsNeedRestoreDownWindowPatch_1_13C_InterceptionFunc01,
      patch_address_and_size_01.second
  );
  this->patches_[0].Swap(patch_01);

  PatchAddressAndSize patch_address_and_size_02 =
      GetPatchAddressAndSize02();
  ::mapi::GamePatch patch_02 = ::mapi::GamePatch::MakeGameBufferPatch(
      patch_address_and_size_02.first,
      kJeOpcodes,
      patch_address_and_size_02.second
  );
  this->patches_[1].Swap(patch_02);
}

PatchAddressAndSize
IsNeedRestoreDownWindowPatch_1_13C::GetPatchAddressAndSize01() {
  /*
  * How to find patch locations:
  * 1. Start the game in windowed GDI mode.
  * 2. Maximize the game window, if the game window is not maximized.
  * 3. Go to User32.dll's SystemParametersInfoA function.
  * 4. Set a code breakpoint at the start of the function.
  * 5. Restore Down the game window.
  * 6. The breakpoint will trigger. Step over the code until the
  *    function returns.
  * 7. Scroll up to find the patch location. A call to User32.dll's
  *    GetClientRect should be nearby.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0x811B
          ),
          0x815A - 0x811B
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0xB22B
          ),
          0xB26A - 0xB22B
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0xF31CE
          ),
          0xF3209 - 0xF31CE
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0xF5C0F
          ),
          0xF5C45 - 0xF5C0F
      );
    }
  }
}

PatchAddressAndSize
IsNeedRestoreDownWindowPatch_1_13C::GetPatchAddressAndSize02() {
  /*
  * How to find patch locations:
  * 1. Go to User32.dll's SystemParametersInfoA function.
  * 2. Set a code breakpoint at the start of the function.
  * 3. Maximize the game window, if the game window is not maximized
  *    and then Restore Down the game window.
  * 4. The breakpoint will trigger. Step over the code until the
  *    function returns.
  * 5. Scroll up to find the patch location. A call to User32.dll's
  *    GetClientRect should be nearby.
  */

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_13C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0x815A
          ),
          sizeof(kJeOpcodes)
      );
    }

    case ::d2::GameVersion::k1_13D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0xB26A
          ),
          sizeof(kJeOpcodes)
      );
    }

    case ::d2::GameVersion::kLod1_14C: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0xF3209
          ),
          sizeof(kJeOpcodes)
      );
    }

    case ::d2::GameVersion::kLod1_14D: {
      return PatchAddressAndSize(
          ::mapi::GameAddress::FromOffset(
              ::d2::DefaultLibrary::kD2GFX,
              0xF5C45
          ),
          sizeof(kJeOpcodes)
      );
    }
  }
}

} // namespace d2gfx
} // namespace sgd2fr
