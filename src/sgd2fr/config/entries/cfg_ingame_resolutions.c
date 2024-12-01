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

#include "sgd2fr/config/entries/cfg_ingame_resolutions.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include <cJSON.h>

#include "sgd2fr/common/resolution.h"

/** Type-safe wrapper of Resolution_Compare for use in qsort and bsearch. */
static int Resolution_CompareAsVoid(const void* lhs, const void* rhs) {
  return Resolution_Compare(lhs, rhs);
}

/**
 * Pushes back an element without checking the size against capacity. Does not
 * reallocate space for the resolutions list.
 */
static void CfgIngameResolutions_PushBackUnchecked(
    struct CfgIngameResolutions* resolutions,
    const struct Resolution* resolution) {
  assert(resolutions != NULL);
  assert(resolution != NULL);

  resolutions->values[resolutions->count] = *resolution;
  ++resolutions->count;
}

/** Removes duplicates from the resolutions list. */
static void CfgIngameResolutions_RemoveDuplicates(
    struct CfgIngameResolutions* resolutions) {
  size_t i_original;
  size_t i_comparing;

  assert(resolutions != NULL);

  if (resolutions->count == 0) {
    return;
  }

  i_original = 0;
  for (i_comparing = 1; i_comparing < resolutions->count; ++i_comparing) {
    struct Resolution* original_resolution;
    struct Resolution* comparing_resolution;

    original_resolution = &resolutions->values[i_original];
    comparing_resolution = &resolutions->values[i_comparing];

    if (Resolution_Equals(original_resolution, comparing_resolution)) {
      continue;
    }

    ++i_original;
    if (i_original != i_comparing) {
      resolutions->values[i_original] = *comparing_resolution;
    }
  }
  resolutions->count = i_original + 1;
}

/** Sorts the resolutions list. */
static void CfgIngameResolutions_Sort(
    struct CfgIngameResolutions* resolutions) {
  qsort(
      resolutions->values,
      resolutions->count,
      sizeof(resolutions->values[0]),
      &Resolution_CompareAsVoid);
}

/**
 * External
 */

struct CfgIngameResolutions* CfgIngameResolutions_FromJson(
    struct CfgIngameResolutions* resolutions, const cJSON* value) {
  struct CfgIngameResolutions temp_resolutions;
  int resolution_count;
  cJSON* resolutions_json;
  cJSON* resolution_json;

  assert(resolutions != NULL);
  assert(value != NULL);

  if (!cJSON_IsArray(value)) {
    goto error;
  }

  resolution_count = cJSON_GetArraySize(value);
  if (resolution_count <= 0) {
    goto error;
  }

  temp_resolutions.values =
      malloc(resolution_count * sizeof(temp_resolutions.values[0]));
  if (temp_resolutions.values == NULL) {
    goto error;
  }
  temp_resolutions.capacity = resolution_count;
  temp_resolutions.count = 0;

  cJSON_ArrayForEach(resolution_json, value) {
    struct Resolution resolution;
    char* resolution_str;
    struct Resolution* from_string_result;

    if (!cJSON_IsString(resolution_json)) {
      goto error_deinit;
    }

    resolution_str = cJSON_GetStringValue(resolution_json);
    from_string_result = Resolution_FromString(&resolution, resolution_str);
    if (from_string_result == NULL) {
      goto error_deinit;
    }

    CfgIngameResolutions_PushBackUnchecked(&temp_resolutions, &resolution);
  }

  CfgIngameResolutions_Sort(&temp_resolutions);
  CfgIngameResolutions_RemoveDuplicates(&temp_resolutions);

  *resolutions = temp_resolutions;
  return resolutions;

error_deinit:
  CfgIngameResolutions_Deinit(&temp_resolutions);

error:
  return NULL;
}

struct CfgIngameResolutions* CfgIngameResolutions_InitDefault(
    struct CfgIngameResolutions* resolutions) {
  static const struct Resolution kDefaultResolutions[] = {
    { 640, 480 },
    { 800, 600 }
  };
  enum {
    kDefaultResolutionCount =
        sizeof(kDefaultResolutions) / sizeof(kDefaultResolutions[0])
  };

  size_t i;
  size_t j;
  struct CfgIngameResolutions temp_resolutions;

  assert(resolutions != NULL);

  temp_resolutions.values =
      malloc(kDefaultResolutionCount * sizeof(resolutions->values[0]));
  if (temp_resolutions.values == NULL) {
    goto error;
  }
  temp_resolutions.capacity = kDefaultResolutionCount;

  /* Add resolutions to the list. */
  temp_resolutions.count = 0;
  for (i = 0; i < kDefaultResolutionCount; ++i) {
    CfgIngameResolutions_PushBackUnchecked(
        &temp_resolutions, &kDefaultResolutions[i]);
  }

  *resolutions = temp_resolutions;
  return resolutions;

error:
  return NULL;
}

void CfgIngameResolutions_Deinit(struct CfgIngameResolutions* resolutions) {
  resolutions->count = 0;
  resolutions->capacity = 0;
  free(resolutions->values);
  resolutions->values = NULL;
}

cJSON* CfgIngameResolutions_AddToJson(
    const struct CfgIngameResolutions* resolutions, cJSON* object) {
  size_t i;
  cJSON* resolutions_json;

  assert(resolutions != NULL);
  assert(object != NULL);

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  resolutions_json =
      cJSON_AddArrayToObject(object, CfgIngameResolutions_GetJsonKey(NULL));
  for (i = 0; i < resolutions->count; ++i) {
    char resolution_str[Resolution_kMaxLength + 1];
    char* to_string_result;

    to_string_result =
        Resolution_ToString(&resolutions->values[i], resolution_str, NULL);
    if (to_string_result == NULL) {
      goto error_remove_from_json;
    }
  }

  return object;

error_remove_from_json:
  CfgIngameResolutions_RemoveFromJson(object);

error:
  return NULL;
}

int CfgIngameResolutions_Equals(
    const struct CfgIngameResolutions* lhs,
    const struct CfgIngameResolutions* rhs) {
  size_t i;

  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 1;
  }

  if (lhs->count != rhs->count) {
    return 0;
  }

  for (i = 0; i < lhs->count; ++i) {
    if (!Resolution_Equals(&lhs->values[i], &rhs->values[i])) {
      return 0;
    }
  }

  return 1;
}

size_t CfgIngameResolutions_FindIndex(
    const struct CfgIngameResolutions* resolutions,
    const struct Resolution* resolution) {
  const struct Resolution* search_result;

  assert(resolutions != NULL);
  assert(resolution != NULL);

  search_result =
      bsearch(
          resolution,
          resolutions->values,
          resolutions->count,
          sizeof(resolutions->values[0]),
          &Resolution_CompareAsVoid);
  if (search_result == NULL) {
    return resolutions->count;
  }

  return (struct Resolution*)search_result - resolutions->values;
}

const char* CfgIngameResolutions_GetJsonKey(size_t* length) {
  static const char kKey[] = "Ingame Resolutions";

  if (length != NULL) {
    *length = sizeof(kKey) / sizeof(kKey[0]) - 1;
  }

  return kKey;
}

void CfgIngameResolutions_RemoveFromJson(cJSON* object) {
  const char* key;
  cJSON* resolutions_json;
  int i;

  assert(object != NULL);

  key = CfgIngameResolutions_GetJsonKey(NULL);
  resolutions_json = cJSON_GetObjectItem(object, key);
  cJSON_Delete(resolutions_json);
}
