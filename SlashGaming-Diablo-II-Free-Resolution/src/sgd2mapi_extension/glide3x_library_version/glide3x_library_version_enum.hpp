/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2021  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Modding API for C++. It
 * has been copied and retooled for reading glide3x.dll.
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

#ifndef SGD2FR_SGD2MAPI_EXTENSION_GLIDE3X_LIBRARY_GLIDE3X_LIBRARY_VERSION_ENUM_HPP_
#define SGD2FR_SGD2MAPI_EXTENSION_GLIDE3X_LIBRARY_GLIDE3X_LIBRARY_VERSION_ENUM_HPP_

#include "glide3x_library_version_enum.h"

namespace d2 {
namespace glide3x_library_version {

enum Glide3xLibraryVersion {
  kSven1_4_4_21 = ::D2_Glide3xLibraryVersion_kSven1_4_4_21,
  kSven1_4_6_1 = ::D2_Glide3xLibraryVersion_kSven1_4_6_1,
  kSven1_4_8_3 = ::D2_Glide3xLibraryVersion_kSven1_4_8_3,
  kNGlide3_10_0_658 = ::D2_Glide3xLibraryVersion_kNGlide3_10_0_658,
  kD2dx = ::D2_Glide3xLibraryVersion_kD2dx,
};

} // namespace glide3x_library_version

typedef glide3x_library_version::Glide3xLibraryVersion Glide3xLibraryVersion;

} // namespace d2

#endif /* SGD2FR_SGD2MAPI_EXTENSION_GLIDE3X_LIBRARY_GLIDE3X_LIBRARY_VERSION_ENUM_HPP_ */
