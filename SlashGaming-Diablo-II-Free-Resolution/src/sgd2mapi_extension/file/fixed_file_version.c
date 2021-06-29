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

#include "fixed_file_version.h"

/**
 * External
 */

struct Mapi_FixedFileVersion Mapi_FixedFileVersion_InitFromVersion(
    WORD major_high,
    WORD major_low,
    WORD minor_high,
    WORD minor_low
) {
  struct Mapi_FixedFileVersion fixed_file_version;

  fixed_file_version.major_high = major_high;
  fixed_file_version.major_low = major_low;
  fixed_file_version.minor_high = minor_high;
  fixed_file_version.minor_low = minor_low;

  return fixed_file_version;
}

void Mapi_FixedFileVersion_Deinit(
    struct Mapi_FixedFileVersion* fixed_file_version
) {
}

uint_least64_t Mapi_FixedFileVersion_ToValue(
    const struct Mapi_FixedFileVersion* fixed_file_version
) {
  return MAPI_FIXED_FILE_VERSION_MERGE_VERSION_TO_VALUE(
      fixed_file_version->major_high,
      fixed_file_version->major_low,
      fixed_file_version->minor_high,
      fixed_file_version->minor_low
  );
}
