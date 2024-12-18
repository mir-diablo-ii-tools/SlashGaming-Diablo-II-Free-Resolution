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

#include "sgd2fr/config/entries/cfg_globals.h"

#include <stddef.h>

#include <cJSON.h>

#include "sgd2fr/config/entries/cfg_indent_width.h"

/**
 * External
 */

struct CfgGlobals* CfgGlobals_InitDefault(struct CfgGlobals* globals) {
  void* result;

  result = CfgIndentWidth_InitDefault(&globals->indent_width);
  if (result == NULL) {
    goto error;
  }

  return globals;

error:
  return NULL;
}

struct CfgGlobals* CfgGlobals_FromJson(
    struct CfgGlobals* globals, const cJSON* object) {
  const cJSON* indent_width_json;
  struct CfgIndentWidth* indent_width_from_json_result;

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  indent_width_json =
      cJSON_GetObjectItemCaseSensitive(object, CfgIndentWidth_kJsonKey);
  if (indent_width_json == NULL) {
    goto error;
  }

  indent_width_from_json_result =
      CfgIndentWidth_FromJson(&globals->indent_width, indent_width_json);
  if (indent_width_from_json_result == NULL) {
    goto error;
  }

  return globals;

error:
  return NULL;
}

int CfgGlobals_Equals(
    const struct CfgGlobals* lhs, const struct CfgGlobals* rhs) {
  return CfgIndentWidth_Equals(&lhs->indent_width, &rhs->indent_width);
}

const char* CfgGlobals_GetJsonKey(size_t* length) {
  static const char kKey[] = "!!!Globals!!!";

  if (length != NULL) {
    *length = sizeof(kKey) / sizeof(kKey[0]) - 1;
  }

  return kKey;
}

void CfgGlobals_RemoveFromJson(cJSON* object) {
  CfgIndentWidth_RemoveFromJson(object);
  cJSON_DeleteItemFromObjectCaseSensitive(object, CfgGlobals_GetJsonKey(NULL));
}
