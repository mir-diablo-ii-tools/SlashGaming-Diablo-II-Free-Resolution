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

#include "glide3x_version.hpp"

#include <mdc/error/exit_on_error.hpp>
#include <mdc/wchar_t/filew.h>
#include "file_version.hpp"
#include "glide3x_d2dx.hpp"

namespace sgd2fr::glide3x_version {
namespace {

static const wchar_t* const kGlide3xPath = L"glide3x.dll";

static Glide3xVersion DetermineGlide3xVersion() {
  if (d2dx_glide::IsD2dxGlideWrapper(kGlide3xPath)) {
    return Glide3xVersion::kD2dx;
  }

  return FileVersion::GuessGlide3xVersion(kGlide3xPath);
}

} // namespace

::std::string_view GetName(Glide3xVersion glide3x_version) {
  switch (glide3x_version) {
    case Glide3xVersion::kSven1_4_4_21: {
      return "Sven 1.4.4.21";
    }

    case Glide3xVersion::kSven1_4_6_1: {
      return "Sven 1.4.6.1";
    }

    case Glide3xVersion::kSven1_4_8_3: {
      return "Sven 1.4.8.3";
    }

    case Glide3xVersion::kNGlide3_10_0_658: {
      return "nGlide 3.10.0.658";
    }

    default: {
      ::mdc::error::ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          static_cast<int>(glide3x_version)
      );

      return "";
    }
  }
}

Glide3xVersion GetRunning() {
  static Glide3xVersion running_glide3x_version =
      DetermineGlide3xVersion();

  return running_glide3x_version;
}

::std::string_view GetRunningName() {
  static ::std::string_view running_glide3x_version_name = GetName(
      GetRunning()
  );

  return running_glide3x_version_name;
}

} // namespace sgd2fr::glide3x_version
