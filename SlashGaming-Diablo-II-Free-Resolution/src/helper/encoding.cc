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

#include "encoding.hpp"

#include <windows.h>

#include "error_handling.hpp"

namespace sgd2fr {
namespace {

template<typename T>
static std::wstring ConvertUtf8ToWide_Impl(
    T utf8_string,
    std::wstring_view source_code_file_path,
    int source_code_line
) {
  // Determine the number of characters needed.
  size_t num_wide_chars = MultiByteToWideChar(
      CP_UTF8,
      MB_ERR_INVALID_CHARS,
      reinterpret_cast<const char*>(utf8_string.data()),
      -1,
      nullptr,
      0
  );

  if (num_wide_chars == 0) {
    ExitOnWindowsFunctionFailureWithLastError(
        L"MultiByteToWideChar",
        GetLastError(),
        source_code_file_path,
        source_code_line
    );
  }

  // Create the wide string with the proper size.
  std::wstring wide_string(num_wide_chars, L'\0');

  // Convert the UTF-8 string to wide string. Check that there was no failure.
  size_t converted_chars = MultiByteToWideChar(
      CP_UTF8,
      MB_ERR_INVALID_CHARS,
      reinterpret_cast<const char*>(utf8_string.data()),
      -1,
      wide_string.data(),
      num_wide_chars
  );

  if (converted_chars == 0) {
    ExitOnWindowsFunctionFailureWithLastError(
        L"MultiByteToWideChar",
        GetLastError(),
        source_code_file_path,
        source_code_line
    );
  } else if (converted_chars < num_wide_chars) {
    ExitOnGeneralFailure(
        L"The number of converted characters is less than the intended "
        L"count.",
        L"String Conversion Failed",
        __FILEW__,
        __LINE__
    );
  }

  return wide_string;
}

template <typename T>
static T ConvertWideToUtf8_Impl(
    std::wstring_view wide_string,
    std::wstring_view source_code_file_path,
    int source_code_line
) {
  // Determine the number of characters needed.
  size_t num_utf8_chars = WideCharToMultiByte(
      CP_UTF8,
      WC_ERR_INVALID_CHARS,
      wide_string.data(),
      -1,
      nullptr,
      0,
      NULL,
      NULL
  );

  if (num_utf8_chars == 0) {
    ExitOnWindowsFunctionFailureWithLastError(
        L"WideCharToMultiByte",
        GetLastError(),
        source_code_file_path,
        source_code_line
    );
  }

  // Create the UTF-8 string with the proper size.
  T utf8_string(num_utf8_chars, '\0');

  // Convert the UTF-8 string to wide string. Check that there was no failure.
  size_t converted_chars = WideCharToMultiByte(
      CP_UTF8,
      WC_ERR_INVALID_CHARS,
      wide_string.data(),
      -1,
      reinterpret_cast<char*>(utf8_string.data()),
      0,
      NULL,
      NULL
  );

  if (converted_chars == 0) {
    ExitOnWindowsFunctionFailureWithLastError(
        L"WideCharToMultiByte",
        GetLastError(),
        source_code_file_path,
        source_code_line
    );
  } else if (converted_chars < num_utf8_chars) {
    ExitOnGeneralFailure(
        L"The number of converted characters is less than the intended "
        L"count.",
        L"String Conversion Failed",
        __FILEW__,
        __LINE__
    );
  }

  return utf8_string;
}

} // namespace

std::wstring ConvertUtf8ToWide(
    std::u8string_view utf8_string,
    std::wstring_view source_code_file_path,
    int source_code_line
) {
  return ConvertUtf8ToWide_Impl(
      utf8_string,
      source_code_file_path,
      source_code_line
  );
}

std::wstring ConvertMultiByteUtf8ToWide(
    std::string_view utf8_string,
    std::wstring_view source_code_file_path,
    int source_code_line
) {
  return ConvertUtf8ToWide_Impl(
      utf8_string,
      source_code_file_path,
      source_code_line
  );
}

std::u8string ConvertWideToUtf8(
    std::wstring_view wide_string,
    std::wstring_view source_code_file_path,
    int source_code_line
) {
  return ConvertWideToUtf8_Impl<std::u8string>(
      wide_string,
      source_code_file_path,
      source_code_line
  );
}

std::string ConvertWideToMultiByteUtf8(
    std::wstring_view wide_string,
    std::wstring_view source_code_file_path,
    int source_code_line
) {
  return ConvertWideToUtf8_Impl<std::string>(
      wide_string,
      source_code_file_path,
      source_code_line
  );
}

} // namespace sgd2fr
