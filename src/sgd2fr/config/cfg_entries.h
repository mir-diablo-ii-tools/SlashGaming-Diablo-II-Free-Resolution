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

#ifndef SGD2FR_CONFIG_CFG_CONFIG_ENTRIES_H_
#define SGD2FR_CONFIG_CFG_CONFIG_ENTRIES_H_

#include <stddef.h>

#include <cJSON.h>

#include "sgd2fr/config/entries/cfg_custom_mpq_file_path.h"
#include "sgd2fr/config/entries/cfg_indent_width.h"
#include "sgd2fr/config/entries/cfg_ingame_resolution.h"
#include "sgd2fr/config/entries/cfg_ingame_resolutions.h"
#include "sgd2fr/config/entries/cfg_main_menu_resolution.h"
#include "sgd2fr/config/entries/cfg_metadata.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

struct CfgEntries {
  struct CfgMetadata metadata;
  struct CfgCustomMpqFilePath custom_mpq_file_path;
  struct CfgIndentWidth indent_width;
  struct CfgIngameResolutions ingame_resolutions;
  struct CfgIngameResolution ingame_resolution;
  struct CfgMainMenuResolution main_menu_resolution;
};

struct CfgEntries* CfgEntries_InitDefault(struct CfgEntries* entries);

/**
 * Parses, sets, and returns the config entries using the format from
 * config versions in the range [3.0.1.0, 3.0.4.X].
 *
 * Function fails if the key "SlashGaming Diablo II Free Resolution" is not
 * present at the root of the config as an object. Otherwise, sets missing
 * fields to defaults, and indicates success.
 *
 * Returns NULL if the function fails. Does not set the config entries if the
 * function fails.
 */
struct CfgEntries* CfgEntries_FromV1Json(
    struct CfgEntries* entries, const cJSON* value);

/**
 * Parses, sets, and returns the config entries using the current config
 * format. Returns NULL and does not set the config entries if the function
 * fails. Missing fields are set to defaults.
 */
struct CfgEntries* CfgEntries_FromV2Json(
    struct CfgEntries* entries, const cJSON* value);

void CfgEntries_Deinit(struct CfgEntries* entries);

cJSON* CfgEntries_AddToJson(const struct CfgEntries* entries, cJSON* object);

int CfgEntries_Equals(
    const struct CfgEntries* lhs, const struct CfgEntries* rhs);

void CfgEntries_RemoveFromJson(cJSON* object);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* SGD2FR_CONFIG_CFG_CONFIG_ENTRIES_H_ */
