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

#include "glide3x_library_version_file_version.h"

#include <limits.h>
#include <windows.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/std/stdint.h>
#include <mdc/wchar_t/filew.h>
#include "../file/fixed_file_version.h"
#include "../glide3x_library.h"

static enum D2_Glide3xLibraryVersion SearchGlide3xLibraryVersionTable(
    const struct Mapi_FixedFileVersion* file_version
) {
  uint_least64_t file_version_as_value;

  file_version_as_value = Mapi_FixedFileVersion_ToValue(file_version);

  switch (file_version_as_value) {
    case MAPI_FIXED_FILE_VERSION_MERGE_VERSION_TO_VALUE(1, 4, 4, 21): {
      return D2_Glide3xLibraryVersion_kSven1_4_4_21;
    }

    case MAPI_FIXED_FILE_VERSION_MERGE_VERSION_TO_VALUE(1, 4, 6, 1): {
      return D2_Glide3xLibraryVersion_kSven1_4_6_1;
    }

    case MAPI_FIXED_FILE_VERSION_MERGE_VERSION_TO_VALUE(1, 4, 8, 3): {
      return D2_Glide3xLibraryVersion_kSven1_4_8_3;
    }

    case MAPI_FIXED_FILE_VERSION_MERGE_VERSION_TO_VALUE(3, 10, 0, 658): {
      return D2_Glide3xLibraryVersion_kNGlide3_10_0_658;
    }

    default: {
      Mdc_Error_ExitOnGeneralError(
          L"Error",
          L"Could not map the file version %u.%u.%u.%u to a known "
              L"glide3x version.",
          __FILEW__,
          __LINE__,
          file_version->major_high,
          file_version->major_low,
          file_version->minor_high,
          file_version->minor_low
      );
    }
  }
}

/**
 * External
 */

enum D2_Glide3xLibraryVersion GuessGlide3xLibraryVersion(void) {
  enum D2_Glide3xLibraryVersion glide3x_library_version;

  const VS_FIXEDFILEINFO* fixed_file_info;
  struct Mapi_FixedFileVersion file_version;

  fixed_file_info = D2_Glide3xLibrary_QueryFixedFileInfo();

  file_version = Mapi_FixedFileVersion_InitFromVersion(
      HIWORD(fixed_file_info->dwFileVersionMS),
      LOWORD(fixed_file_info->dwFileVersionMS),
      HIWORD(fixed_file_info->dwFileVersionLS),
      LOWORD(fixed_file_info->dwFileVersionLS)
  );

  glide3x_library_version = SearchGlide3xLibraryVersionTable(&file_version);

  Mapi_FixedFileVersion_Deinit(&file_version);

  return glide3x_library_version;
}
