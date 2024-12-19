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

#include "sgd2fr/config/entries/cfg_main_menu_resolution_test.h"

#include <stddef.h>
#include <string.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/config/entries/cfg_main_menu_resolution.h"

static const struct CfgMainMenuResolution kDefaultResolution = { { 800, 600 } };
static const char kDefaultResolutionStr[] = "800x600";

/**
 * Test
 */

static void InitDefault_ReturnsDefault(CuTest* tc) {
  struct CfgMainMenuResolution actual;
  struct CfgMainMenuResolution* result;

  result = CfgMainMenuResolution_InitDefault(&actual);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgMainMenuResolution_Equals(&actual, &kDefaultResolution));
}

static void FromJson_640x480_ReturnsResolution(CuTest* tc) {
  struct CfgMainMenuResolution expected = { { 640, 480 } };
  cJSON* resolution_json;
  struct CfgMainMenuResolution actual;
  struct CfgMainMenuResolution* result;

  resolution_json = cJSON_CreateString("640x480");

  result = CfgMainMenuResolution_FromJson(&actual, resolution_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgMainMenuResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromJson_800x600_ReturnsResolution(CuTest* tc) {
  struct CfgMainMenuResolution expected = { { 800, 600 } };
  cJSON* resolution_json;
  struct CfgMainMenuResolution actual;
  struct CfgMainMenuResolution* result;

  resolution_json = cJSON_CreateString("800x600");

  result = CfgMainMenuResolution_FromJson(&actual, resolution_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgMainMenuResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromJson_1024x768_ReturnsResolution(CuTest* tc) {
  struct CfgMainMenuResolution expected = { { 1024, 768 } };
  cJSON* resolution_json;
  struct CfgMainMenuResolution actual;
  struct CfgMainMenuResolution* result;

  resolution_json = cJSON_CreateString("1024x768");

  result = CfgMainMenuResolution_FromJson(&actual, resolution_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgMainMenuResolution_Equals(&actual, &expected));

  cJSON_Delete(resolution_json);
}

static void FromJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* resolution_json;
  struct CfgMainMenuResolution actual;
  struct CfgMainMenuResolution* result;

  resolution_json = cJSON_CreateObject();

  result = CfgMainMenuResolution_FromJson(&actual, resolution_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(resolution_json);
}

static void AddToJson_Object_AddsEntry(CuTest* tc) {
  cJSON* object;
  cJSON* result;
  cJSON* value;

  object = cJSON_CreateObject();

  result = CfgMainMenuResolution_AddToJson(&kDefaultResolution, object);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(
      tc, cJSON_HasObjectItem(object, CfgMainMenuResolution_kJsonKey));
  value =
      cJSON_GetObjectItemCaseSensitive(object, CfgMainMenuResolution_kJsonKey);
  CuAssertTrue(tc, cJSON_IsString(value));
  CuAssertStrEquals(tc, kDefaultResolutionStr, cJSON_GetStringValue(value));

  cJSON_Delete(object);
}

static void AddToJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  cJSON* result;
  cJSON* value;

  object = cJSON_CreateArray();

  result = CfgMainMenuResolution_AddToJson(&kDefaultResolution, object);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(object);
}

static void Compare_SameResolution_ReturnsZero(CuTest* tc) {
  CuAssertIntEquals(
      tc,
      0,
      CfgMainMenuResolution_Compare(&kDefaultResolution, &kDefaultResolution));
}

static void Compare_EqualResolutions_ReturnsZero(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640, 480 } };
  struct CfgMainMenuResolution rhs = { { 640, 480 } };

  CuAssertIntEquals(tc, 0, CfgMainMenuResolution_Compare(&lhs, &rhs));
}

static void Compare_LtWidths_ReturnsNegative(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640 - 1, 480 } };
  struct CfgMainMenuResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgMainMenuResolution_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtWidths_ReturnsPositive(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640 + 1, 480 } };
  struct CfgMainMenuResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgMainMenuResolution_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtHeights_ReturnsNegative(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640, 480 - 1 } };
  struct CfgMainMenuResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgMainMenuResolution_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtHeights_ReturnsPositive(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640, 480 + 1 } };
  struct CfgMainMenuResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgMainMenuResolution_Compare(&lhs, &rhs) > 0);
}

static void Compare_DifferentWidthsAndHeights_ReturnsNonZero(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640 - 1, 480 + 1 } };
  struct CfgMainMenuResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgMainMenuResolution_Compare(&lhs, &rhs) != 0);
}

static void Equals_SameResolution_ReturnsTrue(CuTest* tc) {
  CuAssertTrue(
      tc,
      CfgMainMenuResolution_Equals(&kDefaultResolution, &kDefaultResolution));
}

static void Equals_EqualResolutions_ReturnsTrue(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640, 480 } };
  struct CfgMainMenuResolution rhs = { { 640, 480 } };

  CuAssertTrue(tc, CfgMainMenuResolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentWidths_ReturnsTrue(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640, 480 } };
  struct CfgMainMenuResolution rhs = { { 800, 480 } };

  CuAssertTrue(tc, !CfgMainMenuResolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentHeights_ReturnsTrue(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640, 480 } };
  struct CfgMainMenuResolution rhs = { { 640, 600 } };

  CuAssertTrue(tc, !CfgMainMenuResolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentWidthsAndHeights_ReturnsTrue(CuTest* tc) {
  struct CfgMainMenuResolution lhs = { { 640, 480 } };
  struct CfgMainMenuResolution rhs = { { 800, 600 } };

  CuAssertTrue(tc, !CfgMainMenuResolution_Equals(&lhs, &rhs));
}

static void GetJsonKey_WithLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;
  size_t length;

  result = CfgMainMenuResolution_GetJsonKey(&length);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 0, strcmp(result, CfgMainMenuResolution_kJsonKey));
  CuAssertTrue(tc, strlen(result) == length);
}

static void GetJsonKey_WithNullLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;

  result = CfgMainMenuResolution_GetJsonKey(NULL);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 0, strcmp(result, CfgMainMenuResolution_kJsonKey));
  CuAssertTrue(tc, strlen(result) > 0);
}

/**
 * External
 */

CuSuite* CfgMainMenuResolution_GetTestSuite(void) {
  CuSuite* suite;

  suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, InitDefault_ReturnsDefault);

  SUITE_ADD_TEST(suite, FromJson_640x480_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromJson_800x600_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromJson_1024x768_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromJson_TypeMismatch_ReturnsNull);

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
