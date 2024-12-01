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

#include "sgd2fr/config/entries/cfg_ingame_resolution_test.h"

#include <limits.h>
#include <stddef.h>
#include <string.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/common/resolution.h"
#include "sgd2fr/config/entries/cfg_ingame_resolution.h"
#include "sgd2fr/config/entries/cfg_ingame_resolutions.h"

static const struct CfgIngameResolution kDefaultResolution = { { 640, 480 } };
static const char kDefaultResolutionStr[] = "640x480";

static struct Resolution kResolutions[] = {
  { 640, 480 }, { 800, 600 }, { 1024, 768 }
};
enum {
  kResolutionCount = sizeof(kResolutions) / sizeof(kResolutions[0])
};

static struct CfgIngameResolutions kIngameResolutions = {
  kResolutions, kResolutionCount, kResolutionCount
};

/**
 * Test
 */

static void FromV1Json_640x480_ReturnsResolution(CuTest* tc) {
  struct CfgIngameResolution expected = { { 640, 480 } };
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateNumber(0);

  result =
      CfgIngameResolution_FromV1Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromV1Json_800x600_ReturnsResolution(CuTest* tc) {
  struct CfgIngameResolution expected = { { 800, 600 } };
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateNumber(1);

  result =
      CfgIngameResolution_FromV1Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromV1Json_1024x768_ReturnsResolution(CuTest* tc) {
  struct CfgIngameResolution expected = { { 1024, 768 } };
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateNumber(2);

  result =
      CfgIngameResolution_FromV1Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromV1Json_AboveMax_ReturnsNull(CuTest* tc) {
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateNumber(INT_MAX);

  result =
      CfgIngameResolution_FromV1Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(resolution_json);
}

static void FromV1Json_BelowMin_ReturnsNull(CuTest* tc) {
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateNumber(INT_MIN);

  result =
      CfgIngameResolution_FromV1Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(resolution_json);
}

static void FromV1Json_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateObject();

  result =
      CfgIngameResolution_FromV1Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(resolution_json);
}

static void FromV2Json_640x480_ReturnsResolution(CuTest* tc) {
  struct CfgIngameResolution expected = { { 640, 480 } };
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateString("640x480");

  result =
      CfgIngameResolution_FromV2Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromV2Json_800x600_ReturnsResolution(CuTest* tc) {
  struct CfgIngameResolution expected = { { 800, 600 } };
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateString("800x600");

  result =
      CfgIngameResolution_FromV2Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromV2Json_1024x768_ReturnsResolution(CuTest* tc) {
  struct CfgIngameResolution expected = { { 1024, 768 } };
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateString("1024x768");

  result =
      CfgIngameResolution_FromV2Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromV2Json_NotExists_ReturnsDefault(CuTest* tc) {
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateString("3840x2160");

  result =
      CfgIngameResolution_FromV2Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &kDefaultResolution));

  cJSON_Delete(resolution_json);
}

static void FromV2Json_TypeMismatch_ReturnsDefault(CuTest* tc) {
  cJSON* resolution_json;
  struct CfgIngameResolution actual;
  struct CfgIngameResolution* result;

  resolution_json = cJSON_CreateObject();

  result =
      CfgIngameResolution_FromV2Json(
          &actual, resolution_json, &kIngameResolutions);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgIngameResolution_Equals(&actual, &kDefaultResolution));

  cJSON_Delete(resolution_json);
}

static void AddToJson_Object_AddsEntry(CuTest* tc) {
  cJSON* object;
  cJSON* result;
  cJSON* value;

  object = cJSON_CreateObject();

  result = CfgIngameResolution_AddToJson(&kDefaultResolution, object);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc, cJSON_HasObjectItem(object, CfgIngameResolution_GetJsonKey(NULL)));
  value =
      cJSON_GetObjectItemCaseSensitive(
          object, CfgIngameResolution_GetJsonKey(NULL));
  CuAssertTrue(tc, cJSON_IsString(value));
  CuAssertStrEquals(tc, kDefaultResolutionStr, cJSON_GetStringValue(value));

  cJSON_Delete(object);
}

static void AddToJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  cJSON* result;
  cJSON* value;

  object = cJSON_CreateArray();

  result = CfgIngameResolution_AddToJson(&kDefaultResolution, object);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(object);
}

static void Compare_SameResolution_ReturnsZero(CuTest* tc) {
  CuAssertIntEquals(
      tc,
      0,
      CfgIngameResolution_Compare(&kDefaultResolution, &kDefaultResolution));
}

static void Compare_EqualResolutions_ReturnsZero(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640, 480 } };
  struct CfgIngameResolution rhs = { { 640, 480 } };

  CuAssertIntEquals(tc, 0, CfgIngameResolution_Compare(&lhs, &rhs));
}

static void Compare_LtWidths_ReturnsNegative(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640 - 1, 480 } };
  struct CfgIngameResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgIngameResolution_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtWidths_ReturnsPositive(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640 + 1, 480 } };
  struct CfgIngameResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgIngameResolution_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtHeights_ReturnsNegative(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640, 480 - 1 } };
  struct CfgIngameResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgIngameResolution_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtHeights_ReturnsPositive(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640, 480 + 1 } };
  struct CfgIngameResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgIngameResolution_Compare(&lhs, &rhs) > 0);
}

static void Compare_DifferentWidthsAndHeights_ReturnsNonZero(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640 - 1, 480 + 1 } };
  struct CfgIngameResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgIngameResolution_Compare(&lhs, &rhs) != 0);
}

static void Equals_SameResolution_ReturnsTrue(CuTest* tc) {
  CuAssertTrue(
      tc,
      CfgIngameResolution_Equals(&kDefaultResolution, &kDefaultResolution));
}

static void Equals_EqualResolutions_ReturnsTrue(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640, 480 } };
  struct CfgIngameResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgIngameResolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentWidths_ReturnsTrue(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640, 480 } };
  struct CfgIngameResolution rhs = { { 800, 480 } };

  CuAssertTrue(tc, !CfgIngameResolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentHeights_ReturnsTrue(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640, 480 } };
  struct CfgIngameResolution rhs = { { 640, 600 } };

  CuAssertTrue(tc, !CfgIngameResolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentWidthsAndHeights_ReturnsTrue(CuTest* tc) {
  struct CfgIngameResolution lhs = { { 640, 480 } };
  struct CfgIngameResolution rhs = { { 800, 600 } };

  CuAssertTrue(tc, !CfgIngameResolution_Equals(&lhs, &rhs));
}

static void GetJsonKey_WithLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;
  size_t length;

  result = CfgIngameResolution_GetJsonKey(&length);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) == length);
}

static void GetJsonKey_WithNullLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;

  result = CfgIngameResolution_GetJsonKey(NULL);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) > 0);
}

/**
 * External
 */

CuSuite* CfgIngameResolution_GetTestSuite(void) {
  CuSuite* suite;

  suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, FromV1Json_640x480_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromV1Json_800x600_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromV1Json_1024x768_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromV1Json_AboveMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_BelowMin_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, FromV2Json_640x480_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromV2Json_800x600_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromV2Json_1024x768_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromV2Json_NotExists_ReturnsDefault);
  SUITE_ADD_TEST(suite, FromV2Json_TypeMismatch_ReturnsDefault);

  SUITE_ADD_TEST(suite, AddToJson_Object_AddsEntry);
  SUITE_ADD_TEST(suite, AddToJson_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, Compare_SameResolution_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_EqualResolutions_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_LtWidths_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtWidths_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtHeights_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtHeights_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_DifferentWidthsAndHeights_ReturnsNonZero);

  SUITE_ADD_TEST(suite, Equals_SameResolution_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualResolutions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentWidths_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentHeights_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentWidthsAndHeights_ReturnsTrue);

  SUITE_ADD_TEST(suite, GetJsonKey_WithLength_ReturnsJsonKey);
  SUITE_ADD_TEST(suite, GetJsonKey_WithNullLength_ReturnsJsonKey);

  return suite;
}
