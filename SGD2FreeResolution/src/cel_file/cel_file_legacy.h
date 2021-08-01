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

#ifndef SGD2FR_CEL_FILE_CEL_FILE_LEGACY_H_
#define SGD2FR_CEL_FILE_CEL_FILE_LEGACY_H_

#include <sgd2mapi.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Left screen border
 */

struct D2_CelFile* CelFile_LeftScreenBorder_GetLeft(void);

void CelFile_LeftScreenBorder_UnloadLeft(void);

const char* CelFile_LeftScreenBorder_GetLeftPath(void);

struct D2_CelFile* CelFile_LeftScreenBorder_GetTop(void);

void CelFile_LeftScreenBorder_UnloadTop(void);

const char* CelFile_LeftScreenBorder_GetTopPath(void);

struct D2_CelFile* CelFile_LeftScreenBorder_GetTopRight(void);

void CelFile_LeftScreenBorder_UnloadTopRight(void);

const char* CelFile_LeftScreenBorder_GetTopRightPath(void);

struct D2_CelFile* CelFile_LeftScreenBorder_GetBottom(void);

void CelFile_LeftScreenBorder_UnloadBottom(void);

const char* CelFile_LeftScreenBorder_GetBottomPath(void);

struct D2_CelFile* CelFile_LeftScreenBorder_GetBottomRight(void);

void CelFile_LeftScreenBorder_UnloadBottomRight(void);

const char* CelFile_LeftScreenBorder_GetBottomRightPath(void);

/**
 * Right screen border
 */

struct D2_CelFile* CelFile_RightScreenBorder_GetRight(void);

void CelFile_RightScreenBorder_UnloadRight(void);

const char* CelFile_RightScreenBorder_GetRightPath(void);

struct D2_CelFile* CelFile_RightScreenBorder_GetTop(void);

void CelFile_RightScreenBorder_UnloadTop(void);

const char* CelFile_RightScreenBorder_GetTopPath(void);

struct D2_CelFile* CelFile_RightScreenBorder_GetTopLeft(void);

void CelFile_RightScreenBorder_UnloadTopLeft(void);

const char* CelFile_RightScreenBorder_GetTopLeftPath(void);

struct D2_CelFile* CelFile_RightScreenBorder_GetBottom(void);

void CelFile_RightScreenBorder_UnloadBottom(void);

const char* CelFile_RightScreenBorder_GetBottomPath(void);

struct D2_CelFile* CelFile_RightScreenBorder_GetBottomLeft(void);

void CelFile_RightScreenBorder_UnloadBottomLeft(void);

const char* CelFile_RightScreenBorder_GetBottomLeftPath(void);

/**
 * Screen border ribbons
 */

struct D2_CelFile* CelFile_ScreenBorderRibbon_GetHorizontal(void);

void CelFile_ScreenBorderRibbon_UnloadHorizontal(void);

const char* CelFile_ScreenBorderRibbon_GetHorizontalPath(void);

struct D2_CelFile* CelFile_ScreenBorderRibbon_GetVertical(void);

void CelFile_ScreenBorderRibbon_UnloadVertical(void);

const char* CelFile_ScreenBorderRibbon_GetVerticalPath(void);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SGD2FR_CEL_FILE_CEL_FILE_LEGACY_H_ */
