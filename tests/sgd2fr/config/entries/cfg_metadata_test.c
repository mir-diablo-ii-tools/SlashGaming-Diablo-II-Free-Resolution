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

#include "sgd2fr/config/entries/cfg_metadata_test.h"

#include <stddef.h>
#include <string.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/config/entries/cfg_metadata.h"
#include "sgd2fr/config/entries/metadata/cfg_config_version.h"

/**
 * Tests
 */

static void InitDefault_ReturnsDefault(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;

  result = CfgMetadata_InitDefault(&actual);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, !CfgConfigVersion_IsV1Config(&actual.version));
}

static void FromV1Json_Valid_ReturnsMetadata(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1PatchJsonKey, 1);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgMetadata_FromV1Json(&actual, value);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_IsV1Config(&actual.version));

  cJSON_Delete(value);
}

static void FromV1Json_TypeMismatch_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateFalse();

  result = CfgMetadata_FromV1Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void FromV1Json_V2Metadata_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();
  cJSON_AddStringToObject(value, CfgConfigVersion_kV1MajorJsonKey, "3.1.0.0");

  result = CfgMetadata_FromV1Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void FromV1Json_InvalidVersion_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1MajorJsonKey, -1);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1MinorJsonKey, -1);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1PatchJsonKey, -1);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1BuildJsonKey, -1);

  result = CfgMetadata_FromV1Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void FromV1Json_MissingVersion_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();

  result = CfgMetadata_FromV1Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void FromV2Json_Valid_ReturnsMetadata(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();
  cJSON_AddStringToObject(value, CfgConfigVersion_kV2JsonKey, "3.1.0.0");

  result = CfgMetadata_FromV2Json(&actual, value);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, !CfgConfigVersion_IsV1Config(&actual.version));

  cJSON_Delete(value);
}

static void FromV2Json_TypeMismatch_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateFalse();

  result = CfgMetadata_FromV2Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void FromV2Json_V1Metadata_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1PatchJsonKey, 1);
  cJSON_AddNumberToObject(value, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgMetadata_FromV2Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void FromV2Json_InvalidVersion_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();
  cJSON_AddStringToObject(value, CfgConfigVersion_kV2JsonKey, "invalid");

  result = CfgMetadata_FromV2Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void FromV2Json_MissingVersion_ReturnsNull(CuTest* tc) {
  struct CfgMetadata actual;
  struct CfgMetadata* result;
  cJSON* value;

  value = cJSON_CreateObject();

  result = CfgMetadata_FromV2Json(&actual, value);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(value);
}

static void AddToJson_Object_AddsEntry(CuTest* tc) {
  const char* metadata_key;
  cJSON* object;
  struct CfgMetadata metadata;
  cJSON* result;
  cJSON* metadata_json;
  cJSON* version_json;

  CfgMetadata_InitDefault(&metadata);
  object = cJSON_CreateObject();

  result = CfgMetadata_AddToJson(&metadata, object);

  CuAssertPtrNotNull(tc, result);
  metadata_key = CfgMetadata_GetJsonKey(NULL);
  CuAssertTrue(tc, cJSON_HasObjectItem(object, metadata_key));
  metadata_json = cJSON_GetObjectItemCaseSensitive(object, metadata_key);
  CuAssertTrue(tc, cJSON_IsObject(metadata_json));
  CuAssertTrue(
      tc, cJSON_HasObjectItem(metadata_json, CfgConfigVersion_kV2JsonKey));
  version_json =
      cJSON_GetObjectItemCaseSensitive(
          metadata_json, CfgConfigVersion_kV2JsonKey);
  CuAssertTrue(tc, cJSON_IsString(version_json));

  cJSON_Delete(object);
}

static void AddToJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgMetadata metadata;
  cJSON* result;

  CfgMetadata_InitDefault(&metadata);
  object = cJSON_CreateFalse();

  result = CfgMetadata_AddToJson(&metadata, object);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(object);
}

static void Equals_SameMetadata_ReturnsTrue(CuTest* tc) {
  struct CfgMetadata lhs;

  CuAssertTrue(tc, CfgMetadata_Equals(&lhs, &lhs));
}

static void Equals_EqualMetadata_ReturnsTrue(CuTest* tc) {
  struct CfgMetadata lhs;
  struct CfgMetadata rhs;

  CfgMetadata_InitDefault(&lhs);
  CfgMetadata_InitDefault(&rhs);

  CuAssertTrue(tc, CfgMetadata_Equals(&lhs, &rhs));
}

static void Equals_DifferentVersion_ReturnsFalse(CuTest* tc) {
  struct CfgMetadata lhs;
  struct CfgMetadata rhs;

  CfgMetadata_InitDefault(&lhs);
  CfgMetadata_InitDefault(&rhs);
  rhs.version.value.major_version += 1;

  CuAssertTrue(tc, !CfgMetadata_Equals(&lhs, &rhs));
}

static void GetJsonKey_WithLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;
  size_t length;

  result = CfgMetadata_GetJsonKey(&length);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) == length);
}

static void GetJsonKey_WithNullLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;

  result = CfgMetadata_GetJsonKey(NULL);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) > 0);
}

/**
 * External
 */

CuSuite* CfgMetadata_GetTestSuite(void) {
  CuSuite* suite;

  suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, InitDefault_ReturnsDefault);

  SUITE_ADD_TEST(suite, FromV1Json_Valid_ReturnsMetadata);
  SUITE_ADD_TEST(suite, FromV1Json_TypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_V2Metadata_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_InvalidVersion_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_MissingVersion_ReturnsNull);

  SUITE_ADD_TEST(suite, FromV2Json_Valid_ReturnsMetadata);
  SUITE_ADD_TEST(suite, FromV2Json_TypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_V1Metadata_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_InvalidVersion_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MissingVersion_ReturnsNull);

  SUITE_ADD_TEST(suite, AddToJson_Object_AddsEntry);
  SUITE_ADD_TEST(suite, AddToJson_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, Equals_SameMetadata_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualMetadata_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentVersion_ReturnsFalse);

  SUITE_ADD_TEST(suite, GetJsonKey_WithLength_ReturnsJsonKey);
  SUITE_ADD_TEST(suite, GetJsonKey_WithNullLength_ReturnsJsonKey);

  return suite;
}
