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

#include "cel_file_interface_bar_background.h"

#include <stddef.h>

#include "../compile_time_switch.h"

#if COMPILE_TIME_CEL_FILE_PATH_VERSION == 2

#define DEFAULT_BACKGROUND_LEFT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertLeft"
#define DEFAULT_BACKGROUND_CENTER_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertHorizontalBar"
#define DEFAULT_BACKGROUND_RIGHT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertRight"

#elif COMPILE_TIME_CEL_FILE_PATH_VERSION == 3

#define DEFAULT_BACKGROUND_LEFT_PATH \
    "data\\SGD2FreeResolution\\ui\\PANEL\\InterfaceBarBackground\\Left"
#define DEFAULT_BACKGROUND_CENTER_PATH \
    "data\\SGD2FreeResolution\\ui\\PANEL\\InterfaceBarBackground\\Center"
#define DEFAULT_BACKGROUND_RIGHT_PATH \
    "data\\SGD2FreeResolution\\ui\\PANEL\\InterfaceBarBackground\\Right"

#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

static const char* const kDefaultBackgroundLeftPath =
    DEFAULT_BACKGROUND_LEFT_PATH;
static const char* const kDefaultBackgroundCenterPath =
    DEFAULT_BACKGROUND_CENTER_PATH;
static const char* const kDefaultBackgroundRightPath =
    DEFAULT_BACKGROUND_RIGHT_PATH;

enum {
  kDefaultBackgroundLeftPathLength = sizeof(DEFAULT_BACKGROUND_LEFT_PATH)
      / sizeof(DEFAULT_BACKGROUND_LEFT_PATH[0]) - 1,
  kDefaultBackgroundCenterPathLength = sizeof(DEFAULT_BACKGROUND_CENTER_PATH)
      / sizeof(DEFAULT_BACKGROUND_CENTER_PATH[0]) - 1,
  kDefaultBackgroundRightPathLength = sizeof(DEFAULT_BACKGROUND_RIGHT_PATH)
      / sizeof(DEFAULT_BACKGROUND_RIGHT_PATH[0]) - 1,
};

static struct D2_CelFile* background_left = NULL;
static struct D2_CelFile* background_center = NULL;
static struct D2_CelFile* background_right = NULL;

static void InitBackgroundLeft(void) {
  if (background_left != NULL) {
    return;
  }

  background_left = D2_D2Win_LoadCelFile(kDefaultBackgroundLeftPath, 0);
}

static void InitBackgroundCenter(void) {
  if (background_center != NULL) {
    return;
  }

  background_center = D2_D2Win_LoadCelFile(kDefaultBackgroundCenterPath, 0);
}

static void InitBackgroundRight(void) {
  if (background_right != NULL) {
    return;
  }

  background_right = D2_D2Win_LoadCelFile(kDefaultBackgroundRightPath, 0);
}

/**
 * External
 */

struct D2_CelFile* CelFile_InterfaceBarBackground_GetLeft(void) {
  InitBackgroundLeft();

  return background_left;
}

void CelFile_InterfaceBarBackground_UnloadLeft(void) {
  if (background_left == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(background_left);
  background_left = NULL;
}

const char* CelFile_InterfaceBarBackground_GetLeftPath(void) {
  return kDefaultBackgroundLeftPath;
}

struct D2_CelFile* CelFile_InterfaceBarBackground_GetCenter(void) {
  InitBackgroundCenter();

  return background_center;
}

void CelFile_InterfaceBarBackground_UnloadCenter(void) {
  if (background_center == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(background_center);
  background_center = NULL;
}

const char* CelFile_InterfaceBarBackground_GetCenterPath(void) {
  return kDefaultBackgroundCenterPath;
}

struct D2_CelFile* CelFile_InterfaceBarBackground_GetRight(void) {
  InitBackgroundRight();

  return background_right;
}

void CelFile_InterfaceBarBackground_UnloadRight(void) {
  if (background_center == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(background_center);
  background_center = NULL;
}

const char* CelFile_InterfaceBarBackground_GetRightPath(void) {
  return kDefaultBackgroundRightPath;
}
