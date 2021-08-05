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

#include "file_content.h"

#include <stdio.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/wchar_t/filew.h>

size_t Mapi_File_GetFileContentLength(const wchar_t* path) {
  int fclose_result;
  int fseek_result;
  long file_length;

  FILE* file;

  file = _wfopen(path, L"rb");
  if (file == NULL) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"_wfopen failed.",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  fseek_result = fseek(file, 0, SEEK_END);
  if (fseek_result != 0) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"fseek failed.",
        __FILEW__,
        __LINE__
    );

    goto fclose_file;
  }

  file_length = ftell(file);
  if (file_length == -1) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"ftell failed.",
        __FILEW__,
        __LINE__
    );

    goto fclose_file;
  }

  fclose_result = fclose(file);
  if (fclose_result != 0) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"fclose failed.",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return file_length;

fclose_file:
  fclose(file);

return_bad:
  return 0;
}

void Mapi_File_ReadFileContent(
    char* file_content,
    size_t file_length,
    const wchar_t* path
) {
  int fclose_result;
  size_t fread_result;

  FILE* file;

  file = _wfopen(path, L"rb");
  if (file == NULL) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"_wfopen failed.",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  fread_result = fread(
      file_content,
      sizeof(file_content[0]),
      file_length,
      file
  );
  if (fread_result < file_length) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"fread failed.",
        __FILEW__,
        __LINE__
    );

    goto fclose_file;
  }

  fclose_result = fclose(file);
  if (fclose_result != 0) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"fclose failed.",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

fclose_file:
  fclose(file);

return_bad:
  return;
}
