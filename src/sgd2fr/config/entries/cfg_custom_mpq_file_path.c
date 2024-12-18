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

#include "sgd2fr/config/entries/cfg_custom_mpq_file_path.h"
#include "vcruntime.h"

#include <assert.h>
#include <stddef.h>
#include <wchar.h>
#include <windows.h>

#include <cJSON.h>
#include <mdc/wchar_t/wide_decoding.h>
#include <mdc/wchar_t/wide_encoding.h>

#define DEFAULT_PATH L"SGD2FreeRes.mpq"
static const wchar_t kDefaultPath[] = DEFAULT_PATH;
enum {
  kDefaultPathLength = sizeof(DEFAULT_PATH) / sizeof(DEFAULT_PATH[0]) - 1
};
static const struct CfgCustomMpqFilePath kDefaultMpqFilePath = {
  DEFAULT_PATH, kDefaultPathLength
};

/**
 * External
 */

const char CfgCustomMpqFilePath_kJsonKey[] = "Custom MPQ File";

struct CfgCustomMpqFilePath* CfgCustomMpqFilePath_InitDefault(
    struct CfgCustomMpqFilePath* path) {
  assert(path != NULL);

  *path = kDefaultMpqFilePath;

  return path;
}

struct CfgCustomMpqFilePath* CfgCustomMpqFilePath_FromJson(
    struct CfgCustomMpqFilePath* path, const cJSON* value) {
  size_t temp_length;
  char* value_as_str;
  wchar_t* decode_result;

  assert(path != NULL);
  assert(value != NULL);

  if (!cJSON_IsString(value)) {
    goto error;
  }

  value_as_str = cJSON_GetStringValue(value);

  temp_length = Mdc_Wide_DecodeUtf8Length(value_as_str);
  if (temp_length <= 0 || temp_length >= MAX_PATH) {
    goto error;
  }

  decode_result = Mdc_Wide_DecodeUtf8(path->str, value_as_str);
  if (decode_result == NULL) {
    goto error;
  }

  path->length = temp_length;
  return path;

error:
  return NULL;
}

cJSON* CfgCustomMpqFilePath_AddToJson(
    const struct CfgCustomMpqFilePath* path, cJSON* object) {
  char utf8_path[MAX_PATH];
  char* encode_result;
  cJSON* add_result;

  assert(path != NULL);
  assert(object != NULL);

  if (!cJSON_IsObject(object)) {
    goto error;
  }

  encode_result = Mdc_Wide_EncodeUtf8(utf8_path, path->str);
  if (encode_result == NULL) {
    goto error;
  }

  add_result =
      cJSON_AddStringToObject(
          object, CfgCustomMpqFilePath_kJsonKey, utf8_path);
  if (add_result == NULL) {
    goto error;
  }

  return object;

error:
  return NULL;
}

int CfgCustomMpqFilePath_Compare(
    const struct CfgCustomMpqFilePath* lhs,
    const struct CfgCustomMpqFilePath* rhs) {
  size_t shorter_length;

  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 0;
  }

  shorter_length = (lhs->length < rhs->length) ? lhs->length : rhs->length;
  return wmemcmp(lhs->str, rhs->str, shorter_length + 1);
}

int CfgCustomMpqFilePath_Equals(
    const struct CfgCustomMpqFilePath* lhs,
    const struct CfgCustomMpqFilePath* rhs) {
  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 1;
  }

  if (lhs->length != rhs->length) {
    return 0;
  }

  return wmemcmp(lhs->str, rhs->str, lhs->length) == 0;
}

const char* CfgCustomMpqFilePath_GetJsonKey(size_t* length) {
  if (length != NULL) {
    *length =
        sizeof(CfgCustomMpqFilePath_kJsonKey)
            / sizeof(CfgCustomMpqFilePath_kJsonKey[0]) - 1;
  }

  return CfgCustomMpqFilePath_kJsonKey;
}

void CfgCustomMpqFilePath_RemoveFromJson(cJSON* object) {
  cJSON_DeleteItemFromObject(object, CfgCustomMpqFilePath_kJsonKey);
}
