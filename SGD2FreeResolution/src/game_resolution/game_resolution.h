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

#ifndef SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_H_
#define SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_H_

#include <stddef.h>

struct GameResolution {
  int width;
  int height;
};

struct IngameResolutions {
  size_t count;
  struct GameResolution* resolutions;
};

#define GAME_RESOLUTION_640X480 { 640, 480 }
#define GAME_RESOLUTION_800X600 { 800, 600 }
#define GAME_RESOLUTION_856X480 { 856, 480 }
#define GAME_RESOLUTION_1024X768 { 1024, 768 }
#define GAME_RESOLUTION_1068X600 { 1068, 600 }

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const struct GameResolution GameResolution_k640x480;
const struct GameResolution GameResolution_k800x600;
const struct GameResolution GameResolution_k856x480;
const struct GameResolution GameResolution_k1024x768;
const struct GameResolution GameResolution_k1068x600;

enum {
  GameResolution_kDefaultCount = 2,
};

#define GAME_RESOLUTION_DEFAULT \
    { GAME_RESOLUTION_640X480, GAME_RESOLUTION_800X600 }

const struct GameResolution
GameResolution_kDefault[GameResolution_kDefaultCount];

#define INGAME_RESOLUTIONS_DEFAULT \
    { GameResolution_kDefaultCount, GameResolution_kDefault }

const struct IngameResolutions IngameResolution_kDefault;

int GameResolution_Compare(
    const struct GameResolution* resolution1,
    const struct GameResolution* resolution2
);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_H_ */
