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

#ifndef SGD2FR_PATCHES_REQUIRED_GLIDE3X_GR_SST_WIN_OPEN_PATCH_HPP_
#define SGD2FR_PATCHES_REQUIRED_GLIDE3X_GR_SST_WIN_OPEN_PATCH_HPP_

#include "../../../../helper/abstract_multiversion_patch.hpp"
#include "../../../../helper/abstract_version_patch.hpp"
#include "patch_nglide_3_10_0_658.hpp"
#include "patch_sven_1_4_4_21.hpp"
#include "patch_sven_1_4_8_3.hpp"

namespace sgd2fr {
namespace glide3x {

class GrSstWinOpenPatch
    : public AbstractMultiversionPatch {
 public:
  GrSstWinOpenPatch();

 private:
  static bool IsApplicable();
  static AbstractVersionPatch* InitPatch();
};

} // namespace glide3x
} // namespace sgd2fr

#endif // SGD2FR_PATCHES_REQUIRED_GLIDE3X_GR_SST_WIN_OPEN_PATCH_HPP_
