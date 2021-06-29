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

#include "file_version_info.h"

#include <stdlib.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/wchar_t/filew.h>

const struct Mapi_FileVersionInfo Mapi_FileVersionInfo_kUninit =
    MAPI_FILE_VERSION_INFO_UNINIT;

struct Mapi_FileVersionInfo Mapi_FileVersionInfo_InitFromPath(
    const wchar_t* path
) {
  struct Mapi_FileVersionInfo file_version_info;
  DWORD ignored;

  size_t file_version_info_size;
  BOOL is_get_file_version_info_success;

  file_version_info_size = GetFileVersionInfoSizeW(path, &ignored);
  if (file_version_info_size == 0) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"GetFileVersionInfoSizeW",
        GetLastError()
    );

    goto return_bad;
  }

  file_version_info.file_version_info = Mdc_malloc(file_version_info_size);
  if (file_version_info.file_version_info == NULL) {
    Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
    
    goto return_bad;
  }

  is_get_file_version_info_success = GetFileVersionInfoW(
      path,
      ignored = 0,
      file_version_info_size,
      file_version_info.file_version_info
  );

  if (!is_get_file_version_info_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"GetFileVersionInfoW",
        GetLastError()
    );

    goto free_file_version_info;
  }

  return file_version_info;

free_file_version_info:
  Mdc_free(file_version_info.file_version_info);

return_bad:
  return Mapi_FileVersionInfo_kUninit;
}

void Mapi_FileVersionInfo_Deinit(struct Mapi_FileVersionInfo* file_version_info) {
  Mdc_free(file_version_info);
}

const VS_FIXEDFILEINFO* Mapi_FileVersionInfo_QueryFixedFileInfo(
    const struct Mapi_FileVersionInfo* file_version_info
) {
  const VS_FIXEDFILEINFO* fixed_file_info;

  BOOL is_ver_query_value_success;
  UINT len;

  is_ver_query_value_success = VerQueryValueW(
      file_version_info->file_version_info,
      L"\\",
      &fixed_file_info,
      &len
  );

  if (!is_ver_query_value_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"VerQueryValueW",
        GetLastError()
    );

    goto return_bad;
  }

  return fixed_file_info;

return_bad:
  return NULL;
}

const wchar_t* Mapi_FileVersionInfo_QueryString(
    const struct Mapi_FileVersionInfo* file_version_info,
    const wchar_t* sub_block
) {
  const wchar_t* str;

  BOOL is_ver_query_value_success;
  UINT len;

  is_ver_query_value_success = VerQueryValueW(
      file_version_info->file_version_info,
      sub_block,
      &str,
      &len
  );

  if (!is_ver_query_value_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"VerQueryValueW",
        GetLastError()
    );

    goto return_bad;
  }

  return str;

return_bad:
  return NULL;
}

const DWORD* Mapi_FileVersionInfo_QueryVar(
    const struct Mapi_FileVersionInfo* file_version_info,
    const wchar_t* sub_block,
    size_t* count
) {
  const DWORD* var;

  BOOL is_ver_query_value_success;
  UINT size;

  is_ver_query_value_success = VerQueryValueW(
      file_version_info->file_version_info,
      sub_block,
      &var,
      &size
  );

  if (!is_ver_query_value_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"VerQueryValueW",
        GetLastError()
    );

    goto return_bad;
  }

  *count = size / sizeof(var[0]);

  return var;

return_bad:
  return NULL;
}
