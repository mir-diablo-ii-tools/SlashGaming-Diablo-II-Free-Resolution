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

#include "sgd2fr/config/entries/cfg_custom_mpq_file_path_test.h"

#include <stddef.h>
#include <string.h>
#include <wchar.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/config/entries/cfg_custom_mpq_file_path.h"

#define DEFAULT_PATH L"SGD2FreeRes.mpq"
#define DEFAULT_CHAR_PATH "SGD2FreeRes.mpq"
enum {
  kDefaultPathLength = sizeof(DEFAULT_PATH) / sizeof(DEFAULT_PATH[0]) - 1
};

static struct CfgCustomMpqFilePath kDefaultPath = {
  DEFAULT_PATH, kDefaultPathLength
};

/**
 * Tests
 */

static void InitDefault_ReturnsDefault(CuTest* tc) {
  struct CfgCustomMpqFilePath path;
  struct CfgCustomMpqFilePath* result;

  result = CfgCustomMpqFilePath_InitDefault(&path);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgCustomMpqFilePath_Equals(&path, &kDefaultPath));
}

static void FromJson_Valid_ReturnsPath(CuTest* tc) {
  cJSON* path_json;
  struct CfgCustomMpqFilePath path;
  struct CfgCustomMpqFilePath* result;

  path_json = cJSON_CreateString(DEFAULT_CHAR_PATH);

  result = CfgCustomMpqFilePath_FromJson(&path, path_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgCustomMpqFilePath_Equals(&path, &kDefaultPath));

  cJSON_Delete(path_json);
}

static void FromJson_Empty_ReturnsNull(CuTest* tc) {
  cJSON* path_json;
  struct CfgCustomMpqFilePath path;
  struct CfgCustomMpqFilePath* result;

  path_json = cJSON_CreateString("");

  result = CfgCustomMpqFilePath_FromJson(&path, path_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(path_json);
}

static void FromJson_LengthAboveMax_ReturnsNull(CuTest* tc) {
  char path_str[1024];
  enum {
    kPathStrCapacity = sizeof(path_str) / sizeof(path_str[0])
  };
  cJSON* path_json;
  struct CfgCustomMpqFilePath path;
  struct CfgCustomMpqFilePath* result;

  memset(path_str, 'a', kPathStrCapacity);
  strcpy(&path_str[kPathStrCapacity - 5], ".mpq");
  path_json = cJSON_CreateString(path_str);

  result = CfgCustomMpqFilePath_FromJson(&path, path_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(path_json);
}

static void FromJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* path_json;
  struct CfgCustomMpqFilePath path;
  struct CfgCustomMpqFilePath* result;

  path_json = cJSON_CreateObject();

  result = CfgCustomMpqFilePath_FromJson(&path, path_json);

  CuAssertPtrEquals(tc, NULL, result);

  cJSON_Delete(path_json);
}

static void AddToJson_Object_AddsEntry(CuTest* tc) {
  cJSON* object;
  cJSON* result;
  const char* key;
  cJSON* path_json;

  object = cJSON_CreateObject();

  result = CfgCustomMpqFilePath_AddToJson(&kDefaultPath, object);

  CuAssertPtrNotNull(tc, result);
  key = CfgCustomMpqFilePath_GetJsonKey(NULL);
  CuAssertTrue(tc, cJSON_HasObjectItem(object, key));
  path_json = cJSON_GetObjectItem(object, key);
  CuAssertTrue(tc, cJSON_IsString(path_json));

  cJSON_Delete(object);
}

static void AddToJson_TypeMismatch_ReturnsNull(CuTest* tc) {
  cJSON* object;
  cJSON* result;

  object = cJSON_CreateFalse();

  result = CfgCustomMpqFilePath_AddToJson(&kDefaultPath, object);

  CuAssertPtrEquals(tc, NULL, result);
}

static void Compare_SamePaths_ReturnsZero(CuTest* tc) {
  CuAssertIntEquals(
      tc, 0, CfgCustomMpqFilePath_Compare(&kDefaultPath, &kDefaultPath));
}

static void Compare_EqualPaths_ReturnsZero(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;

  CuAssertIntEquals(tc, 0, CfgCustomMpqFilePath_Compare(&path, &kDefaultPath));
}

static void Compare_LtPaths_ReturnsNegative(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;
  path.str[0] = 'A';

  CuAssertTrue(tc, CfgCustomMpqFilePath_Compare(&path, &kDefaultPath) < 0);
}

static void Compare_GtPaths_ReturnsPositive(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;
  path.str[0] = 'b';

  CuAssertTrue(tc, CfgCustomMpqFilePath_Compare(&path, &kDefaultPath) > 0);
}

static void Compare_ShorterPaths_ReturnsNegative(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;
  path.length = 0;
  path.str[0] = '\0';

  CuAssertTrue(tc, CfgCustomMpqFilePath_Compare(&path, &kDefaultPath) < 0);
}

static void Compare_LongerPaths_ReturnsPositive(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;
  wcscat(path.str, kDefaultPath.str);
  path.length *= 2;

  CuAssertTrue(tc, CfgCustomMpqFilePath_Compare(&path, &kDefaultPath) > 0);
}

static void Equals_SamePaths_ReturnsTrue(CuTest* tc) {
  CuAssertTrue(tc, CfgCustomMpqFilePath_Equals(&kDefaultPath, &kDefaultPath));
}

static void Equals_EqualPaths_ReturnsTrue(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;

  CuAssertTrue(tc, CfgCustomMpqFilePath_Equals(&kDefaultPath, &path));
}

static void Equals_DifferentLength_ReturnsFalse(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;
  path.str[0] = '\0';
  path.length = 0;

  CuAssertTrue(tc, !CfgCustomMpqFilePath_Equals(&kDefaultPath, &path));
}

static void Equals_DifferentPaths_ReturnsFalse(CuTest* tc) {
  struct CfgCustomMpqFilePath path;

  path = kDefaultPath;
  path.str[0] = 'b';

  CuAssertTrue(tc, !CfgCustomMpqFilePath_Equals(&kDefaultPath, &path));
}

static void GetJsonKey_WithLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;
  size_t length;

  result = CfgCustomMpqFilePath_GetJsonKey(&length);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) == length);
}

static void GetJsonKey_WithNullLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;

  result = CfgCustomMpqFilePath_GetJsonKey(NULL);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) > 0);
}

/**
 * External
 */

CuSuite* CfgCustomMpqFilePath_GetTestSuite(void) {
  CuSuite* suite;

  suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, InitDefault_ReturnsDefault);

  SUITE_ADD_TEST(suite, FromJson_Valid_ReturnsPath);
  SUITE_ADD_TEST(suite, FromJson_Empty_ReturnsNull);
  SUITE_ADD_TEST(suite, FromJson_LengthAboveMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromJson_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, AddToJson_Object_AddsEntry);
  SUITE_ADD_TEST(suite, AddToJson_TypeMismatch_ReturnsNull);

  SUITE_ADD_TEST(suite, Compare_SamePaths_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_EqualPaths_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_LtPaths_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtPaths_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_ShorterPaths_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_LongerPaths_ReturnsPositive);

  SUITE_ADD_TEST(suite, Equals_SamePaths_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualPaths_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentLength_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentPaths_ReturnsFalse);

  SUITE_ADD_TEST(suite, GetJsonKey_WithLength_ReturnsJsonKey);
  SUITE_ADD_TEST(suite, GetJsonKey_WithNullLength_ReturnsJsonKey);

  return suite;
}
