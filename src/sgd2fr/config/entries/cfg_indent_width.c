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

#include "sgd2fr/config/entries/cfg_indent_width.h"

#include <assert.h>
#include <stddef.h>

#include <cJSON.h>

/**
 * External
 */

struct CfgIndentWidth* CfgIndentWidth_InitDefault(
    struct CfgIndentWidth* indent_width) {
  assert(indent_width != NULL);

  indent_width->value = 4;

  return indent_width;
}

struct CfgIndentWidth* CfgIndentWidth_FromJson(
    struct CfgIndentWidth* indent_width, const cJSON* value) {
  assert(indent_width != NULL);
  assert(value != NULL);

  if (!cJSON_IsNumber(value)) {
    goto error;
  }

  if (value->valueint <= 0) {
    goto error;
  }

  indent_width->value = value->valueint;
  return indent_width;

error:
  return NULL;
}

cJSON* CfgIndentWidth_AddToJson(
    const struct CfgIndentWidth* indent_width, cJSON* object) {
  cJSON* added_entry;

  assert(indent_width != NULL);
  assert(object != NULL);

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  added_entry =
      cJSON_AddNumberToObject(
          object, CfgIndentWidth_GetJsonKey(NULL), indent_width->value);
  if (added_entry == NULL) {
    goto error;
  }

  return object;

error:
  return NULL;
}

int CfgIndentWidth_Compare(
    const struct CfgIndentWidth* lhs, const struct CfgIndentWidth* rhs) {
  if (lhs == rhs) {
    return 0;
  }

  if (lhs->value < rhs->value) {
    return -1;
  } else if (lhs->value > rhs->value) {
    return 1;
  } else {
    return 0;
  }
}

int CfgIndentWidth_Equals(
    const struct CfgIndentWidth* lhs, const struct CfgIndentWidth* rhs) {
  if (lhs == rhs) {
    return 1;
  }

  return lhs->value == rhs->value;
}

const char* CfgIndentWidth_GetJsonKey(size_t* length) {
  static const char kKey[] = "Config Tab Width";

  if (length != NULL) {
    *length = sizeof(kKey) / sizeof(kKey[0]) - 1;
  }

  return kKey;
}

void CfgIndentWidth_RemoveFromJson(cJSON* object) {
  cJSON_DeleteItemFromObjectCaseSensitive(
      object, CfgIndentWidth_GetJsonKey(NULL));
}
