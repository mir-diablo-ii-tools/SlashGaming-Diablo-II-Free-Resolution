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

#include "glide3x_library.h"

#include "file/file_version_info.h"

#define GLIDE3X_LIBRARY_PATH L"glide3x.dll"

static const wchar_t* const kGlide3xLibraryPath = GLIDE3X_LIBRARY_PATH;

enum {
  kGlide3xPathLength = (sizeof(GLIDE3X_LIBRARY_PATH)
      / sizeof(GLIDE3X_LIBRARY_PATH[0])) - 1
};

static struct Mapi_FileVersionInfo file_version_info;

static void InitFileVersionInfo(void) {
  static int is_init = 0;

  if (is_init) {
    return;
  }

  file_version_info = Mapi_FileVersionInfo_InitFromPath(kGlide3xLibraryPath);

  is_init = 1;
}

static void InitStatic(void) {
  InitFileVersionInfo();
}

/**
 * External
 */

const wchar_t* D2_Glide3xLibrary_GetPath(void) {
  return kGlide3xLibraryPath;
}

const wchar_t* D2_Glide3xLibrary_QueryFileVersionInfoString(
    const wchar_t* sub_block
) {
  InitStatic();

  return Mapi_FileVersionInfo_QueryString(&file_version_info, sub_block);
}

const DWORD* D2_Glide3xLibrary_QueryFileVersionInfoVar(
    const wchar_t* sub_block,
    size_t* count
) {
  InitStatic();

  return Mapi_FileVersionInfo_QueryVar(&file_version_info, sub_block, count);
}

const VS_FIXEDFILEINFO* D2_Glide3xLibrary_QueryFixedFileInfo(void) {
  InitStatic();

  return Mapi_FileVersionInfo_QueryFixedFileInfo(&file_version_info);
}
