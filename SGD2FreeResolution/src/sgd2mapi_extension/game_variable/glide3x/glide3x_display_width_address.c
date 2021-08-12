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

#include "glide3x_display_width_address.h"

#include <mdc/error/exit_on_error.h>
#include <mdc/wchar_t/filew.h>
#include <sgd2mapi.h>
#include "../../glide3x_library.h"
#include "../../glide3x_library_version.h"

static struct Mapi_GameAddress game_address;

static void InitGameAddress(void) {
  static int is_init = 0;

  enum D2_Glide3xLibraryVersion running_glide3x_library_version;

  if (is_init) {
    return;
  }

  running_glide3x_library_version = D2_Glide3xLibraryVersion_GetRunning();

  switch (running_glide3x_library_version) {
    case D2_Glide3xLibraryVersion_kSven1_4_4_21: {
      game_address = Mapi_GameAddress_InitFromPathAndOffset(
          D2_Glide3xLibrary_GetPath(),
          0x1C9A0
      );

      break;
    }

    case D2_Glide3xLibraryVersion_kSven1_4_6_1: {
      game_address = Mapi_GameAddress_InitFromPathAndOffset(
          D2_Glide3xLibrary_GetPath(),
          0x1C870
      );

      break;
    }

    case D2_Glide3xLibraryVersion_kSven1_4_8_3: {
      game_address = Mapi_GameAddress_InitFromPathAndOffset(
          D2_Glide3xLibrary_GetPath(),
          0x1D870
      );

      break;
    }

    case D2_Glide3xLibraryVersion_kNGlide3_10_0_658: {
      game_address = Mapi_GameAddress_InitFromPathAndOffset(
          D2_Glide3xLibrary_GetPath(),
          0x169DA4
      );

      break;
    }

    default: {
      Mdc_Error_ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          running_glide3x_library_version
      );

      goto return_bad;
    }
  }

  is_init = 1;
  return;

return_bad:
  is_init = 0;
  return;
}

/**
 * External
 */

int* D2_Glide3x_GetDisplayWidthAddress(void) {
  InitGameAddress();

  return *(int**)game_address.raw_address;
}

void D2_Glide3x_SetDisplayWidthAddress(int* width_address) {
  InitGameAddress();

  *(int**)game_address.raw_address = width_address;
}
