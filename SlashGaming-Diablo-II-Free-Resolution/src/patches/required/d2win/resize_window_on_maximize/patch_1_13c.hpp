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

#ifndef SGD2FR_PATCHES_REQUIRED_D2WIN_RESIZE_WINDOW_ON_MAXIMIZE_PATCH_1_13C_HPP_
#define SGD2FR_PATCHES_REQUIRED_D2WIN_RESIZE_WINDOW_ON_MAXIMIZE_PATCH_1_13C_HPP_

#include <sgd2mapi.hpp>
#include "../../../../helper/abstract_version_patch.hpp"
#include "../../../../helper/patch_address_and_size.hpp"

namespace sgd2fr {
namespace d2win {

class ResizeWindowOnMaximizePatch_1_13C
    : public AbstractVersionPatch {
 public:
  ResizeWindowOnMaximizePatch_1_13C();

 private:
  enum {
    kPatchesCount = 2
  };

  ::mapi::GamePatch patches_[kPatchesCount];

  static PatchAddressAndSize GetPatchAddressAndSize01();
  static PatchAddressAndSize GetPatchAddressAndSize02();
};

} // namespace d2win
} // namespace sgd2fr

#endif // SGD2FR_PATCHES_REQUIRED_D2WIN_RESIZE_WINDOW_ON_MAXIMIZE_PATCH_1_13C_HPP_
