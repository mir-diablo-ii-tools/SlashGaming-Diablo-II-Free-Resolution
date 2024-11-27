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

#ifndef SGD2FR_CONFIG_ENTRIES_METADATA_CFG_CONFIG_VERSION_H_
#define SGD2FR_CONFIG_ENTRIES_METADATA_CFG_CONFIG_VERSION_H_

#include <stddef.h>

#include <cJSON.h>

#include "sgd2fr/common/semantic_version.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

struct CfgConfigVersion {
  struct SemanticVersion version;
};

/**
 * Parses, sets, and returns the config version from JSON using the format from
 * config versions in the range [3.0.1.0, 3.0.4.X]. Returns NULL if the
 * function fails. Does not set the version if the function fails.
 */
struct CfgConfigVersion* CfgConfigVersion_FromV1Json(
    struct CfgConfigVersion* version, const cJSON* object);

/**
 * Parses, sets, and returns the config version from JSON using the current
 * config version format. Returns the default if the function fails. Does not
 * set the version if the function fails.
 */
struct CfgConfigVersion* CfgConfigVersion_FromV2Json(
    struct CfgConfigVersion* version, const cJSON* object);

cJSON* CfgConfigVersion_AddToJson(
    const struct CfgConfigVersion* version, cJSON* object);

int CfgConfigVersion_Compare(
    const struct CfgConfigVersion* lhs, const struct CfgConfigVersion* rhs);

int CfgConfigVersion_Equals(
    const struct CfgConfigVersion* lhs, const struct CfgConfigVersion* rhs);

const struct CfgConfigVersion* CfgConfigVersion_GetDefault(void);

const char* CfgConfigVersion_GetJsonKey(size_t* length);

void CfgConfigVersion_RemoveFromJson(cJSON* object);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* SGD2FR_CONFIG_ENTRIES_METADATA_CFG_CONFIG_VERSION_H_ */
