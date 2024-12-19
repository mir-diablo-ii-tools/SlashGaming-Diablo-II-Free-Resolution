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

#include "sgd2fr/config/entries/metadata/cfg_config_version_test.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/config/entries/metadata/cfg_config_version.h"

static const struct CfgConfigVersion kConfigVersion = {
  { 123, 2468, 321, 42 }
};
static const struct CfgConfigVersion kDefaultConfigVersion = {
  { 3, 2, 0, 0 }
};

static const char kConfigVersionStr[] = "123.2468.321.42";

/**
 * Tests
 */

static void InitDefault_ReturnsDefault(CuTest* tc) {
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  result = CfgConfigVersion_InitDefault(&actual);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kDefaultConfigVersion));
}

static void FromV1Json_Valid_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { { 3, 0, 4, 0 } };
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 4);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV1Json_MajorBelowMin_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, -1);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_MinorBelowMin_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, -1);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_PatchBelowMin_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, -1);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_BuildBelowMin_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, -1);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_MajorAboveMax_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 4);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_MinorAboveMax_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 1);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_PatchAboveMax_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 5);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_BuildAboveMax_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 4);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 1);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_ObjectTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateFalse();

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_MajorTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddFalseToObject(object, CfgConfigVersion_kV1MajorJsonKey);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 4);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 1);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_MinorTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddFalseToObject(object, CfgConfigVersion_kV1MinorJsonKey);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 4);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_PatchTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddFalseToObject(object, CfgConfigVersion_kV1PatchJsonKey);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1BuildJsonKey, 0);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV1Json_BuildTypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  object = cJSON_CreateObject();
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MajorJsonKey, 3);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1MinorJsonKey, 0);
  cJSON_AddNumberToObject(object, CfgConfigVersion_kV1PatchJsonKey, 4);
  cJSON_AddFalseToObject(object, CfgConfigVersion_kV1BuildJsonKey);

  result = CfgConfigVersion_FromV1Json(&actual, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_Valid_ReturnsVersion(CuTest* tc) {
  cJSON* version_json;
  struct CfgConfigVersion version;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kConfigVersionStr);

  result = CfgConfigVersion_FromV2Json(&version, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&version, &kConfigVersion));

  cJSON_Delete(version_json);
}

static void FromV2Json_MajorZero_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { { 0, 2468, 321, 42 } };
  const char kStr[] = "0.2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_MinorZero_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { { 1234, 0, 321, 42 } };
  const char kStr[] = "1234.0.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_PatchZero_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { { 1234, 2468, 0, 42 } };
  const char kStr[] = "1234.2468.0.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_BuildZero_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { { 1234, 2468, 321, 0 } };
  const char kStr[] = "1234.2468.321.0";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_MajorIntMax_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { INT_MAX, 2468, 321, 42 };
  char kStr[64];
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", INT_MAX, 2468, 321, 42);
  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_MinorIntMax_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { 1234, INT_MAX, 321, 42 };
  char kStr[64];
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", 1234, INT_MAX, 321, 42);
  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_PatchIntMax_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { 1234, 2468, INT_MAX, 42 };
  char kStr[64];
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", 1234, 2468, INT_MAX, 42);
  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_BuildIntMax_ReturnsVersion(CuTest* tc) {
  const struct CfgConfigVersion kExpected = { 1234, 2468, 321, INT_MAX };
  char kStr[64];
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", 1234, 2468, 321, INT_MAX);
  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&actual, &kExpected));
}

static void FromV2Json_TerminateStringPeriod_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.42.";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MajorNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "-1234.2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MinorNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.-2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_PatchNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.-321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_BuildNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.-42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MissingMajor_ReturnsNull(CuTest* tc) {
  const char kStr[] = ".2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MissingMinor_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234..321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MissingPatch_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468..42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MissingBuild_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_PrefixMajorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "      1234.2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_SuffixMajorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234     .2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_PrefixMinorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.      2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_SuffixMinorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468     .321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_PrefixPatchNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.      321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_SuffixPatchNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321     .42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_PrefixBuildNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.      42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_SuffixBuildNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.42     ";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_CommaDelimiters_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234,2468,321,42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MajorLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "01234.2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MinorLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.02468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_PatchLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.0321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_BuildLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.042";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MajorAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.2468.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_MinorAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.321.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_PatchAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.42";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromV2Json_BuildAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateString(kStr);

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(version_json);
}

static void FromV2Json_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* version_json;
  struct CfgConfigVersion actual;
  struct CfgConfigVersion* result;

  version_json = cJSON_CreateFalse();

  result = CfgConfigVersion_FromV2Json(&actual, version_json);

  CuAssertPtrEquals(tc, NULL, result);
}

static void AddToJson_Object_AddsEntry(CuTest* tc) {
  cJSON* object;
  cJSON* result;
  cJSON* version_json;

  object = cJSON_CreateObject();

  result = CfgConfigVersion_AddToJson(&kConfigVersion, object);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, cJSON_HasObjectItem(object, CfgConfigVersion_kV2JsonKey));
  version_json =
      cJSON_GetObjectItemCaseSensitive(object, CfgConfigVersion_kV2JsonKey);
  CuAssertTrue(tc, cJSON_IsString(version_json));
  CuAssertStrEquals(tc, kConfigVersionStr, cJSON_GetStringValue(version_json));

  CfgConfigVersion_RemoveFromJson(object);
  cJSON_Delete(object);
}

static void AddToJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  cJSON* result;

  object = cJSON_CreateFalse();

  result = CfgConfigVersion_AddToJson(&kConfigVersion, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void Compare_SameVersions_ReturnsZero(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };

  CuAssertIntEquals(tc, 0, CfgConfigVersion_Compare(&lhs, &lhs));
}

static void Compare_EqualVersions_ReturnsZero(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 0, 0 } };

  CuAssertIntEquals(tc, 0, CfgConfigVersion_Compare(&lhs, &rhs));
}

static void Compare_LtMajor_ReturnsNegative(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 2, 0, 0, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtMajor_ReturnsPositive(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 2, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 0, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtMinor_ReturnsNegative(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 1, 0, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtMinor_ReturnsPositive(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 2, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 1, 0, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtPatch_ReturnsNegative(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 1, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtPatch_ReturnsPositive(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 2, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 1, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtBuild_ReturnsNegative(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 0, 1 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtBuild_ReturnsPositive(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 2 } };
  struct CfgConfigVersion rhs = { { 1, 0, 0, 1 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_DifferentAll_ReturnsNonZero(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 2, 3, 4 } };

  CuAssertTrue(tc, CfgConfigVersion_Compare(&lhs, &rhs) != 0);
}

static void Equals_SameVersions_ReturnsTrue(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Equals(&lhs, &lhs));
}

static void Equals_EqualVersions_ReturnsTrue(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 0, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentMajor_ReturnsFalse(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 2, 0, 0, 0 } };

  CuAssertTrue(tc, !CfgConfigVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentMinor_ReturnsFalse(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 1, 0, 0 } };

  CuAssertTrue(tc, !CfgConfigVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentPatch_ReturnsFalse(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 1, 0 } };

  CuAssertTrue(tc, !CfgConfigVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentBuild_ReturnsFalse(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 0, 0, 1 } };

  CuAssertTrue(tc, !CfgConfigVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentAll_ReturnsFalse(CuTest* tc) {
  struct CfgConfigVersion lhs = { { 1, 0, 0, 0 } };
  struct CfgConfigVersion rhs = { { 1, 2, 3, 4 } };

  CuAssertTrue(tc, !CfgConfigVersion_Equals(&lhs, &rhs));
}

static void GetJsonKey_WithLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;
  size_t length;

  result = CfgConfigVersion_GetJsonKey(&length);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 0, strcmp(result, CfgConfigVersion_kV2JsonKey));
  CuAssertTrue(tc, strlen(result) == length);
}

static void GetJsonKey_WithNullLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;

  result = CfgConfigVersion_GetJsonKey(NULL);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 0, strcmp(result, CfgConfigVersion_kV2JsonKey));
  CuAssertTrue(tc, strlen(result) > 0);
}

static void IsV1Config_V1Config_ReturnsTrue(CuTest* tc) {
  const struct CfgConfigVersion version = { { 3, 0, 4, 0 } };

  CuAssertTrue(tc, CfgConfigVersion_IsV1Config(&version));
}

static void IsV1Config_V2Config_ReturnsFalse(CuTest* tc) {
  const struct CfgConfigVersion version = { { 3, 1, 0, 0 } };

  CuAssertTrue(tc, !CfgConfigVersion_IsV1Config(&version));
}

static void UpgradeToCurrent_LtVersion_UpgradesVersion(CuTest* tc) {
  struct CfgConfigVersion version = { { 0, 0, 0, 0 } };
  int result;

  result = CfgConfigVersion_UpgradeToCurrent(&version);

  CuAssertTrue(tc, result < 0);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&version, &kDefaultConfigVersion));
}

static void UpgradeToCurrent_EqVersion_NoUpgrade(CuTest* tc) {
  struct CfgConfigVersion version = kDefaultConfigVersion;
  int result;

  result = CfgConfigVersion_UpgradeToCurrent(&version);

  CuAssertTrue(tc, result == 0);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&version, &kDefaultConfigVersion));
}

static void UpgradeToCurrent_GtVersion_NoUpgrade(CuTest* tc) {
  struct CfgConfigVersion expected = {
    { INT_MAX, INT_MAX, INT_MAX, INT_MAX }
  };
  struct CfgConfigVersion version = { { INT_MAX, INT_MAX, INT_MAX, INT_MAX } };
  int result;

  result = CfgConfigVersion_UpgradeToCurrent(&version);

  CuAssertTrue(tc, result > 0);
  CuAssertTrue(tc, CfgConfigVersion_Equals(&version, &expected));
}

/**
 * External
 */

CuSuite* CfgConfigVersion_GetTestSuite(void) {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, InitDefault_ReturnsDefault);

  SUITE_ADD_TEST(suite, FromV1Json_Valid_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV1Json_MajorBelowMin_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_MinorBelowMin_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_PatchBelowMin_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_BuildBelowMin_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_MajorAboveMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_MinorAboveMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_PatchAboveMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_BuildAboveMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_ObjectTypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_MajorTypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_MinorTypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_PatchTypeMismatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV1Json_BuildTypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, FromV2Json_Valid_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_MajorZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_MinorZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_PatchZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_BuildZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_MajorIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_MinorIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_PatchIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_BuildIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromV2Json_TerminateStringPeriod_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MajorNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MinorNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_PatchNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_BuildNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MissingMajor_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MissingMinor_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MissingPatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MissingBuild_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_PrefixMajorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_SuffixMajorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_PrefixMinorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_SuffixMinorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_PrefixPatchNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_SuffixPatchNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_PrefixBuildNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_SuffixBuildNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_CommaDelimiters_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MajorLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MinorLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_PatchLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_BuildLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MajorAboveIntMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_MinorAboveIntMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_PatchAboveIntMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_BuildAboveIntMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromV2Json_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, AddToJson_Object_AddsEntry);
  SUITE_ADD_TEST(suite, AddToJson_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, Compare_SameVersions_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_EqualVersions_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_LtMajor_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtMajor_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtMinor_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtMinor_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtPatch_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtPatch_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtBuild_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtBuild_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_DifferentAll_ReturnsNonZero);

  SUITE_ADD_TEST(suite, Equals_SameVersions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualVersions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentMajor_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentMinor_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentPatch_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentBuild_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentAll_ReturnsFalse);

  SUITE_ADD_TEST(suite, GetJsonKey_WithLength_ReturnsJsonKey);
  SUITE_ADD_TEST(suite, GetJsonKey_WithNullLength_ReturnsJsonKey);

  SUITE_ADD_TEST(suite, IsV1Config_V1Config_ReturnsTrue);
  SUITE_ADD_TEST(suite, IsV1Config_V2Config_ReturnsFalse);

  SUITE_ADD_TEST(suite, UpgradeToCurrent_LtVersion_UpgradesVersion);
  SUITE_ADD_TEST(suite, UpgradeToCurrent_EqVersion_NoUpgrade);
  SUITE_ADD_TEST(suite, UpgradeToCurrent_GtVersion_NoUpgrade);

  return suite;
}
