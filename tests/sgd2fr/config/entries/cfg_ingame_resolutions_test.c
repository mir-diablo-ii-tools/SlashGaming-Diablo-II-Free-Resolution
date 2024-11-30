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

#include "sgd2fr/config/entries/cfg_ingame_resolutions_test.h"

#include <stddef.h>
#include <string.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/common/resolution.h"
#include "sgd2fr/config/entries/cfg_ingame_resolutions.h"

static struct Resolution kResolutions[] = {
  { 640, 480 }, { 800, 600 }, { 1024, 768 }
};
static struct Resolution kDefaultResolutions[] = {
  { 640, 480 }, { 800, 600 }
};

enum {
  kResolutionCount = sizeof(kResolutions) / sizeof(kResolutions[0]),
  kDefaultResolutionCount =
      sizeof(kDefaultResolutions) / sizeof(kDefaultResolutions[0])
};

static struct CfgIngameResolutions kIngameResolutions = {
  kResolutions, kResolutionCount, kResolutionCount
};
static struct CfgIngameResolutions kDefaultIngameResolutions = {
  kDefaultResolutions, kDefaultResolutionCount, kDefaultResolutionCount
};

static const char* const kResolutionStrs[] = {
  "640x480", "800x600", "1024x768"
};
static const char* const kDefaultResolutionStrs[] = {
  "640x480", "800x600"
};

static void AddResolutionsJson(
    cJSON* resolutions_json, const char* const* strs, size_t count) {
  size_t i;

  for (i = 0; i < count; ++i) {
    cJSON_AddItemToArray(
        resolutions_json, cJSON_CreateString(strs[i]));
  }
}

/**
 * Tests
 */

static void InitDefault_ReturnsDefault(CuTest* tc) {
  struct Resolution resolutions[] = {
    { 640, 480 },
    { 800, 600 }
  };
  struct CfgIngameResolutions expected = { resolutions, 2, 2 };
  struct CfgIngameResolutions actual;
  struct CfgIngameResolutions* result;

  result = CfgIngameResolutions_InitDefault(&actual);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolutions_Equals(&actual, &expected));

  CfgIngameResolutions_Deinit(&actual);
}

static void FromJson_Valid_ReturnsResolutions(CuTest* tc) {
  cJSON* resolutions_json;
  struct CfgIngameResolutions actual;
  struct CfgIngameResolutions* result;

  resolutions_json = cJSON_CreateArray();
  AddResolutionsJson(resolutions_json, kResolutionStrs, kResolutionCount);

  result = CfgIngameResolutions_FromJson(&actual, resolutions_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolutions_Equals(&actual, &kIngameResolutions));

  CfgIngameResolutions_Deinit(&actual);
}

static void FromJson_Empty_ReturnsDefault(CuTest* tc) {
  cJSON* resolutions_json;
  struct CfgIngameResolutions actual;
  struct CfgIngameResolutions* result;

  resolutions_json = cJSON_CreateArray();

  result = CfgIngameResolutions_FromJson(&actual, resolutions_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc, CfgIngameResolutions_Equals(&actual, &kDefaultIngameResolutions));

  CfgIngameResolutions_Deinit(&actual);
  cJSON_Delete(resolutions_json);
}

static void FromJson_TypeMismatch_ReturnsDefault(CuTest* tc) {
  cJSON* object;
  struct CfgIngameResolutions actual;
  struct CfgIngameResolutions* result;

  object = cJSON_CreateObject();

  result = CfgIngameResolutions_FromJson(&actual, object);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc, CfgIngameResolutions_Equals(&actual, &kDefaultIngameResolutions));

  CfgIngameResolutions_Deinit(&actual);
  cJSON_Delete(object);
}

static void FromJson_WithDuplicates_ReturnsUniqueResolutions(CuTest* tc) {
  cJSON* resolutions_json;
  struct CfgIngameResolutions actual;
  struct CfgIngameResolutions* result;

  resolutions_json = cJSON_CreateArray();
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[0]));
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[0]));
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[1]));
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[1]));
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[2]));
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[2]));

  result = CfgIngameResolutions_FromJson(&actual, resolutions_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolutions_Equals(&actual, &kIngameResolutions));

  CfgIngameResolutions_Deinit(&actual);
  cJSON_Delete(resolutions_json);
}

static void FromJson_WithUnsorted_ReturnsUniqueResolutions(CuTest* tc) {
  const char* kResolutionStrs[] = {
    "1024x768", "800x600", "640x480"
  };
  cJSON* resolutions_json;
  struct CfgIngameResolutions actual;
  struct CfgIngameResolutions* result;

  resolutions_json = cJSON_CreateArray();
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[0]));
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[1]));
  cJSON_AddItemToArray(resolutions_json, cJSON_CreateString(kResolutionStrs[2]));

  result = CfgIngameResolutions_FromJson(&actual, resolutions_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolutions_Equals(&actual, &kIngameResolutions));

  CfgIngameResolutions_Deinit(&actual);
  cJSON_Delete(resolutions_json);
}

static void AddToJson_WithObject_AddsEntry(CuTest* tc) {
  size_t i;
  cJSON* object;
  cJSON* result;
  cJSON* resolutions_json;
  cJSON* resolution_json;

  object = cJSON_CreateObject();

  result =
      CfgIngameResolutions_AddToJson(&kIngameResolutions, object);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc, cJSON_HasObjectItem(object, CfgIngameResolutions_GetJsonKey(NULL)));
  resolutions_json =
      cJSON_GetObjectItemCaseSensitive(
          object, CfgIngameResolutions_GetJsonKey(NULL));
  CuAssertTrue(tc, cJSON_IsArray(resolutions_json));
  i = 0;
  cJSON_ArrayForEach(resolution_json, resolutions_json) {
    CuAssertTrue(tc, cJSON_IsString(resolution_json));
    CuAssertStrEquals(
        tc, kResolutionStrs[i], cJSON_GetStringValue(resolution_json));
    ++i;
  }

  cJSON_Delete(object);
}

static void AddToJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* item;
  cJSON* result;

  item = cJSON_CreateFalse();

  result = CfgIngameResolutions_AddToJson(&kIngameResolutions, item);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(item);
}

static void Equals_SameResolutions_ReturnsTrue(CuTest* tc) {
  CuAssertTrue(
      tc,
      CfgIngameResolutions_Equals(
          &kDefaultIngameResolutions,&kDefaultIngameResolutions));
}

static void Equals_EqualResolutions_ReturnsTrue(CuTest* tc) {
  struct CfgIngameResolutions lhs;

  CfgIngameResolutions_InitDefault(&lhs);

  CuAssertTrue(
      tc, CfgIngameResolutions_Equals(&lhs,&kDefaultIngameResolutions));
}

static void Equals_DifferentCount_ReturnsFalse(CuTest* tc) {
  struct Resolution resolutions[2] = { { 640, 480 }, { 800, 600 } };
  struct CfgIngameResolutions lhs = { resolutions, 1, 1 };
  struct CfgIngameResolutions rhs = { resolutions, 2, 2 };

  CuAssertTrue(tc, !CfgIngameResolutions_Equals(&lhs,&rhs));
}

static void Equals_DifferentResolutions_ReturnsFalse(CuTest* tc) {
  struct Resolution lhs_resolutions[2] = { { 640, 480 }, { 800, 600 } };
  struct Resolution rhs_resolutions[2] = { { 644, 480 }, { 800, 600 } };
  struct CfgIngameResolutions lhs = { lhs_resolutions, 1, 1 };
  struct CfgIngameResolutions rhs = { rhs_resolutions, 2, 2 };

  CuAssertTrue(tc, !CfgIngameResolutions_Equals(&lhs,&rhs));
}

static void FindIndex_Exists_ReturnsIndex(CuTest* tc) {
  struct Resolution resolution = { 800, 600 };

  CuAssertIntEquals(
      tc, 1, CfgIngameResolutions_FindIndex(&kIngameResolutions, &resolution));
}

static void FindIndex_NotExists_ReturnsCount(CuTest* tc) {
  struct Resolution resolution = { 1344, 700 };

  CuAssertIntEquals(
      tc,
      kResolutionCount,
      CfgIngameResolutions_FindIndex(&kIngameResolutions, &resolution));
}

static void GetJsonKey_WithLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;
  size_t length;

  result = CfgIngameResolutions_GetJsonKey(&length);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) == length);
}

static void GetJsonKey_WithNullLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;

  result = CfgIngameResolutions_GetJsonKey(NULL);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) > 0);
}

/**
 * External
 */

CuSuite* CfgIngameResolutions_GetTestSuite(void) {
  CuSuite* suite;

  suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, InitDefault_ReturnsDefault);

  SUITE_ADD_TEST(suite, FromJson_Valid_ReturnsResolutions);
  SUITE_ADD_TEST(suite, FromJson_Empty_ReturnsDefault);
  SUITE_ADD_TEST(suite, FromJson_TypeMismatch_ReturnsDefault);
  SUITE_ADD_TEST(suite, FromJson_WithDuplicates_ReturnsUniqueResolutions);
  SUITE_ADD_TEST(suite, FromJson_WithUnsorted_ReturnsUniqueResolutions);

  SUITE_ADD_TEST(suite, AddToJson_WithObject_AddsEntry);
  SUITE_ADD_TEST(suite, AddToJson_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, Equals_SameResolutions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualResolutions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentCount_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentResolutions_ReturnsFalse);

  SUITE_ADD_TEST(suite, FindIndex_Exists_ReturnsIndex);
  SUITE_ADD_TEST(suite, FindIndex_NotExists_ReturnsCount);

  SUITE_ADD_TEST(suite, GetJsonKey_WithLength_ReturnsJsonKey);
  SUITE_ADD_TEST(suite, GetJsonKey_WithNullLength_ReturnsJsonKey);

  return suite;
}
