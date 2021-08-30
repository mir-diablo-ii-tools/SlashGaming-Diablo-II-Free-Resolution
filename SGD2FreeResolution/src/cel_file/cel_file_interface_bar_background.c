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

#include "../helper/custom_mpq.h"
#include "../cel_file_config.h"

static struct D2_CelFile* background_left = NULL;
static struct D2_CelFile* background_left_center = NULL;
static struct D2_CelFile* background_right = NULL;
static struct D2_CelFile* background_right_center = NULL;

static void InitBackgroundLeft(void) {
  if (background_left != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  background_left = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->interface_bar_background_left.path,
      0
  );
}

static void InitBackgroundLeftCenter(void) {
  if (background_left_center != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  background_left_center = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->interface_bar_background_left_center.path,
      0
  );
}

static void InitBackgroundRight(void) {
  if (background_right != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  background_right = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->interface_bar_background_right.path,
      0
  );
}

static void InitBackgroundRightCenter(void) {
  if (background_right != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  background_right_center = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->interface_bar_background_right_center.path,
      0
  );
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

struct D2_CelFile* CelFile_InterfaceBarBackground_GetLeftCenter(void) {
  InitBackgroundLeftCenter();

  return background_left_center;
}

void CelFile_InterfaceBarBackground_UnloadLeftCenter(void) {
  if (background_left_center == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(background_left_center);
  background_left_center = NULL;
}

struct D2_CelFile* CelFile_InterfaceBarBackground_GetRight(void) {
  InitBackgroundRight();

  return background_right;
}

void CelFile_InterfaceBarBackground_UnloadRight(void) {
  if (background_right == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(background_right);
  background_right = NULL;
}

struct D2_CelFile* CelFile_InterfaceBarBackground_GetRightCenter(void) {
  InitBackgroundRightCenter();

  return background_right_center;
}

void CelFile_InterfaceBarBackground_UnloadRightCenter(void) {
  if (background_right_center == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(background_right_center);
  background_right_center = NULL;
}
