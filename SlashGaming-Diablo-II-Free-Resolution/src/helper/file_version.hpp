/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2023  Mir Drualga
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

#ifndef SGD2FR_HELPER_FILE_VERSION_HPP_
#define SGD2FR_HELPER_FILE_VERSION_HPP_

#include <windows.h>

#include <compare>
#include <filesystem>

#include "glide3x_version.hpp"

namespace sgd2fr {

class FileVersion {
 public:
  using VersionType = std::tuple<DWORD, DWORD, DWORD, DWORD>;

  FileVersion() = delete;

  explicit constexpr FileVersion(
      const VersionType& version
  ) noexcept
      : version_(version) {
  }

  explicit constexpr FileVersion(
      VersionType&& version
  ) noexcept
      : version_(std::move(version)) {
  }

  constexpr FileVersion(
      DWORD major_version_left,
      DWORD major_version_right,
      DWORD minor_version_left,
      DWORD minor_version_right
  ) noexcept
      : version_(
            VersionType(
                major_version_left,
                major_version_right,
                minor_version_left,
                minor_version_right
            )
        ) {
  }

  constexpr FileVersion(const FileVersion& file_version) noexcept = default;

  constexpr FileVersion(FileVersion&& file_version) noexcept = default;

  ~FileVersion() noexcept = default;

  constexpr FileVersion& operator=(
      const FileVersion& file_version
  ) noexcept = default;

  constexpr FileVersion& operator=(
      FileVersion&& file_version
  ) noexcept = default;

  constexpr friend bool operator==(
      const FileVersion& lhs,
      const FileVersion& rhs
  ) = default;

  constexpr friend std::strong_ordering operator<=>(
      const FileVersion& lhs,
      const FileVersion& rhs
  ) = default;

  static Glide3xVersion GuessGlide3xVersion(
      std::wstring_view raw_path
  );

  constexpr const VersionType& version() const noexcept {
    return this->version_;
  }

 private:
  VersionType version_;

  static FileVersion ReadFileVersion(
      std::wstring_view raw_path
  );

  static Glide3xVersion SearchGlide3xTable(
      const FileVersion& file_version
  );
};

} // namespace sgd2fr

#endif // SGD2FR_HELPER_FILE_VERSION_HPP_
