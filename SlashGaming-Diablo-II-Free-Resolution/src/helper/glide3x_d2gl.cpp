/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2022  Mir Drualga
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

#include <filesystem>

#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.hpp>


namespace sgd2fr {
namespace d2gl_glide {
namespace {

typedef void(__stdcall *SetCustomScreenSizeFuncType)(
	uint32_t width,
	uint32_t height
);

static const char* const kSetCustomScreenSizeFuncName =
    "_setCustomScreenSize@8";

static SetCustomScreenSizeFuncType D2glSetCustomScreenSize;

} // namespace

bool IsD2glGlideWrapper(const wchar_t* path) {
  if (!::std::filesystem::exists(path)) {
    return false;
  }

  HMODULE glide3x_handle = GetModuleHandleW(path);
  bool is_library_already_loaded = (glide3x_handle != nullptr);

  if (!is_library_already_loaded) {
    glide3x_handle = LoadLibraryW(path);
  }

  if (glide3x_handle == nullptr) {
    ::mdc::error::ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        is_library_already_loaded
            ? L"GetModuleHandleW"
            : L"LoadLibraryW",
        GetLastError()
    );

    return false;
  }

  FARPROC raw_func_ptr = GetProcAddress(
      glide3x_handle,
      kSetCustomScreenSizeFuncName
  );

  if (!is_library_already_loaded) {
    FreeLibrary(glide3x_handle);
  }

  D2glSetCustomScreenSize = reinterpret_cast<SetCustomScreenSizeFuncType>(raw_func_ptr);

  return (raw_func_ptr != nullptr);
}

void SetCustomScreenSize(
	uint32_t width,
	uint32_t height
) {
  return D2glSetCustomScreenSize(width, height);
}

} // namespace d2gl_glide
} // namespace sgd2fr
