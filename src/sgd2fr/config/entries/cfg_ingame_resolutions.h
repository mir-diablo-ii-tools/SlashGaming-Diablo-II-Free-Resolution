/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2024  Mir Drualga
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

#ifndef SGD2FR_CONFIG_ENTRIES_CFG_INGAME_RESOLUTIONS_H_
#define SGD2FR_CONFIG_ENTRIES_CFG_INGAME_RESOLUTIONS_H_

#include <stddef.h>

#include <cJSON.h>

#include "sgd2fr/common/resolution.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/** A contiguous, sorted set of resolutions. */
struct CfgIngameResolutions {
  struct Resolution* values;
  size_t capacity;
  size_t count;
};

extern const char CfgIngameResolutions_kJsonKey[];

struct CfgIngameResolutions* CfgIngameResolutions_InitDefault(
    struct CfgIngameResolutions* resolutions);

/**
 * Parses, sets, and returns the ingame resolutions from a JSON array. Returns
 * NULL and does not set the ingame resolutions if the function fails.
 */
struct CfgIngameResolutions* CfgIngameResolutions_FromJson(
    struct CfgIngameResolutions* resolutions, const cJSON* value);

void CfgIngameResolutions_Deinit(struct CfgIngameResolutions* resolutions);

cJSON* CfgIngameResolutions_AddToJson(
    const struct CfgIngameResolutions* resolutions, cJSON* object);

int CfgIngameResolutions_Equals(
    const struct CfgIngameResolutions* lhs,
    const struct CfgIngameResolutions* rhs);

/** Returns the index in the resolutions set for the specified resolution. */
size_t CfgIngameResolutions_FindIndex(
    const struct CfgIngameResolutions* resolutions,
    const struct Resolution* resolution);

const char* CfgIngameResolutions_GetJsonKey(size_t* length);

void CfgIngameResolutions_RemoveFromJson(cJSON* object);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* SGD2FR_CONFIG_ENTRIES_CFG_INGAME_RESOLUTIONS_H_ */
