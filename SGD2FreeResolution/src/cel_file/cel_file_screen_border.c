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

#include "cel_file_screen_border.h"

#include <stddef.h>

#include "../helper/custom_mpq.h"
#include "../cel_file_config.h"

#define CEL_FILE_VANILLA_SCREEN_BORDER_PATH_DEFAULT \
    "data\\global\\UI\\Panel\\800BorderFrame"

static struct D2_CelFile* left_screen_border = NULL;
static struct D2_CelFile* right_screen_border = NULL;
static struct D2_CelFile* vanilla_screen_border = NULL;

static void InitLeftScreenBorder(void) {
  if (left_screen_border != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  left_screen_border = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->left_screen_border.path,
      0
  );
}

static void InitRightScreenBorder(void) {
  if (right_screen_border != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  right_screen_border = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->right_screen_border.path,
      0
  );
}

static void InitVanillaScreenBorder(void) {
  if (vanilla_screen_border != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  vanilla_screen_border = D2_D2Win_LoadCelFile(
      CEL_FILE_VANILLA_SCREEN_BORDER_PATH_DEFAULT,
      0
  );
}

/**
 * External
 */

/**
 * SGD2FreeRes Screen Borders
 */

struct D2_CelFile* CelFile_LeftScreenBorder_Get(void) {
  InitLeftScreenBorder();

  return left_screen_border;
}

void CelFile_LeftScreenBorder_Unload(void) {
  if (left_screen_border == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(left_screen_border);
  left_screen_border = NULL;
}

struct D2_CelFile* CelFile_RightScreenBorder_Get(void) {
  InitRightScreenBorder();

  return right_screen_border;
}

void CelFile_RightScreenBorder_Unload(void) {
  if (right_screen_border == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(right_screen_border);
  right_screen_border = NULL;
}

/**
 * Vanilla D2 border
 */

struct D2_CelFile* CelFile_VanillaScreenBorder_Get(void) {
  InitVanillaScreenBorder();

  return vanilla_screen_border;
}

void CelFile_VanillaScreenBorder_Unload(void) {
  if (vanilla_screen_border == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(vanilla_screen_border);
  vanilla_screen_border = NULL;
}
