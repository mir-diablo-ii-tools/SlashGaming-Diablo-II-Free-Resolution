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

#ifndef SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_SETTING_H_
#define SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_SETTING_H_

#include <stddef.h>

#include "game_resolution.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

size_t Global_GetIngameResolutionMode(void);
void Global_SetIngameResolutionMode(size_t mode);

size_t Global_GetMinConfigResolutionMode(void);
size_t Global_GetMaxConfigResolutionMode(void);

size_t Global_GetMinIngameResolutionMode(void);
size_t Global_GetMaxIngameResolutionMode(void);

size_t Global_GetNumIngameResolutions(void);
void Global_GetIngameResolution(
    struct GameResolution* resolution,
    size_t mode
);

/**
 * Returns the display resolution using the global variables
 * corresponding to the current video mode.
 */
void Global_GetVideoModeDisplayResolution(
    struct GameResolution* resolution
);

unsigned int Global_GetSourceInventoryArrangeMode(void);

const GameResolution& Global_GetSourceInventoryArrangeResolution(void);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_SETTING_H_ */
