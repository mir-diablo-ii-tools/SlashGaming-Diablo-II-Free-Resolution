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

#include "sgd2fr/config/cfg_entries.h"

#include <assert.h>
#include <stddef.h>

#include <cJSON.h>

#include "sgd2fr/config/entries/cfg_custom_mpq_file_path.h"
#include "sgd2fr/config/entries/cfg_globals.h"
#include "sgd2fr/config/entries/cfg_indent_width.h"
#include "sgd2fr/config/entries/cfg_ingame_resolution.h"
#include "sgd2fr/config/entries/cfg_ingame_resolutions.h"
#include "sgd2fr/config/entries/cfg_main_menu_resolution.h"
#include "sgd2fr/config/entries/cfg_metadata.h"

#define ENTRY_FROM_JSON_OR_DEFAULT( \
    entry_ptr, json_object, json_key, from_json_func, init_default_func) \
        { \
          const cJSON* entry_json; \
          void* from_json_result;\
          if (cJSON_HasObjectItem(json_object, json_key)) { \
            entry_json = \
                cJSON_GetObjectItemCaseSensitive(json_object, json_key); \
            from_json_result = from_json_func(entry_ptr, entry_json); \
            if (from_json_result == NULL) { \
              init_default_func(entry_ptr); \
            } \
          } else { \
            init_default_func(entry_ptr); \
          } \
        }

static const char kMainV1Key[] = "SlashGaming Diablo II Free Resolution";

/**
 * External
 */

struct CfgEntries* CfgEntries_InitDefault(struct CfgEntries* entries) {
  void* result;

  result = CfgMetadata_InitDefault(&entries->metadata);
  if (result == NULL) {
    goto error;
  }

  result =
      CfgCustomMpqFilePath_InitDefault(&entries->custom_mpq_file_path);
  if (result == NULL) {
    goto error;
  }

  result = CfgIndentWidth_InitDefault(&entries->indent_width);
  if (result == NULL) {
    goto error;
  }

  result = CfgIngameResolutions_InitDefault(&entries->ingame_resolutions);
  if (result == NULL) {
    goto error;
  }

  entries->ingame_resolution.value = entries->ingame_resolutions.values[0];

  result =
      CfgMainMenuResolution_InitDefault(&entries->main_menu_resolution);
  if (result == NULL) {
    goto error;
  }

  return entries;

error:
  return NULL;
}

struct CfgEntries* CfgEntries_FromV1Json(
    struct CfgEntries* entries, const cJSON* value) {
  cJSON* main_json;
  struct CfgGlobals globals;
  const char* entry_key;
  const cJSON* entry_json;
  void* from_json_result;

  if (!cJSON_IsObject(value)) {
    goto error;
  }

  if (!cJSON_HasObjectItem(value, kMainV1Key)) {
    goto error;
  }

  main_json = cJSON_GetObjectItemCaseSensitive(value, kMainV1Key);
  if (!cJSON_IsObject(main_json)) {
    goto error;
  }

  /* CfgEntries.metadata */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->metadata,
      main_json,
      CfgMetadata_kJsonKey,
      CfgMetadata_FromV1Json,
      CfgMetadata_InitDefault);

  /* CfgEntries.custom_mpq_file_path */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->custom_mpq_file_path,
      main_json,
      CfgCustomMpqFilePath_kJsonKey,
      CfgCustomMpqFilePath_FromJson,
      CfgCustomMpqFilePath_InitDefault);

  /* CfgEntries.indent_width */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &globals,
      value,
      CfgGlobals_kJsonKey,
      CfgGlobals_FromJson,
      CfgGlobals_InitDefault);
  entries->indent_width = globals.indent_width;

  /* CfgEntries.ingame_resolutions */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->ingame_resolutions,
      main_json,
      CfgIngameResolutions_kJsonKey,
      CfgIngameResolutions_FromJson,
      CfgIngameResolutions_InitDefault);

  /* CfgEntries.ingame_resolution */
  if (cJSON_HasObjectItem(
          main_json, CfgIngameResolution_kV1JsonKey)) {
    entry_json =
        cJSON_GetObjectItemCaseSensitive(
            main_json, CfgIngameResolution_kV1JsonKey);
    from_json_result =
        CfgIngameResolution_FromV1Json(
            &entries->ingame_resolution,
            entry_json,
            &entries->ingame_resolutions);
    if (from_json_result == NULL) {
      CfgIngameResolution_InitDefault(
          &entries->ingame_resolution, &entries->ingame_resolutions);
    }
  } else {
    CfgIngameResolution_InitDefault(
        &entries->ingame_resolution, &entries->ingame_resolutions);
  }

  /* CfgEntries.main_menu_resolution */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->main_menu_resolution,
      main_json,
      CfgMainMenuResolution_kJsonKey,
      CfgMainMenuResolution_FromJson,
      CfgMainMenuResolution_InitDefault);

  return entries;

error:
  return NULL;
}

struct CfgEntries* CfgEntries_FromV2Json(
    struct CfgEntries* entries, const cJSON* value) {
  const cJSON* entry_json;
  void* from_json_result;

  if (!cJSON_IsObject(value)) {
    goto error;
  }

  /* CfgEntries.metadata */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->metadata,
      value,
      CfgMetadata_kJsonKey,
      CfgMetadata_FromV2Json,
      CfgMetadata_InitDefault);

  /* CfgEntries.custom_mpq_file_path */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->custom_mpq_file_path,
      value,
      CfgCustomMpqFilePath_kJsonKey,
      CfgCustomMpqFilePath_FromJson,
      CfgCustomMpqFilePath_InitDefault);

  /* CfgEntries.indent_width */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->indent_width,
      value,
      CfgIndentWidth_kJsonKey,
      CfgIndentWidth_FromJson,
      CfgIndentWidth_InitDefault);

  /* CfgEntries.ingame_resolutions */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->ingame_resolutions,
      value,
      CfgIngameResolutions_kJsonKey,
      CfgIngameResolutions_FromJson,
      CfgIngameResolutions_InitDefault);

  /* CfgEntries.ingame_resolution */
  if (cJSON_HasObjectItem(value, CfgIngameResolution_kV2JsonKey)) {
    entry_json = cJSON_GetObjectItemCaseSensitive(value, CfgIngameResolution_kV2JsonKey);
    from_json_result =
        CfgIngameResolution_FromV2Json(
            &entries->ingame_resolution,
            entry_json,
            &entries->ingame_resolutions);
    if (from_json_result == NULL) {
      CfgIngameResolution_InitDefault(
          &entries->ingame_resolution, &entries->ingame_resolutions);
    }
  } else {
    CfgIngameResolution_InitDefault(
        &entries->ingame_resolution, &entries->ingame_resolutions);
  }

  /* CfgEntries.main_menu_resolution */
  ENTRY_FROM_JSON_OR_DEFAULT(
      &entries->main_menu_resolution,
      value,
      CfgMainMenuResolution_kJsonKey,
      CfgMainMenuResolution_FromJson,
      CfgMainMenuResolution_InitDefault);

  return entries;

error:
  return NULL;
}

void CfgEntries_Deinit(struct CfgEntries *entries) {
  CfgIngameResolutions_Deinit(&entries->ingame_resolutions);
}

cJSON* CfgEntries_AddToJson(const struct CfgEntries* entries, cJSON* object) {
  cJSON* result;

  result = CfgMetadata_AddToJson(&entries->metadata, object);
  if (result == NULL) {
    goto error;
  }

  result =
      CfgCustomMpqFilePath_AddToJson(&entries->custom_mpq_file_path, object);
  if (result == NULL) {
    goto error_remove_metadata_json;
  }

  result = CfgIndentWidth_AddToJson(&entries->indent_width, object);
  if (result == NULL) {
    goto error_remove_indent_width_json;
  }

  result =
      CfgIngameResolutions_AddToJson(&entries->ingame_resolutions, object);
  if (result == NULL) {
    goto error_remove_indent_width_json;
  }

  result = CfgIngameResolution_AddToJson(&entries->ingame_resolution, object);
  if (result == NULL) {
    goto error_remove_ingame_resolutions_json;
  }

  result =
      CfgMainMenuResolution_AddToJson(&entries->main_menu_resolution, object);
  if (result == NULL) {
    goto error_remove_ingame_resolution_json;
  }

  return object;

error_remove_ingame_resolution_json:
  CfgIngameResolution_RemoveFromJson(object);

error_remove_ingame_resolutions_json:
  CfgIngameResolutions_RemoveFromJson(object);

error_remove_indent_width_json:
  CfgIndentWidth_RemoveFromJson(object);

error_remove_custom_mpq_file_path_json:
  CfgCustomMpqFilePath_RemoveFromJson(object);

error_remove_metadata_json:
  CfgMetadata_RemoveFromJson(object);

error:
  return NULL;
}

int CfgEntries_Equals(
    const struct CfgEntries* lhs, const struct CfgEntries* rhs) {
  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 1;
  }

  if (!CfgMetadata_Equals(&lhs->metadata, &rhs->metadata)) {
    return 0;
  }

  if (!CfgCustomMpqFilePath_Equals(
          &lhs->custom_mpq_file_path, &rhs->custom_mpq_file_path)) {
    return 0;
  }

  if (!CfgIndentWidth_Equals(&lhs->indent_width, &rhs->indent_width)) {
    return 0;
  }

  if (!CfgIngameResolutions_Equals(
          &lhs->ingame_resolutions, &rhs->ingame_resolutions)) {
    return 0;
  }

  if (!CfgIngameResolution_Equals(
          &lhs->ingame_resolution, &rhs->ingame_resolution)) {
    return 0;
  }

  if (!CfgMainMenuResolution_Equals(
          &lhs->main_menu_resolution, &rhs->main_menu_resolution)) {
    return 0;
  }

  return 1;
}
