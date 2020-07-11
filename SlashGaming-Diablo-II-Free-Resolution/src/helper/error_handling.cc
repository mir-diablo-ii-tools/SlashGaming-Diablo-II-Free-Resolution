/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2020  Mir Drualga
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

#include "error_handling.hpp"

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cwchar>
#include <memory>

#include <fmt/format.h>

namespace sgd2fr {
namespace {

static constexpr std::wstring_view kWindowsFunctionFailErrorFormat =
    L"File: {} \n"
    L"Line: {} \n"
    L"\n"
    L"The function {} failed with error code {:X}.";

static constexpr std::wstring_view kWindowsFunctionGeneralFailErrorFormat =
    L"File: {} \n"
    L"Line: {} \n"
    L"Function: {} \n"
    L"GetLastError: {:X} \n"
    L"\n"
    L"{}";

static constexpr std::wstring_view kGeneralFailErrorFormat =
    L"File: {} \n"
    L"Line: {} \n"
    L"\n"
    L"{}";

} // namespace

void ExitOnGeneralFailure(
    std::wstring_view message,
    std::wstring_view caption,
    std::wstring_view file_name,
    int line
) {
#ifndef NDEBUG
  std::wstring full_message = fmt::format(
      kGeneralFailErrorFormat,
      file_name,
      line,
      message
  );

  MessageBoxW(
      NULL,
      full_message.data(),
      caption.data(),
      MB_OK | MB_ICONERROR
  );
#endif // NDEBUG

  std::exit(EXIT_FAILURE);
}

[[noreturn]]
void ExitOnWindowsFunctionGeneralFailureWithLastError(
    std::wstring_view message,
    std::wstring_view caption,
    std::wstring_view function_name,
    DWORD last_error,
    std::wstring_view file_name,
    int line
){
#ifndef NDEBUG
  // Build the message string.
  std::wstring full_message = fmt::format(
      kWindowsFunctionGeneralFailErrorFormat,
      file_name,
      line,
      function_name,
      last_error,
      message
  );

  // Build the caption string.
  std::wstring full_caption = fmt::format(
      L"{} Failed",
      function_name
  );

  MessageBoxW(
      NULL,
      full_message.data(),
      full_caption.data(),
      MB_OK | MB_ICONERROR
  );
#endif // NDEBUG

  std::exit(EXIT_FAILURE);
}

void ExitOnWindowsFunctionFailureWithLastError(
    std::wstring_view function_name,
    DWORD last_error,
    std::wstring_view file_name,
    int line
){
#ifndef NDEBUG
  // Build the message string.
  std::wstring full_message = fmt::format(
      kWindowsFunctionFailErrorFormat,
      file_name,
      line,
      function_name,
      last_error
  );

  // Build the caption string.
  std::wstring full_caption = fmt::format(
      L"{} Failed",
      function_name
  );

  MessageBoxW(
      NULL,
      full_message.data(),
      full_caption.data(),
      MB_OK | MB_ICONERROR
  );
#endif // NDEBUG

  std::exit(EXIT_FAILURE);
}

} // namespace sgd2fr
