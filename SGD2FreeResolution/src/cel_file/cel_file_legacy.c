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

#include "cel_file_legacy.h"

#include <stddef.h>

static struct D2_CelFile* left_screen_border_left = NULL;
static struct D2_CelFile* left_screen_border_top = NULL;
static struct D2_CelFile* left_screen_border_top_right = NULL;
static struct D2_CelFile* left_screen_border_bottom = NULL;
static struct D2_CelFile* left_screen_border_bottom_right = NULL;

static struct D2_CelFile* right_screen_border_right = NULL;
static struct D2_CelFile* right_screen_border_top = NULL;
static struct D2_CelFile* right_screen_border_top_left = NULL;
static struct D2_CelFile* right_screen_border_bottom = NULL;
static struct D2_CelFile* right_screen_border_bottom_left = NULL;

static struct D2_CelFile* screen_border_ribbon_horizontal = NULL;
static struct D2_CelFile* screen_border_ribbon_vertical = NULL;

static void InitLeftScreenBorderLeft(void) {
  if (left_screen_border_left != NULL) {
    return;
  }

  left_screen_border_left = D2_D2Win_LoadCelFile(
      CEL_FILE_LEFT_SCREEN_BORDER_LEFT_PATH_DEFAULT,
      0
  );
}

static void InitLeftScreenBorderTop(void) {
  if (left_screen_border_top != NULL) {
    return;
  }

  left_screen_border_top = D2_D2Win_LoadCelFile(
      CEL_FILE_LEFT_SCREEN_BORDER_TOP_PATH_DEFAULT,
      0
  );
}

static void InitLeftScreenBorderTopRight(void) {
  if (left_screen_border_top_right != NULL) {
    return;
  }

  left_screen_border_top_right = D2_D2Win_LoadCelFile(
      CEL_FILE_LEFT_SCREEN_BORDER_TOP_RIGHT_PATH_DEFAULT,
      0
  );
}

static void InitLeftScreenBorderBottom(void) {
  if (left_screen_border_bottom != NULL) {
    return;
  }

  left_screen_border_bottom = D2_D2Win_LoadCelFile(
      CEL_FILE_LEFT_SCREEN_BORDER_BOTTOM_PATH_DEFAULT,
      0
  );
}

static void InitLeftScreenBorderBottomRight(void) {
  if (left_screen_border_bottom_right != NULL) {
    return;
  }

  left_screen_border_bottom_right = D2_D2Win_LoadCelFile(
      CEL_FILE_LEFT_SCREEN_BORDER_BOTTOM_RIGHT_PATH_DEFAULT,
      0
  );
}

static void InitRightScreenBorderRight(void) {
  if (right_screen_border_right != NULL) {
    return;
  }

  right_screen_border_right = D2_D2Win_LoadCelFile(
      CEL_FILE_RIGHT_SCREEN_BORDER_RIGHT_PATH_DEFAULT,
      0
  );
}

static void InitRightScreenBorderTop(void) {
  if (right_screen_border_top != NULL) {
    return;
  }

  right_screen_border_top = D2_D2Win_LoadCelFile(
      CEL_FILE_RIGHT_SCREEN_BORDER_TOP_PATH_DEFAULT,
      0
  );
}

static void InitRightScreenBorderTopLeft(void) {
  if (right_screen_border_top_left != NULL) {
    return;
  }

  right_screen_border_top_left = D2_D2Win_LoadCelFile(
      CEL_FILE_RIGHT_SCREEN_BORDER_TOP_LEFT_PATH_DEFAULT,
      0
  );
}

static void InitRightScreenBorderBottom(void) {
  if (right_screen_border_bottom != NULL) {
    return;
  }

  right_screen_border_bottom = D2_D2Win_LoadCelFile(
      CEL_FILE_RIGHT_SCREEN_BORDER_BOTTOM_PATH_DEFAULT,
      0
  );
}

static void InitRightScreenBorderBottomLeft(void) {
  if (right_screen_border_bottom_left != NULL) {
    return;
  }

  right_screen_border_bottom_left = D2_D2Win_LoadCelFile(
      CEL_FILE_RIGHT_SCREEN_BORDER_BOTTOM_LEFT_PATH_DEFAULT,
      0
  );
}

static void InitScreenBorderRibbonHorizontal(void) {
  if (screen_border_ribbon_horizontal != NULL) {
    return;
  }

  screen_border_ribbon_horizontal = D2_D2Win_LoadCelFile(
      CEL_FILE_SCREEN_BORDER_RIBBON_HORIZONTAL_PATH_DEFAULT,
      0
  );
}

static void InitScreenBorderRibbonVertical(void) {
  if (screen_border_ribbon_vertical != NULL) {
    return;
  }

  screen_border_ribbon_vertical = D2_D2Win_LoadCelFile(
      CEL_FILE_SCREEN_BORDER_RIBBON_VERTICAL_PATH_DEFAULT,
      0
  );
}

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int __cdecl Helper_CelFileCollection_RunChecksum(int* flags);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

/**
 * Left screen border
 */

struct D2_CelFile* CelFile_LeftScreenBorder_GetLeft(void) {
  InitLeftScreenBorderLeft();

  return left_screen_border_left;
}

void CelFile_LeftScreenBorder_UnloadLeft(void) {
  if (left_screen_border_left == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(left_screen_border_left);
  left_screen_border_left = NULL;
}

struct D2_CelFile* CelFile_LeftScreenBorder_GetTop(void) {
  InitLeftScreenBorderTop();

  return left_screen_border_top;
}

void CelFile_LeftScreenBorder_UnloadTop(void) {
  if (left_screen_border_top == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(left_screen_border_top);
  left_screen_border_top = NULL;
}

struct D2_CelFile* CelFile_LeftScreenBorder_GetTopRight(void) {
  InitLeftScreenBorderTopRight();

  return left_screen_border_top_right;
}

void CelFile_LeftScreenBorder_UnloadTopRight(void) {
  if (left_screen_border_top_right == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(left_screen_border_top_right);
  left_screen_border_top_right = NULL;
}

struct D2_CelFile* CelFile_LeftScreenBorder_GetBottom(void) {
  InitLeftScreenBorderBottom();

  return left_screen_border_bottom;
}

void CelFile_LeftScreenBorder_UnloadBottom(void) {
  if (left_screen_border_bottom == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(left_screen_border_bottom);
  left_screen_border_bottom = NULL;
}

struct D2_CelFile* CelFile_LeftScreenBorder_GetBottomRight(void) {
  InitLeftScreenBorderBottomRight();

  return left_screen_border_bottom_right;
}

void CelFile_LeftScreenBorder_UnloadBottomRight(void) {
  if (left_screen_border_bottom_right == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(left_screen_border_bottom_right);
  left_screen_border_bottom_right = NULL;
}

/**
 * Right screen border
 */

struct D2_CelFile* CelFile_RightScreenBorder_GetRight(void) {
  InitRightScreenBorderRight();

  return right_screen_border_right;
}

void CelFile_RightScreenBorder_UnloadRight(void) {
  if (right_screen_border_right == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(right_screen_border_right);
  right_screen_border_right = NULL;
}

struct D2_CelFile* CelFile_RightScreenBorder_GetTop(void) {
  InitRightScreenBorderTop();

  return right_screen_border_top;
}

void CelFile_RightScreenBorder_UnloadTop(void) {
  if (right_screen_border_top == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(right_screen_border_top);
  right_screen_border_top = NULL;
}

struct D2_CelFile* CelFile_RightScreenBorder_GetTopLeft(void) {
  InitRightScreenBorderTopLeft();

  return right_screen_border_top_left;
}

void CelFile_RightScreenBorder_UnloadTopLeft(void) {
  if (right_screen_border_top_left == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(right_screen_border_top_left);
  right_screen_border_top_left = NULL;
}

struct D2_CelFile* CelFile_RightScreenBorder_GetBottom(void) {
  InitRightScreenBorderBottom();

  return right_screen_border_bottom;
}

void CelFile_RightScreenBorder_UnloadBottom(void) {
  if (right_screen_border_bottom == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(right_screen_border_bottom);
  right_screen_border_bottom = NULL;
}

struct D2_CelFile* CelFile_RightScreenBorder_GetBottomLeft(void) {
  InitRightScreenBorderBottomLeft();

  return right_screen_border_bottom_left;
}

void CelFile_RightScreenBorder_UnloadBottomLeft(void) {
  if (right_screen_border_bottom_left == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(right_screen_border_bottom_left);
  right_screen_border_bottom_left = NULL;
}

/**
 * Screen border ribbons
 */

struct D2_CelFile* CelFile_ScreenBorderRibbon_GetHorizontal(void) {
  InitScreenBorderRibbonHorizontal();

  return screen_border_ribbon_horizontal;
}

void CelFile_ScreenBorderRibbon_UnloadHorizontal(void) {
  if (screen_border_ribbon_horizontal == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(screen_border_ribbon_horizontal);
  screen_border_ribbon_horizontal = NULL;
}

struct D2_CelFile* CelFile_ScreenBorderRibbon_GetVertical(void) {
  InitScreenBorderRibbonVertical();

  return screen_border_ribbon_vertical;
}

void CelFile_ScreenBorderRibbon_UnloadVertical(void) {
  if (screen_border_ribbon_vertical == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(screen_border_ribbon_vertical);
  screen_border_ribbon_vertical = NULL;
}
