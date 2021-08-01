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

#include "../compile_time_switch.h"

#define DEFAULT_LEFT_SCREEN_BORDER_LEFT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderInterfaceLeft"
#define DEFAULT_LEFT_SCREEN_BORDER_TOP_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderTopLeft"
#define DEFAULT_LEFT_SCREEN_BORDER_TOP_RIGHT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerTopLeft"
#define DEFAULT_LEFT_SCREEN_BORDER_BOTTOM_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderBottomLeft"
#define DEFAULT_LEFT_SCREEN_BORDER_BOTTOM_RIGHT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerBottomLeft"

#define DEFAULT_RIGHT_SCREEN_BORDER_RIGHT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderInterfaceRight"
#define DEFAULT_RIGHT_SCREEN_BORDER_TOP_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderTopRight"
#define DEFAULT_RIGHT_SCREEN_BORDER_TOP_LEFT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerTopRight"
#define DEFAULT_RIGHT_SCREEN_BORDER_BOTTOM_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderBottomRight"
#define DEFAULT_RIGHT_SCREEN_BORDER_BOTTOM_LEFT_PATH \
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerBottomRight"

#define DEFAULT_SCREEN_BORDER_RIBBON_HORIZONTAL \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyHorizontalBar"
#define DEFAULT_SCREEN_BORDER_RIBBON_VERTICAL \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyVerticalBar"

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
      DEFAULT_LEFT_SCREEN_BORDER_LEFT_PATH,
      0
  );
}

static void InitLeftScreenBorderTop(void) {
  if (left_screen_border_top != NULL) {
    return;
  }

  left_screen_border_top = D2_D2Win_LoadCelFile(
      DEFAULT_LEFT_SCREEN_BORDER_TOP_PATH,
      0
  );
}

static void InitLeftScreenBorderTopRight(void) {
  if (left_screen_border_top_right != NULL) {
    return;
  }

  left_screen_border_top_right = D2_D2Win_LoadCelFile(
      DEFAULT_LEFT_SCREEN_BORDER_TOP_RIGHT_PATH,
      0
  );
}

static void InitLeftScreenBorderBottom(void) {
  if (left_screen_border_bottom != NULL) {
    return;
  }

  left_screen_border_bottom = D2_D2Win_LoadCelFile(
      DEFAULT_LEFT_SCREEN_BORDER_BOTTOM_PATH,
      0
  );
}

static void InitLeftScreenBorderBottomRight(void) {
  if (left_screen_border_bottom_right != NULL) {
    return;
  }

  left_screen_border_bottom_right = D2_D2Win_LoadCelFile(
      DEFAULT_LEFT_SCREEN_BORDER_BOTTOM_RIGHT_PATH,
      0
  );
}

static void InitRightScreenBorderRight(void) {
  if (right_screen_border_right != NULL) {
    return;
  }

  right_screen_border_right = D2_D2Win_LoadCelFile(
      DEFAULT_RIGHT_SCREEN_BORDER_RIGHT_PATH,
      0
  );
}

static void InitRightScreenBorderTop(void) {
  if (right_screen_border_top != NULL) {
    return;
  }

  right_screen_border_top = D2_D2Win_LoadCelFile(
      DEFAULT_RIGHT_SCREEN_BORDER_TOP_PATH,
      0
  );
}

static void InitRightScreenBorderTopLeft(void) {
  if (right_screen_border_top_left != NULL) {
    return;
  }

  right_screen_border_top_left = D2_D2Win_LoadCelFile(
      DEFAULT_RIGHT_SCREEN_BORDER_TOP_LEFT_PATH,
      0
  );
}

static void InitRightScreenBorderBottom(void) {
  if (right_screen_border_bottom != NULL) {
    return;
  }

  right_screen_border_bottom = D2_D2Win_LoadCelFile(
      DEFAULT_RIGHT_SCREEN_BORDER_BOTTOM_PATH,
      0
  );
}

static void InitRightScreenBorderBottomLeft(void) {
  if (right_screen_border_bottom_left != NULL) {
    return;
  }

  right_screen_border_bottom_left = D2_D2Win_LoadCelFile(
      DEFAULT_RIGHT_SCREEN_BORDER_BOTTOM_LEFT_PATH,
      0
  );
}

static void InitScreenBorderRibbonHorizontal(void) {
  if (screen_border_ribbon_horizontal != NULL) {
    return;
  }

  screen_border_ribbon_horizontal = D2_D2Win_LoadCelFile(
      DEFAULT_SCREEN_BORDER_RIBBON_HORIZONTAL,
      0
  );
}

static void InitScreenBorderRibbonVertical(void) {
  if (screen_border_ribbon_vertical != NULL) {
    return;
  }

  screen_border_ribbon_vertical = D2_D2Win_LoadCelFile(
      DEFAULT_SCREEN_BORDER_RIBBON_VERTICAL,
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

const char* CelFile_LeftScreenBorder_GetLeftPath(void) {
  return DEFAULT_LEFT_SCREEN_BORDER_LEFT_PATH;
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

const char* CelFile_LeftScreenBorder_GetTopPath(void) {
  return DEFAULT_LEFT_SCREEN_BORDER_TOP_PATH;
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

const char* CelFile_LeftScreenBorder_GetTopRightPath(void) {
  return DEFAULT_LEFT_SCREEN_BORDER_TOP_RIGHT_PATH;
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

const char* CelFile_LeftScreenBorder_GetBottomPath(void) {
  return DEFAULT_LEFT_SCREEN_BORDER_BOTTOM_PATH;
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

const char* CelFile_LeftScreenBorder_GetBottomRightPath(void) {
  return DEFAULT_LEFT_SCREEN_BORDER_BOTTOM_RIGHT_PATH;
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

const char* CelFile_RightScreenBorder_GetRightPath(void) {
  return DEFAULT_RIGHT_SCREEN_BORDER_RIGHT_PATH;
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

const char* CelFile_RightScreenBorder_GetTopPath(void) {
  return DEFAULT_RIGHT_SCREEN_BORDER_TOP_PATH;
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

const char* CelFile_RightScreenBorder_GetTopLeftPath(void) {
  return DEFAULT_RIGHT_SCREEN_BORDER_TOP_LEFT_PATH;
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

const char* CelFile_RightScreenBorder_GetBottomPath(void) {
  return DEFAULT_RIGHT_SCREEN_BORDER_BOTTOM_PATH;
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

const char* CelFile_RightScreenBorder_GetBottomLeftPath(void) {
  return DEFAULT_RIGHT_SCREEN_BORDER_BOTTOM_LEFT_PATH;
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

const char* CelFile_ScreenBorderRibbon_GetHorizontalPath(void) {
  return DEFAULT_SCREEN_BORDER_RIBBON_HORIZONTAL;
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

const char* CelFile_ScreenBorderRibbon_GetVerticalPath(void) {
  return DEFAULT_SCREEN_BORDER_RIBBON_VERTICAL;
}
