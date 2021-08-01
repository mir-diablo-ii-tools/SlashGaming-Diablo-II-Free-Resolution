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

#include "cel_file_screen_background_border.h"

#include "../compile_time_switch.h"

#if !defined(COMPILE_TIME_CEL_FILE_PATH_VERSION)
#error COMPILE_TIME_CEL_FILE_PATH_VERSION not defined.
#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

#if COMPILE_TIME_CEL_FILE_PATH_VERSION == 2

#define DEFAULT_LEFT_SCREEN_BACKGROUND_BORDER_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyVerticalBar"
#define DEFAULT_RIGHT_SCREEN_BACKGROUND_BORDER_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyVerticalBar"

#elif COMPILE_TIME_CEL_FILE_PATH_VERSION == 3

#define DEFAULT_LEFT_SCREEN_BACKGROUND_BORDER_PATH \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBackgroundBorder\\LeftScreen"
#define DEFAULT_RIGHT_SCREEN_BACKGROUND_BORDER_PATH \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBackgroundBorder\\RightScreen"

#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

static const char* const kDefaultLeftScreenBackgroundBorderPath =
    DEFAULT_LEFT_SCREEN_BACKGROUND_BORDER_PATH;
static const char* const kDefaultRightScreenBackgroundBorderPath =
    DEFAULT_RIGHT_SCREEN_BACKGROUND_BORDER_PATH;

enum {
  kDefaultLeftScreenBorderPathLength =
      sizeof(DEFAULT_LEFT_SCREEN_BACKGROUND_BORDER_PATH)
          / sizeof(DEFAULT_LEFT_SCREEN_BACKGROUND_BORDER_PATH[0]) - 1,
  kDefaultRightScreenBackgroundBorderPathLength =
      sizeof(DEFAULT_RIGHT_SCREEN_BACKGROUND_BORDER_PATH)
          / sizeof(DEFAULT_RIGHT_SCREEN_BACKGROUND_BORDER_PATH[0]) - 1,
};

static struct D2_CelFile* left_screen_background_border;
static struct D2_CelFile* right_screen_background_border;

static void InitLeftScreenBackgroundBorder(void) {

  if (left_screen_background_border != NULL) {
    return;
  }

  left_screen_background_border = D2_D2Win_LoadCelFile(
      kDefaultLeftScreenBackgroundBorderPath,
      0
  );
}

static void InitRightScreenBackgroundBorder(void) {
  if (right_screen_background_border != NULL) {
    return;
  }

  right_screen_background_border = D2_D2Win_LoadCelFile(
      kDefaultRightScreenBackgroundBorderPath,
      0
  );
}

/**
 * External
 */

struct D2_CelFile* CelFile_LeftScreenBackgroundBorder_Get(void) {
  InitLeftScreenBackgroundBorder();

  return left_screen_background_border;
}

void CelFile_LeftScreenBackgroundBorder_Unload(void) {
  if (left_screen_background_border == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(left_screen_background_border);
  left_screen_background_border = NULL;
}

const char* CelFile_LeftScreenBackgroundBorder_GetPath(void) {
  return kDefaultLeftScreenBackgroundBorderPath;
}

struct D2_CelFile* CelFile_RightScreenBackgroundBorder_Get(void) {
  InitRightScreenBackgroundBorder();

  return right_screen_background_border;
}

void CelFile_RightScreenBackgroundBorder_Unload(void) {
  if (right_screen_background_border == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(right_screen_background_border);
  right_screen_background_border = NULL;
}

const char* CelFile_RightScreenBackgroundBorder_GetPath(void) {
  return kDefaultRightScreenBackgroundBorderPath;
}
