/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019  Mir Drualga
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

#include "glide3x_version.hpp"

#include <windows.h>
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>

#include <nowide/convert.hpp>
#include <fmt/format.h>
#include <sgd2mapi.hpp>
#include "../wide_macro.h"

namespace sgd2fr {
namespace {

constexpr std::wstring_view kFunctionFailErrorFormat =
    L"File: {} \n"
    L"Line: {} \n"
    L"\n"
    L"The function {} failed with error code {:X}.";

const std::unordered_map<
    std::string_view,
    Glide3xVersion
>&
GetGlide3xVersionsByFileVersions() {
  static const std::unordered_map<
      std::string_view,
      Glide3xVersion
  > glide3x_versions_by_file_versions = {
        { "1.0.0.1", Glide3xVersion::kSven1_4_4_21 },
        { "1.0.2.0", Glide3xVersion::kSven1_4_8_3 },
        { "3.10.0.658", Glide3xVersion::kNGlide3_10_0_658 },
  };

  return glide3x_versions_by_file_versions;
}

const std::unordered_map<
    Glide3xVersion,
    std::string_view
>&
GetGlide3xVersionNamesByGlide3xVersionIds() {
  static const std::unordered_map<
      Glide3xVersion,
      std::string_view
  > glide3x_version_names_by_glide3x_version_ids = {
        { Glide3xVersion::kSven1_4_4_21, "Sven 1.4.4.21" },
        { Glide3xVersion::kSven1_4_8_3, "Sven 1.4.8.3" },
        { Glide3xVersion::kNGlide3_10_0_658, "nGlide 3.10.0.658" },
  };

  return glide3x_version_names_by_glide3x_version_ids;
}

std::string
ExtractFileVersionString(
    const std::filesystem::path& file_path
) {
  // All the code for this function originated from StackOverflow user
  // crashmstr. Some parts were refactored for clarity.
  std::wstring file_path_text_wide = file_path.wstring();

  // Check version size.
  DWORD ignored;
  DWORD file_version_info_size = GetFileVersionInfoSizeW(
      file_path_text_wide.data(),
      &ignored
  );

  if (file_version_info_size == 0) {
    std::wstring full_message = fmt::format(
        kFunctionFailErrorFormat.data(),
        __FILEW__,
        __LINE__,
        L"GetFileVersionInfoSizeW",
        GetLastError()
    );

    MessageBoxW(
        nullptr,
        full_message.data(),
        L"GetFileVersionInfoSizeW Failed",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }

  // Get the file version info.
  auto file_version_info = std::make_unique<wchar_t[]>(file_version_info_size);
  BOOL is_get_file_version_info_success = GetFileVersionInfoW(
      file_path_text_wide.data(),
      ignored,
      file_version_info_size,
      file_version_info.get()
  );

  if (!is_get_file_version_info_success) {
    std::wstring full_message = fmt::format(
        kFunctionFailErrorFormat,
        __FILEW__,
        __LINE__,
        L"GetFileVersionInfoW",
        GetLastError()
    );

    MessageBoxW(
        nullptr,
        full_message.data(),
        L"GetFileVersionInfoW Failed",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }

  // Gather all of the information into the specified buffer, then check
  // version info signature.
  UINT version_info_size;
  VS_FIXEDFILEINFO* version_info;

  BOOL is_ver_query_value_success = VerQueryValueW(
      file_version_info.get(),
      L"\\",
      reinterpret_cast<LPVOID*>(&version_info),
      &version_info_size
  );

  if (!is_ver_query_value_success) {
    std::wstring full_message = fmt::format(
        kFunctionFailErrorFormat,
        __FILEW__,
        __LINE__,
        L"VerQueryValueW",
        GetLastError()
    );

    MessageBoxW(
        nullptr,
        full_message.data(),
        L"VerQueryValueW Failed",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }

  // Doesn't matter if you are on 32 bit or 64 bit,
  // DWORD is always 32 bits, so first two revision numbers
  // come from dwFileVersionMS, last two come from dwFileVersionLS
  return fmt::format(
      "{}.{}.{}.{}",
      (version_info->dwFileVersionMS >> 16) & 0xFFFF,
      (version_info->dwFileVersionMS >> 0) & 0xFFFF,
      (version_info->dwFileVersionLS >> 16) & 0xFFFF,
      (version_info->dwFileVersionLS >> 0) & 0xFFFF
  );
}

Glide3xVersion
DetermineGlide3xVersionByFileVersion(
    std::string_view version_string
) {
  const auto& glide3x_versions_by_file_versions =
      GetGlide3xVersionsByFileVersions();

  try {
    return glide3x_versions_by_file_versions.at(version_string);
  } catch(const std::out_of_range& e) {
    constexpr std::wstring_view kErrorFormatMessage =
        L"File: {} \n"
        L"Line: {} \n"
        L"\n"
        L"Could not determine the Glide3x version from the file version:"
        L"\"{}\"";

    std::wstring full_message = fmt::format(
        kErrorFormatMessage,
        __FILEW__,
        __LINE__,
        nowide::widen(version_string.data())
    );

    MessageBoxW(
        nullptr,
        full_message.data(),
        L"Failed to Determine Glide3x Version",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }
}

Glide3xVersion
GetGlide3xVersionByLibraryData(
    Glide3xVersion glide3x_version
) {
  // When detecting game address, we need to specify the library as a path and
  // not with the enum. The enum requires knowledge of the current game
  // version, and if this function is called, we know that the game version is
  // not yet known.

  std::vector<BYTE> expected_values;
  std::filesystem::path library_path;
  std::intptr_t offset_value;
  Glide3xVersion matching_version;
  Glide3xVersion non_matching_version;

  switch (glide3x_version) {
    default: {
      return glide3x_version;
    }
  }

  mapi::GameAddress game_address = mapi::GameAddress::FromOffset(
      std::move(library_path),
      offset_value
  );

  std::intptr_t raw_address = game_address.raw_address();

  bool is_range_equal = std::equal(
      expected_values.cbegin(),
      expected_values.cend(),
      reinterpret_cast<const BYTE*>(raw_address)
  );

  if (is_range_equal) {
    return matching_version;
  } else {
    return non_matching_version;
  }
}

Glide3xVersion
DetermineRunningGlide3xVersion() {
  std::string game_version_string = ExtractFileVersionString(
      "glide3x.dll"
  );

  // Perform first stage game version detection using the executable file
  // name.
  Glide3xVersion game_version = DetermineGlide3xVersionByFileVersion(
      game_version_string
  );

  // Perform second stage game version detection by checking the bytes of game
  // libraries.
  game_version = GetGlide3xVersionByLibraryData(game_version);

  return game_version;
}

} // namespace

std::string_view
GetGameVersionName(
    Glide3xVersion glide3x_version
) {
  try {
    return GetGlide3xVersionNamesByGlide3xVersionIds().at(glide3x_version);
  } catch (const std::out_of_range& e) {
    constexpr std::wstring_view kErrorFormatMessage =
        L"File: {} \n"
        L"Line: {} \n"
        L"\n"
        L"Could not determine the Glide3x version name from the Glide3x "
        L"version ID: "
        L"{}.";

    std::wstring full_message = fmt::format(
        kErrorFormatMessage,
        __FILEW__,
        __LINE__,
        static_cast<int>(glide3x_version)
    );

    MessageBoxW(
        nullptr,
        full_message.data(),
        L"Failed to Determine Glide3x Version ID",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }
}

Glide3xVersion GetRunningGlide3xVersionId() {
  static Glide3xVersion running_glide3x_version_id =
      DetermineRunningGlide3xVersion();
  return running_glide3x_version_id;
}

std::string_view
GetRunningGlide3xVersionName() {
  static std::string_view running_glide3x_version_name = GetGameVersionName(
      GetRunningGlide3xVersionId()
  );
  return running_glide3x_version_name;
}

} // namespace sgd2fr
