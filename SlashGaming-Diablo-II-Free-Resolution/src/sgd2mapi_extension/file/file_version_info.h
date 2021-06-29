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

#ifndef SGD2FR_SGD2MAPI_EXTENSION_FILE_FILE_VERSION_INFO_H_
#define SGD2FR_SGD2MAPI_EXTENSION_FILE_FILE_VERSION_INFO_H_

#include <stddef.h>
#include <windows.h>

#include <mdc/std/wchar.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct Mapi_FileVersionInfo {
  void* file_version_info;
};

#define MAPI_FILE_VERSION_INFO_UNINIT { 0 };

const struct Mapi_FileVersionInfo Mapi_FileVersionInfo_kUninit;

struct Mapi_FileVersionInfo Mapi_FileVersionInfo_InitFromPath(
    const wchar_t* path
);

void Mapi_FileVersionInfo_Deinit(
    struct Mapi_FileVersionInfo* file_version_info
);

const VS_FIXEDFILEINFO* Mapi_FileVersionInfo_QueryFixedFileInfo(
    const struct Mapi_FileVersionInfo* file_version_info
);

const wchar_t* Mapi_FileVersionInfo_QueryString(
    const struct Mapi_FileVersionInfo* file_version_info,
    const wchar_t* sub_block
);

const DWORD* Mapi_FileVersionInfo_QueryVar(
    const struct Mapi_FileVersionInfo* file_version_info,
    const wchar_t* sub_block,
    size_t* count
);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SGD2FR_SGD2MAPI_EXTENSION_FILE_FILE_VERSION_INFO_H_ */
