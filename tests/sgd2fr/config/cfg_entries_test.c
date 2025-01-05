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

#include "sgd2fr/config/cfg_entries_test.h"

#include <stddef.h>
#include <string.h>
#include <wchar.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/common/resolution.h"
#include "sgd2fr/config/cfg_entries.h"
#include "sgd2fr/config/entries/cfg_custom_mpq_file_path.h"
#include "sgd2fr/config/entries/cfg_globals.h"
#include "sgd2fr/config/entries/cfg_indent_width.h"
#include "sgd2fr/config/entries/cfg_ingame_resolution.h"
#include "sgd2fr/config/entries/cfg_ingame_resolutions.h"
#include "sgd2fr/config/entries/cfg_main_menu_resolution.h"
#include "sgd2fr/config/entries/cfg_metadata.h"
#include "sgd2fr/config/entries/metadata/cfg_config_version.h"

static const char kMainV1Key[] = "SlashGaming Diablo II Free Resolution";

static const struct Resolution kIngameResolutions[] = {
  { 2420, 4240 }, { 4240, 2420 }
};
static const struct CfgEntries kEntries = {
  { { { 3, 1, 42, 1337 } } },
  { L"file.mpq", 8 },
  { 42 },
  { (struct Resolution*)kIngameResolutions, 2, 2 },
  { { 4240, 2420 } },
  { { 1200, 900 } }
};

static void InitDefault_ReturnsDefault(CuTest* tc) {
  const struct Resolution expected_ingame_resolutions[] = {
    { 640, 480 }, { 800, 600 }
  };
  const struct CfgEntries expected = {
    { { { 3, 1, 0, 0 } } },
    { L"SGD2FreeRes.mpq", 15 },
    { 4 },
    { (struct Resolution*)expected_ingame_resolutions, 2, 2 },
    { { 640, 480 } },
    { { 800, 600 } }
  };
  struct CfgEntries entries;
  struct CfgEntries* result;

  result = CfgEntries_InitDefault(&entries);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgEntries_Equals(&entries, &expected));

  CfgEntries_Deinit(&entries);
}

static void FromV1Json_Valid_ReturnsEntries(CuTest* tc) {
  cJSON* entries_json;
  cJSON* sgd2fr_json;
  cJSON* metadata_json;
  cJSON* ingame_resolutions_json;
  cJSON* globals_json;
  struct CfgEntries entries;
  struct CfgEntries* result;
  struct CfgEntries expected;

  expected = kEntries;
  expected.metadata.version.value.major_version = 3;
  expected.metadata.version.value.minor_version = 0;
  expected.metadata.version.value.patch_version = 4;
  expected.metadata.version.value.build_version = 0;
  entries_json = cJSON_CreateObject();
  sgd2fr_json = cJSON_AddObjectToObject(entries_json, kMainV1Key);
  metadata_json =
      cJSON_AddObjectToObject(sgd2fr_json, CfgMetadata_kJsonKey);
  cJSON_AddNumberToObject(metadata_json, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(metadata_json, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(metadata_json, CfgConfigVersion_kV1PatchJsonKey, 4);
  cJSON_AddNumberToObject(metadata_json, CfgConfigVersion_kV1BuildJsonKey, 0);
  ingame_resolutions_json =
      cJSON_AddArrayToObject(sgd2fr_json, CfgIngameResolutions_kJsonKey);
  cJSON_AddItemToArray(
      ingame_resolutions_json, cJSON_CreateString("2420x4240"));
  cJSON_AddItemToArray(
      ingame_resolutions_json, cJSON_CreateString("4240x2420"));
  cJSON_AddNumberToObject(sgd2fr_json, CfgIngameResolution_kV1JsonKey, 1);
  cJSON_AddStringToObject(
      sgd2fr_json, CfgMainMenuResolution_kJsonKey, "1200x900");
  cJSON_AddStringToObject(
      sgd2fr_json, CfgCustomMpqFilePath_kJsonKey, "file.mpq");
  globals_json = cJSON_AddObjectToObject(entries_json, CfgGlobals_kJsonKey);
  cJSON_AddNumberToObject(globals_json, CfgIndentWidth_kJsonKey, 42);
  /* Unused entries that were valid in the version 1 format. */
  cJSON_AddTrueToObject(sgd2fr_json, "Enable Screen Border Frame?");
  cJSON_AddFalseToObject(sgd2fr_json, "Use Original Screen Border Frame?");
  cJSON_AddTrueToObject(sgd2fr_json, "Use 800 Interface Bar?");

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgEntries_Equals(&entries, &expected));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void FromV1Json_EntriesTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  entries_json = cJSON_CreateTrue();

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(entries_json);
}

static void FromV1Json_Sgd2frMissing_ReturnsNull(CuTest* tc) {
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  entries_json = cJSON_CreateObject();

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(entries_json);
}

static void FromV1Json_Sgd2frTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  entries_json = cJSON_CreateObject();
  cJSON_AddTrueToObject(entries_json, kMainV1Key);

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(entries_json);
}

static void
FromV1Json_Sgd2frSubentriesMissing_ReturnsEntriesWithDefaultSubentries(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  cJSON* sgd2fr_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddObjectToObject(entries_json, kMainV1Key);

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc,
      CfgMetadata_Equals(&entries.metadata, &default_entries.metadata));
  CuAssertTrue(
      tc,
      CfgCustomMpqFilePath_Equals(
          &entries.custom_mpq_file_path,
          &default_entries.custom_mpq_file_path));
  CuAssertTrue(
      tc,
      CfgIngameResolutions_Equals(
          &entries.ingame_resolutions, &default_entries.ingame_resolutions));
  CuAssertTrue(
      tc,
      CfgIngameResolution_Equals(
          &entries.ingame_resolution, &default_entries.ingame_resolution));
  CuAssertTrue(
      tc,
      CfgMainMenuResolution_Equals(
          &entries.main_menu_resolution,
          &default_entries.main_menu_resolution));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV1Json_Sgd2frSubentriesTypeMismatch_ReturnsEntriesWithDefaultSubentries(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  cJSON* sgd2fr_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  sgd2fr_json = cJSON_AddObjectToObject(entries_json, kMainV1Key);
  cJSON_AddNullToObject(sgd2fr_json, CfgMetadata_kJsonKey);
  cJSON_AddNullToObject(sgd2fr_json, CfgIngameResolutions_kJsonKey);
  cJSON_AddNullToObject(sgd2fr_json, CfgIngameResolution_kV1JsonKey);
  cJSON_AddNullToObject(sgd2fr_json, CfgMainMenuResolution_kJsonKey);
  cJSON_AddNullToObject(sgd2fr_json, CfgCustomMpqFilePath_kJsonKey);
  /* Unused entries that were valid in the version 1 format. */
  cJSON_AddNullToObject(sgd2fr_json, "Enable Screen Border Frame?");
  cJSON_AddNullToObject(sgd2fr_json, "Use Original Screen Border Frame?");
  cJSON_AddNullToObject(sgd2fr_json, "Use 800 Interface Bar?");

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc,
      CfgMetadata_Equals(&entries.metadata, &default_entries.metadata));
  CuAssertTrue(
      tc,
      CfgCustomMpqFilePath_Equals(
          &entries.custom_mpq_file_path,
          &default_entries.custom_mpq_file_path));
  CuAssertTrue(
      tc,
      CfgIngameResolutions_Equals(
          &entries.ingame_resolutions, &default_entries.ingame_resolutions));
  CuAssertTrue(
      tc,
      CfgIngameResolution_Equals(
          &entries.ingame_resolution, &default_entries.ingame_resolution));
  CuAssertTrue(
      tc,
      CfgMainMenuResolution_Equals(
          &entries.main_menu_resolution,
          &default_entries.main_menu_resolution));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void FromV1Json_GlobalsMissing_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddObjectToObject(entries_json, kMainV1Key);
  cJSON_AddTrueToObject(entries_json, CfgGlobals_kJsonKey);

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgIndentWidth_Equals(
          &entries.indent_width, &default_entries.indent_width));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void FromV1Json_GlobalsTypeMismatch_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddObjectToObject(entries_json, kMainV1Key);

  result = CfgEntries_FromV1Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgIndentWidth_Equals(
          &entries.indent_width, &default_entries.indent_width));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void FromV2Json_Valid_ReturnsEntries(CuTest* tc) {
  cJSON* entries_json;
  cJSON* metadata_json;
  cJSON* ingame_resolutions_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  entries_json = cJSON_CreateObject();
  metadata_json = cJSON_AddObjectToObject(entries_json, CfgMetadata_kJsonKey);
  cJSON_AddStringToObject(
      metadata_json, CfgConfigVersion_kV2JsonKey, "3.1.42.1337");
  cJSON_AddNumberToObject(entries_json, CfgIndentWidth_kJsonKey, 42);
  cJSON_AddStringToObject(
      entries_json, CfgCustomMpqFilePath_kJsonKey, "file.mpq");
  cJSON_AddStringToObject(
      entries_json, CfgIngameResolution_kV2JsonKey, "4240x2420");
  ingame_resolutions_json =
      cJSON_AddArrayToObject(entries_json, CfgIngameResolutions_kJsonKey);
  cJSON_AddItemToArray(
      ingame_resolutions_json, cJSON_CreateString("2420x4240"));
  cJSON_AddItemToArray(
      ingame_resolutions_json, cJSON_CreateString("4240x2420"));
  cJSON_AddStringToObject(
      entries_json, CfgMainMenuResolution_kJsonKey, "1200x900");

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgEntries_Equals(&entries, &kEntries));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void FromV2Json_EntriesTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* entries_json;
  cJSON* metadata_json;
  cJSON* ingame_resolutions_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  entries_json = cJSON_CreateNull();

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(entries_json);
}

static void FromV2Json_MetadataMissing_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc, CfgMetadata_Equals(&entries.metadata, &default_entries.metadata));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void FromV2Json_MetadataTypeMismatch_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddNullToObject(entries_json, CfgMetadata_kJsonKey);

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc, CfgMetadata_Equals(&entries.metadata, &default_entries.metadata));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void FromV2Json_IndentWidthMissing_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgIndentWidth_Equals(
          &entries.indent_width, &default_entries.indent_width));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_IndentWidthTypeMismatch_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddNullToObject(entries_json, CfgIndentWidth_kJsonKey);

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgIndentWidth_Equals(
          &entries.indent_width, &default_entries.indent_width));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_CustomMpqFilePathMissing_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgCustomMpqFilePath_Equals(
          &entries.custom_mpq_file_path,
          &default_entries.custom_mpq_file_path));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_CustomMpqFilePathTypeMismatch_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddNullToObject(entries_json, CfgCustomMpqFilePath_kJsonKey);

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgCustomMpqFilePath_Equals(
          &entries.custom_mpq_file_path,
          &default_entries.custom_mpq_file_path));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_IngameResolutionMissing_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgIngameResolution_Equals(
          &entries.ingame_resolution, &default_entries.ingame_resolution));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_IngameResolutionTypeMismatch_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddNullToObject(entries_json, CfgIngameResolution_kV2JsonKey);

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgIngameResolution_Equals(
          &entries.ingame_resolution, &default_entries.ingame_resolution));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_IngameResolutionsMissing_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgIngameResolutions_Equals(
          &entries.ingame_resolutions, &default_entries.ingame_resolutions));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_IngameResolutionsTypeMismatch_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddNullToObject(entries_json, CfgIngameResolutions_kJsonKey);

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgMainMenuResolution_Equals(
          &entries.main_menu_resolution,
          &default_entries.main_menu_resolution));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_MainMenuResolutionMissing_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgMainMenuResolution_Equals(
          &entries.main_menu_resolution,
          &default_entries.main_menu_resolution));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void
FromV2Json_MainMenuResolutionTypeMismatch_ReturnsEntriesWithDefaultValue(
    CuTest* tc) {
  struct CfgEntries default_entries;
  cJSON* entries_json;
  struct CfgEntries entries;
  struct CfgEntries* result;

  CfgEntries_InitDefault(&default_entries);
  entries_json = cJSON_CreateObject();
  cJSON_AddNullToObject(entries_json, CfgMainMenuResolution_kJsonKey);

  result = CfgEntries_FromV2Json(&entries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc,
      CfgMainMenuResolution_Equals(
          &entries.main_menu_resolution,
          &default_entries.main_menu_resolution));

  CfgEntries_Deinit(&entries);
  cJSON_Delete(entries_json);
}

static void AddToJson_WithObject_AddsEntry(CuTest* tc) {
  cJSON* entries_json;
  cJSON* result;
  cJSON* metadata_json;
  cJSON* config_version_json;
  const char* config_version_str;
  cJSON* indent_width_json;
  cJSON* custom_mpq_file_path_json;
  const char* custom_mpq_file_path_str;
  cJSON* ingame_resolution_json;
  const char* ingame_resolution_str;
  cJSON* ingame_resolutions_json;
  cJSON* ingame_resolution_2420x4240_json;
  const char* ingame_resolution_2420x4240_str;
  cJSON* ingame_resolution_4240x2420_json;
  const char* ingame_resolution_4240x2420_str;
  cJSON* main_menu_resolution_json;
  const char* main_menu_resolution_str;

  entries_json = cJSON_CreateObject();

  result = CfgEntries_AddToJson(&kEntries, entries_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, cJSON_HasObjectItem(entries_json, CfgMetadata_kJsonKey));
  metadata_json =
      cJSON_GetObjectItemCaseSensitive(entries_json, CfgMetadata_kJsonKey);
  CuAssertTrue(tc, cJSON_IsObject(metadata_json));
  config_version_json =
      cJSON_GetObjectItemCaseSensitive(
          metadata_json, CfgConfigVersion_kV2JsonKey);
  CuAssertTrue(tc, cJSON_IsString(config_version_json));
  config_version_str = cJSON_GetStringValue(config_version_json);
  CuAssertStrEquals(tc, "3.1.42.1337", config_version_str);
  CuAssertTrue(
      tc, cJSON_HasObjectItem(entries_json, CfgIndentWidth_kJsonKey));
  indent_width_json =
      cJSON_GetObjectItemCaseSensitive(entries_json, CfgIndentWidth_kJsonKey);
  CuAssertTrue(tc, cJSON_IsNumber(indent_width_json));
  CuAssertIntEquals(tc, 42, cJSON_GetNumberValue(indent_width_json));
  CuAssertTrue(
      tc, cJSON_HasObjectItem(entries_json, CfgCustomMpqFilePath_kJsonKey));
  custom_mpq_file_path_json =
      cJSON_GetObjectItemCaseSensitive(
          entries_json, CfgCustomMpqFilePath_kJsonKey);
  CuAssertTrue(tc, cJSON_IsString(custom_mpq_file_path_json));
  custom_mpq_file_path_str = cJSON_GetStringValue(custom_mpq_file_path_json);
  CuAssertStrEquals(tc, "file.mpq", custom_mpq_file_path_str);
  CuAssertTrue(
      tc, cJSON_HasObjectItem(entries_json, CfgIngameResolution_kV2JsonKey));
  ingame_resolution_json =
      cJSON_GetObjectItemCaseSensitive(
          entries_json, CfgIngameResolution_kV2JsonKey);
  CuAssertTrue(tc, cJSON_IsString(ingame_resolution_json));
  ingame_resolution_str = cJSON_GetStringValue(ingame_resolution_json);
  CuAssertStrEquals(tc, "4240x2420", ingame_resolution_str);
  CuAssertTrue(
      tc, cJSON_HasObjectItem(entries_json, CfgIngameResolutions_kJsonKey));
  ingame_resolutions_json =
      cJSON_GetObjectItemCaseSensitive(
          entries_json, CfgIngameResolutions_kJsonKey);
  CuAssertTrue(tc, cJSON_IsArray(ingame_resolutions_json));
  CuAssertIntEquals(tc, 2, cJSON_GetArraySize(ingame_resolutions_json));
  ingame_resolution_2420x4240_json =
      cJSON_GetArrayItem(ingame_resolutions_json, 0);
  CuAssertTrue(tc, cJSON_IsString(ingame_resolution_2420x4240_json));
  ingame_resolution_2420x4240_str =
      cJSON_GetStringValue(ingame_resolution_2420x4240_json);
  CuAssertStrEquals(tc, "2420x4240", ingame_resolution_2420x4240_str);
  ingame_resolution_4240x2420_json =
      cJSON_GetArrayItem(ingame_resolutions_json, 1);
  CuAssertTrue(tc, cJSON_IsString(ingame_resolution_4240x2420_json));
  ingame_resolution_4240x2420_str =
      cJSON_GetStringValue(ingame_resolution_4240x2420_json);
  CuAssertStrEquals(tc, "4240x2420", ingame_resolution_4240x2420_str);
  CuAssertTrue(
      tc, cJSON_HasObjectItem(entries_json, CfgMainMenuResolution_kJsonKey));
  main_menu_resolution_json =
      cJSON_GetObjectItemCaseSensitive(
          entries_json, CfgMainMenuResolution_kJsonKey);
  CuAssertTrue(tc, cJSON_IsString(main_menu_resolution_json));
  main_menu_resolution_str = cJSON_GetStringValue(main_menu_resolution_json);
  CuAssertStrEquals(tc, "1200x900", main_menu_resolution_str);

  cJSON_Delete(entries_json);
}

static void AddToJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* entries_json;
  cJSON* result;

  entries_json = cJSON_CreateNull();

  result = CfgEntries_AddToJson(&kEntries, entries_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(entries_json);
}

/**
 * External
 */

CuSuite* CfgEntries_GetTestSuite(void) {
  CuSuite* suite;

  suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, InitDefault_ReturnsDefault);

  SUITE_ADD_TEST(suite, FromV1Json_Valid_ReturnsEntries);
  SUITE_ADD_TEST(suite, FromV1Json_EntriesTypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_Sgd2frMissing_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_Sgd2frTypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_Sgd2frSubentriesMissing_ReturnsEntriesWithDefaultSubentries);
  SUITE_ADD_TEST(suite, FromV1Json_Sgd2frSubentriesTypeMismatch_ReturnsEntriesWithDefaultSubentries);
  SUITE_ADD_TEST(suite, FromV1Json_GlobalsMissing_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV1Json_GlobalsTypeMismatch_ReturnsEntriesWithDefaultValue);

  SUITE_ADD_TEST(suite, FromV2Json_Valid_ReturnsEntries);
  SUITE_ADD_TEST(suite, FromV2Json_EntriesTypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MetadataMissing_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_MetadataTypeMismatch_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_IndentWidthMissing_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_IndentWidthTypeMismatch_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_CustomMpqFilePathMissing_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_CustomMpqFilePathTypeMismatch_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_IngameResolutionMissing_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_IngameResolutionTypeMismatch_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_IngameResolutionsMissing_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_IngameResolutionsTypeMismatch_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_MainMenuResolutionMissing_ReturnsEntriesWithDefaultValue);
  SUITE_ADD_TEST(suite, FromV2Json_MainMenuResolutionTypeMismatch_ReturnsEntriesWithDefaultValue);

  SUITE_ADD_TEST(suite, AddToJson_WithObject_AddsEntry);
  SUITE_ADD_TEST(suite, AddToJson_TypeMismatch_ReturnsNull);

  return suite;
}
