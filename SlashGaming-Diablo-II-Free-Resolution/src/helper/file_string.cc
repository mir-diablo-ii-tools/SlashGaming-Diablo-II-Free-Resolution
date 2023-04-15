/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2023  Mir Drualga
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

#include "file_string.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <utility>

#include <mdc/error/exit_on_error.hpp>
#include <mdc/wchar_t/filew.h>

namespace sgd2fr {
namespace {

using FileStringTableEntry = std::pair<
    ::std::wstring_view,
    DDrawVersion
>;

struct FileStringTableEntryCompareKey {
  constexpr bool operator()(
      const FileStringTableEntry& entry1,
      const FileStringTableEntry& entry2
  ) const noexcept {
    return entry1.first < entry2.first;
  }

  constexpr bool operator()(
      const FileStringTableEntry& entry,
      ::std::wstring_view file_string
  ) const noexcept {
    return entry.first < file_string;
  }

  constexpr bool operator()(
      ::std::wstring_view file_string,
      const FileStringTableEntry& entry
  ) const noexcept {
    return file_string < entry.first;
  }
};

static constexpr const std::array<
    FileStringTableEntry,
    2
> kFileStringSortedTable = {{
    { L"D2GL", DDrawVersion::kD2gl },
    { L"cnc-ddraw", DDrawVersion::kCnC },
}};

// If this assertion compiles but produces a linter error, ignore it.
static_assert(
    std::is_sorted(
        kFileStringSortedTable.cbegin(),
        kFileStringSortedTable.cend(),
        FileStringTableEntryCompareKey()
    )
);

} // namespace

DDrawVersion FileString::GuessDDrawVersion(
    std::wstring_view raw_path
) {
  ::std::wstring file_string = ReadFileString(
      raw_path,
      L"040904B0",
      L"ProductName"
  );

  return SearchDDrawTable(file_string);
}

::std::wstring FileString::ReadFileString(
    ::std::wstring_view raw_path,
    ::std::wstring_view language_charset,
    ::std::wstring_view file_string_name
) {
  const wchar_t* file_path_text_cstr = raw_path.data();

  // Check version size.
  DWORD ignored;
  DWORD file_version_info_size = GetFileVersionInfoSizeW(
      file_path_text_cstr,
      &ignored
  );

  if (file_version_info_size == 0) {
    ::mdc::error::ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"GetFileVersionInfoSizeW",
        GetLastError()
    );

    return L"";
  }

  // Get the file version info.
  auto file_version_info = std::make_unique<wchar_t[]>(
      file_version_info_size
  );

  BOOL is_get_file_version_info_success = GetFileVersionInfoW(
      file_path_text_cstr,
      ignored,
      file_version_info_size,
      file_version_info.get()
  );

  if (!is_get_file_version_info_success) {
    ::mdc::error::ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"GetFileVersionInfoW",
        GetLastError()
    );

    return L"";
  }

  // Generate the full file string name.
  static constexpr ::std::size_t kFullFileStringNameCapacity = 256;
  ::std::array<wchar_t, kFullFileStringNameCapacity> full_file_string_name;

  // Acceptable unchecked sprintf-family usage, as the inputs are
  // determined internally.
  ::std::swprintf(
      full_file_string_name.data(),
      kFullFileStringNameCapacity,
      L"\\StringFileInfo\\%ls\\%ls",
      language_charset.data(),
      file_string_name.data()
  );

  // Query the file string value. 
  UINT file_string_value_capacity;
  wchar_t* temp_file_string_value;

  BOOL is_ver_query_value_success = VerQueryValueW(
      file_version_info.get(),
      full_file_string_name.data(),
      reinterpret_cast<LPVOID*>(&temp_file_string_value),
      &file_string_value_capacity
  );

  if (!is_ver_query_value_success) {
    ::mdc::error::ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"VerQueryValueW",
        GetLastError()
    );

    return L"";
  }

  return temp_file_string_value;
}

DDrawVersion FileString::SearchDDrawTable(
    ::std::wstring_view file_string
) {
  std::pair search_range = std::equal_range(
      kFileStringSortedTable.cbegin(),
      kFileStringSortedTable.cend(),
      file_string,
      FileStringTableEntryCompareKey()
  );

  if (search_range.first == kFileStringSortedTable.cend()
      || search_range.first == search_range.second) {
    return DDrawVersion::kWindowsDefault;
  }

  return search_range.first->second;
}

} // namespace sgd2fr
