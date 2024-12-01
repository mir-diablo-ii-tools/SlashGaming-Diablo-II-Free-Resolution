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

#include "sgd2fr/config/entries/metadata/cfg_config_version.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <cJSON.h>

#include "sgd2fr/common/semantic_version.h"

static struct CfgConfigVersion kConfigV1Min = { { 3, 0, 0, 0 } };
static struct CfgConfigVersion kConfigV1Max = { { 3, 0, 4, 0 } };

/**
 * External
 */

struct CfgConfigVersion* CfgConfigVersion_InitDefault(
    struct CfgConfigVersion* version) {
  assert(version != NULL);

  version->value.major_version = 3;
  version->value.minor_version = 2;
  version->value.patch_version = 0;
  version->value.build_version = 0;

  return version;
}

struct CfgConfigVersion* CfgConfigVersion_FromV1Json(
    struct CfgConfigVersion* version, const cJSON* object) {
  static const char kMajorKey[] = "Major Version A";
  static const char kMinorKey[] = "Major Version B";
  static const char kPatchKey[] = "Minor Version A";
  static const char kBuildKey[] = "Minor Version B";

  struct CfgConfigVersion temp_version;
  struct SemanticVersion* inner_version_ptr;
  cJSON* major_json;
  cJSON* minor_json;
  cJSON* patch_json;
  cJSON* build_json;

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  if (!cJSON_HasObjectItem(object, kMajorKey)
      || !cJSON_HasObjectItem(object, kMinorKey)
      || !cJSON_HasObjectItem(object, kPatchKey)
      || !cJSON_HasObjectItem(object, kBuildKey)) {
    goto error;
  }

  major_json = cJSON_GetObjectItemCaseSensitive(object, kMajorKey);
  minor_json = cJSON_GetObjectItemCaseSensitive(object, kMinorKey);
  patch_json = cJSON_GetObjectItemCaseSensitive(object, kPatchKey);
  build_json = cJSON_GetObjectItemCaseSensitive(object, kBuildKey);

  if (!cJSON_IsNumber(major_json)
      || !cJSON_IsNumber(minor_json)
      || !cJSON_IsNumber(patch_json)
      || !cJSON_IsNumber(build_json)) {
    goto error;
  }

  inner_version_ptr = &temp_version.value;

  inner_version_ptr->major_version = cJSON_GetNumberValue(major_json);
  inner_version_ptr->minor_version = cJSON_GetNumberValue(minor_json);
  inner_version_ptr->patch_version = cJSON_GetNumberValue(patch_json);
  inner_version_ptr->build_version = cJSON_GetNumberValue(build_json);

  if (!CfgConfigVersion_IsV1Config(&temp_version)) {
    goto error;
  }

  *version = temp_version;
  return version;

error:
  return NULL;
}

struct CfgConfigVersion* CfgConfigVersion_FromV2Json(
    struct CfgConfigVersion* version, const cJSON* value) {
  char* version_json;
  struct SemanticVersion* from_string_result;

  if (!cJSON_IsString(value)) {
    goto error;
  }

  version_json = cJSON_GetStringValue(value);

  from_string_result =
      SemanticVersion_FromString(
          &version->value, version_json, strlen(version_json));
  if (from_string_result == NULL) {
    goto error;
  }

  return version;

error:
  return NULL;
}

cJSON* CfgConfigVersion_AddToJson(
    const struct CfgConfigVersion* version, cJSON* object) {
  char* version_to_string_result;
  cJSON* add_version_str_result;

  char version_str[SemanticVersion_kMaxLength + 1];

  assert(version != NULL);
  assert(object != NULL);

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  version_to_string_result =
      SemanticVersion_ToString(&version->value, version_str, NULL);
  if (version_to_string_result == NULL) {
    goto error;
  }

  add_version_str_result =
      cJSON_AddStringToObject(
          object, CfgConfigVersion_GetJsonKey(NULL), version_str);
  if (add_version_str_result == NULL) {
    goto error;
  }

  return object;

error:
  return NULL;
}

int CfgConfigVersion_Compare(
    const struct CfgConfigVersion* lhs, const struct CfgConfigVersion* rhs) {
  return SemanticVersion_Compare(&lhs->value, &rhs->value);
}

int CfgConfigVersion_Equals(
    const struct CfgConfigVersion* lhs, const struct CfgConfigVersion* rhs) {
  return SemanticVersion_Equals(&lhs->value, &rhs->value);
}

const char* CfgConfigVersion_GetJsonKey(size_t* length) {
  static const char kKey[] = "Config Version";

  if (length != NULL) {
    *length = sizeof(kKey) / sizeof(kKey[0]) - 1;
  }

  return kKey;
}

int CfgConfigVersion_IsV1Config(const struct CfgConfigVersion* version) {
  return CfgConfigVersion_Compare(version, &kConfigV1Min) >= 0
      && CfgConfigVersion_Compare(version, &kConfigV1Max) <= 0;
}

void CfgConfigVersion_RemoveFromJson(cJSON* object) {
  cJSON_DeleteItemFromObjectCaseSensitive(
      object, CfgConfigVersion_GetJsonKey(NULL));
}
