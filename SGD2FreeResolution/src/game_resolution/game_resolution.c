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

#include "game_resolution.h"

#include <stddef.h>
#include <stdlib.h>
#include <windows.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/std/assert.h>
#include <mdc/wchar_t/filew.h>

static int GameResolution_CompareAsVoid(
    const void* resolution1,
    const void* resolution2
) {
  return GameResolution_Compare(resolution1, resolution2);
}

static struct GameResolution* standard_resolutions = NULL;
static size_t standard_resolutions_count = 0;
static size_t standard_resolutions_capacity = 0;

static void InitStandardResolutions(void) {
  static int is_init = 0;

  size_t i;
  void* realloc_result;

  DEVMODEW devmode;
  struct GameResolution game_resolution = { 0 };
  int compare_result;
  struct GameResolution* search_result;

  if (is_init) {
    return;
  }

  /*
   * Get an approximate for how much to allocate. This space will be
   * overallocated.
   */

  devmode.dmSize = sizeof(devmode);
  for (i = 0; EnumDisplaySettingsW(NULL, i, &devmode); i += 1) {
    /* This is intentionally kept blank. */
  }
  standard_resolutions_capacity = i;

  standard_resolutions = Mdc_malloc(
      standard_resolutions_capacity * sizeof(standard_resolutions[0])
  );

  if (standard_resolutions == NULL) {
    Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
    goto return_bad;
  }

  /*
   * Add the standard resolutions.
   */

  for (i = 0; EnumDisplaySettingsW(NULL, i, &devmode); i += 1) {
    game_resolution.width = devmode.dmPelsWidth;
    game_resolution.height = devmode.dmPelsHeight;

    search_result = bsearch(
        &game_resolution,
        standard_resolutions,
        standard_resolutions_count,
        sizeof(standard_resolutions[0]),
        &GameResolution_CompareAsVoid
    );

    if (search_result != NULL) {
      continue;
    }

    standard_resolutions[standard_resolutions_count] = game_resolution;
    standard_resolutions_count += 1;

    /*
     * Sort only if the newly added resolution unsorts the array.
     */

    if (standard_resolutions_count <= 1) {
      continue;
    }

    compare_result = GameResolution_Compare(
        &standard_resolutions[standard_resolutions_count - 2],
        &standard_resolutions[standard_resolutions_count - 1]
    );

    assert(compare_result != 0);

    if (compare_result < 0) {
      continue;
    }

    qsort(
        standard_resolutions,
        standard_resolutions_count,
        sizeof(standard_resolutions[0]),
        &GameResolution_CompareAsVoid
    );
  }

  /*
   * Shrink size to fit.
   */

  realloc_result = Mdc_realloc(
      standard_resolutions,
      standard_resolutions_count * sizeof(standard_resolutions[0])
  );

  if (realloc_result == NULL) {
    Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
    goto return_bad;
  }

  standard_resolutions = realloc_result;
  standard_resolutions_capacity = standard_resolutions_count;

  is_init = 1;
  return;

return_bad:
  return;
}

/**
 * External
 */

const struct GameResolution GameResolution_kUninit = GAME_RESOLUTION_UNINIT;
const struct IngameResolutions IngameResolutions_kUninit =
    INGAME_RESOLUTIONS_UNINIT;

const struct GameResolution GameResolution_k640x480 =
    GAME_RESOLUTION_640X480;
const struct GameResolution GameResolution_k800x600 =
    GAME_RESOLUTION_800X600;
const struct GameResolution GameResolution_k856x480 =
    GAME_RESOLUTION_856X480;
const struct GameResolution GameResolution_k1024x768 =
    GAME_RESOLUTION_1024X768;
const struct GameResolution GameResolution_k1068x600 =
    GAME_RESOLUTION_1068X600;

const struct GameResolution GameResolution_kDefault[] =
    GAME_RESOLUTION_DEFAULT;

const struct IngameResolutions IngameResolution_kDefault =
    INGAME_RESOLUTIONS_DEFAULT;

int GameResolution_Compare(
    const struct GameResolution* resolution1,
    const struct GameResolution* resolution2
) {
  if (resolution1->width < resolution2->width) {
    return -1;
  } else if (resolution1->width > resolution2->width) {
    return 1;
  }

  if (resolution1->height < resolution2->height) {
    return -1;
  } else if (resolution1->height > resolution2->height) {
    return 1;
  }

  return 0;
}

int GameResolution_IsStandardResolution(
    const struct GameResolution* resolution
) {
  const struct GameResolution* search_result;

  InitStandardResolutions();

  search_result = bsearch(
      resolution,
      standard_resolutions,
      standard_resolutions_count,
      sizeof(standard_resolutions[0]),
      &GameResolution_CompareAsVoid
  );

  return search_result != NULL;
}
