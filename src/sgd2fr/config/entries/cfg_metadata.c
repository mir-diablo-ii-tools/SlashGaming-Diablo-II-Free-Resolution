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

#include "sgd2fr/config/entries/cfg_metadata.h"

#include <assert.h>
#include <stddef.h>

#include <cJSON.h>

#include "sgd2fr/config/entries/metadata/cfg_config_version.h"

/**
 * External
 */

struct CfgMetadata* CfgMetadata_InitDefault(struct CfgMetadata* metadata) {
  struct CfgConfigVersion* version_init_result;

  assert(metadata != NULL);

  version_init_result = CfgConfigVersion_InitDefault(&metadata->version);
  if (version_init_result == NULL) {
    goto error;
  }

  return metadata;

error:
  return NULL;
}

struct CfgMetadata* CfgMetadata_FromV1Json(
    struct CfgMetadata* metadata, const cJSON* value) {
  struct CfgConfigVersion* version_from_json_result;

  assert(metadata != NULL);
  assert(value != NULL);

  if (!cJSON_IsObject(value)) {
    goto error;
  }

  version_from_json_result =
      CfgConfigVersion_FromV1Json(&metadata->version, value);
  if (version_from_json_result == NULL) {
    goto error;
  }

  return metadata;

error:
  return NULL;
}

struct CfgMetadata* CfgMetadata_FromV2Json(
    struct CfgMetadata* metadata, const cJSON* value) {
  const char* version_key;
  cJSON* version_json;
  struct CfgConfigVersion* version_from_json_result;

  assert(metadata != NULL);
  assert(value != NULL);

  if (!cJSON_IsObject(value)) {
    goto error;
  }

  version_key = CfgConfigVersion_GetJsonKey(NULL);
  if (!cJSON_HasObjectItem(value, version_key)) {
    goto error;
  }

  version_json = cJSON_GetObjectItemCaseSensitive(value, version_key);
  version_from_json_result =
      CfgConfigVersion_FromV2Json(&metadata->version, version_json);
  if (version_from_json_result == NULL) {
    goto error;
  }

  return metadata;

error:
  return NULL;
}

cJSON* CfgMetadata_AddToJson(
    const struct CfgMetadata* metadata, cJSON* object) {
  const char* key;
  cJSON* metadata_json;
  cJSON* add_config_version_result;

  assert(metadata != NULL);
  assert(object != NULL);

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  key = CfgMetadata_GetJsonKey(NULL);
  metadata_json = cJSON_AddObjectToObject(object, key);
  if (metadata_json == NULL) {
    goto error;
  }

  add_config_version_result =
      CfgConfigVersion_AddToJson(&metadata->version, metadata_json);
  if (add_config_version_result == NULL) {
    goto error_remove_metadata_json;
  }

  return object;

error_remove_metadata_json:
  CfgConfigVersion_RemoveFromJson(object);

error:
  return NULL;
}

int CfgMetadata_Equals(
    const struct CfgMetadata* lhs, const struct CfgMetadata* rhs) {
  return CfgConfigVersion_Equals(&lhs->version, &rhs->version);
}

const char* CfgMetadata_GetJsonKey(size_t* length) {
  static const char kKey[] = "!!!Metadata (Do not modify)!!!";

  if (length != NULL) {
    *length = sizeof(kKey) / sizeof(kKey[0]) - 1;
  }

  return kKey;
}

void CfgMetadata_RemoveFromJson(cJSON* object) {
  const char* key;
  cJSON* metadata_json;

  key = CfgMetadata_GetJsonKey(NULL);
  metadata_json = cJSON_GetObjectItemCaseSensitive(object, key);
  CfgConfigVersion_RemoveFromJson(metadata_json);

  cJSON_DeleteItemFromObjectCaseSensitive(object, key);
}
