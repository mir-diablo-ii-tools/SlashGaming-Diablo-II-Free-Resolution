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

#include "sgd2fr/config/entries/cfg_ingame_resolution.h"

#include <assert.h>
#include <stddef.h>

#include <cJSON.h>

#include "sgd2fr/common/resolution.h"
#include "sgd2fr/config/entries/cfg_ingame_resolutions.h"

/**
 * External
 */

struct CfgIngameResolution* CfgIngameResolution_FromV1Json(
    struct CfgIngameResolution* resolution,
    const cJSON* value,
    const struct CfgIngameResolutions* resolutions) {
  int ingame_resolution_mode;

  assert(resolution != NULL);
  assert(value != NULL);
  assert(resolutions != NULL);
  assert(resolutions->count > 0);

  if (!cJSON_IsNumber(value)) {
    return NULL;
  }

  ingame_resolution_mode = cJSON_GetNumberValue(value);

  if (ingame_resolution_mode < 0
      || (size_t)ingame_resolution_mode >= resolutions->count) {
    return NULL;
  }

  resolution->value = resolutions->values[ingame_resolution_mode];

  return resolution;
}

struct CfgIngameResolution* CfgIngameResolution_FromV2Json(
    struct CfgIngameResolution* resolution,
    const cJSON* value,
    const struct CfgIngameResolutions* resolutions) {
  struct CfgIngameResolution temp_resolution;
  struct Resolution* from_string_result;
  char* resolution_json;
  size_t resolution_index;

  assert(resolution != NULL);
  assert(value != NULL);
  assert(resolutions != NULL);
  assert(resolutions->count > 0);

  if (!cJSON_IsString(value)) {
    resolution->value = resolutions->values[0];
    return resolution;
  }

  resolution_json = cJSON_GetStringValue(value);

  from_string_result =
      Resolution_FromString(&temp_resolution.value, resolution_json);
  if (from_string_result == NULL) {
    resolution->value = resolutions->values[0];
    return resolution;
  }

  resolution_index =
      CfgIngameResolutions_FindIndex(resolutions, &temp_resolution.value);
  if (resolution_index == resolutions->count) {
    resolution->value = resolutions->values[0];
    return resolution;
  }

  *resolution = temp_resolution;
  return resolution;
}

cJSON* CfgIngameResolution_AddToJson(
    const struct CfgIngameResolution* resolution, cJSON* object) {
  assert(resolution != NULL);
  assert(object != NULL);

  char resolution_str[Resolution_kMaxLength + 1];
  char* to_string_result;
  cJSON* add_string_result;

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  to_string_result =
      Resolution_ToString(&resolution->value, resolution_str, NULL);
  if (to_string_result == NULL) {
    goto error;
  }

  add_string_result =
      cJSON_AddStringToObject(
          object, CfgIngameResolution_GetJsonKey(NULL), resolution_str);
  if (add_string_result == NULL) {
    goto error;
  }

  return object;

error:
  return NULL;
}

int CfgIngameResolution_Compare(
    const struct CfgIngameResolution *lhs,
    const struct CfgIngameResolution *rhs) {
  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 0;
  }

  return Resolution_Compare(&lhs->value, &rhs->value);
}

int CfgIngameResolution_Equals(
    const struct CfgIngameResolution* lhs,
    const struct CfgIngameResolution* rhs) {
  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 1;
  }

  return Resolution_Equals(&lhs->value, &rhs->value);
}

const char* CfgIngameResolution_GetJsonKey(size_t* length) {
  static const char kKey[] = "Ingame Resolution";

  if (length != NULL) {
    *length = sizeof(kKey) / sizeof(kKey[0]) - 1;
  }

  return kKey;
}

void CfgIngameResolution_RemoveFromJson(cJSON* object) {
  assert(object != NULL);

  cJSON_DeleteItemFromObjectCaseSensitive(
      object, CfgIngameResolution_GetJsonKey(NULL));
}
