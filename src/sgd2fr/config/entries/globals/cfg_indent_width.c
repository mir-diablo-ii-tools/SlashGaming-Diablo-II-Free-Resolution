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

#include "sgd2fr/config/entries/globals/cfg_indent_width.h"

#include <assert.h>
#include <stddef.h>

#include <cJSON.h>

const char CfgIndentWidth_kKey[] = "Config Tab Width";

/**
 * External
 */


const struct CfgIndentWidth* CfgIndentWidth_GetDefault(void) {
  static const struct CfgIndentWidth kDefault = { 4 };
  return &kDefault;
}

struct CfgIndentWidth* CfgIndentWidth_FromJson(
    struct CfgIndentWidth* indent_width, const cJSON* value) {
  assert(indent_width != NULL);
  assert(value != NULL);

  if (!cJSON_IsNumber(value)) {
    *indent_width = *CfgIndentWidth_GetDefault();
    return indent_width;
  }

  if (value->valueint <= 0) {
    *indent_width = *CfgIndentWidth_GetDefault();
    return indent_width;
  }

  indent_width->value = value->valueint;
  return indent_width;
}

void CfgIndentWidth_RemoveFromJson(cJSON* object) {
  cJSON_DeleteItemFromObjectCaseSensitive(object, CfgIndentWidth_kKey);
}

cJSON* CfgIndentWidth_AddToJson(cJSON* object, const struct CfgIndentWidth* indent_width) {
  cJSON* added_entry;

  assert(object != NULL);
  assert(indent_width != NULL);

  added_entry =
      cJSON_AddNumberToObject(
          object, CfgIndentWidth_kKey, indent_width->value);
  if (added_entry == NULL) {
    goto error;
  }

  return object;

error:
  return NULL;
}
