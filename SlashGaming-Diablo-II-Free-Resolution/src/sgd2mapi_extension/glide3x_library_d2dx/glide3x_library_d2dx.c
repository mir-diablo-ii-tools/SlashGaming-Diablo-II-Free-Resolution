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

#include "glide3x_library_d2dx.h"

#include <windows.h>
#include <shlwapi.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/wchar_t/filew.h>

#define GET_CONFIGURATOR_FUNCTION_NAME "_D2DXGetConfigurator@0"

static const char* const kGetConfiguratorFunctionName =
    GET_CONFIGURATOR_FUNCTION_NAME;

enum {
  kGetConfiguratorFuncNameLength = (sizeof(GET_CONFIGURATOR_FUNCTION_NAME)
      / sizeof(GET_CONFIGURATOR_FUNCTION_NAME[0])) - 1,
};

/**
 * External
 */

int IsD2dxGlideWrapper(void) {
  const wchar_t* path;
  HMODULE glide3x_handle;
  int is_library_already_loaded;
  FARPROC get_configurator_function;
  int is_free_library_success;

  path = D2_Glide3xLibrary_GetPath();

  if (!PathFileExistsW(path)) {
    return 0;
  }

  glide3x_handle = GetModuleHandleW(path);
  is_library_already_loaded = (glide3x_handle != NULL);

  if (!is_library_already_loaded) {
    glide3x_handle = LoadLibraryW(path);
  }

  if (glide3x_handle == NULL) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        is_library_already_loaded
            ? L"GetModuleHandleW"
            : L"LoadLibraryW",
        GetLastError()
    );

    return 0;
  }

  get_configurator_function = GetProcAddress(
      glide3x_handle,
      kGetConfiguratorFunctionName
  );

  if (!is_library_already_loaded) {
    is_free_library_success = FreeLibrary(glide3x_handle);
    if (!is_free_library_success) {
      Mdc_Error_ExitOnWindowsFunctionError(
          __FILEW__,
          __LINE__,
          L"FreeLibrary",
          GetLastError()
      );

      return 0;
    }
  }

  return (get_configurator_function != NULL);
}
