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

#include "glide3x_library_version.h"

#include <stddef.h>
#include <stdlib.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/wchar_t/filew.h>
#include "glide3x_library_d2dx/glide3x_library_d2dx.h"
#include "glide3x_library_version/glide3x_library_version_file_version.h"

static enum D2_Glide3xLibraryVersion running_glide3x_library_version;

static void InitRunningGlide3xLibraryVersion(void) {
  static int is_init = 0;

  if (is_init) {
    return;
  }

  running_glide3x_library_version = (IsD2dxGlideWrapper())
      ? D2_Glide3xLibraryVersion_kD2dx
      : GuessGlide3xLibraryVersion();

  is_init = 1;
}

static void InitStatic(void) {
  InitRunningGlide3xLibraryVersion();
}

/**
 * External
 */

const char* D2_Glide3xLibraryVersion_GetName(
    enum D2_Glide3xLibraryVersion glide3x_version
) {
  InitStatic();

  switch (glide3x_version) {
    case D2_Glide3xLibraryVersion_kSven1_4_4_21: {
      return "Sven 1.4.4.21";
    }

    case D2_Glide3xLibraryVersion_kSven1_4_6_1: {
      return "Sven 1.4.6.1";
    }

    case D2_Glide3xLibraryVersion_kSven1_4_8_3: {
      return "Sven 1.4.8.3";
    }

    case D2_Glide3xLibraryVersion_kNGlide3_10_0_658: {
      return "nGlide 3.10.0.658";
    }

    default: {
      Mdc_Error_ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          glide3x_version
      );

      return "";
    }
  }
}

enum D2_Glide3xLibraryVersion D2_Glide3xLibraryVersion_GetRunning() {
  InitStatic();

  return running_glide3x_library_version;
}

const char* D2_Glide3xLibraryVersion_GetRunningName() {
  InitStatic();

  return D2_Glide3xLibraryVersion_GetName(
      D2_Glide3xLibraryVersion_GetRunning()
  );
}
