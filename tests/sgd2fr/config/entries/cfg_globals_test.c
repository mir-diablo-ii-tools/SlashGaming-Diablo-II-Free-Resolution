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

#include "sgd2fr/config/entries/cfg_globals_test.h"

#include <stddef.h>
#include <string.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/config/entries/cfg_globals.h"
#include "sgd2fr/config/entries/globals/cfg_indent_width.h"

/**
 * External
 */

static void AddToJson_AddsEntry(CuTest* tc) {
  struct CfgGlobals globals;
  cJSON* object;
  cJSON* result;
  cJSON* globals_json;
  cJSON* indent_width_json;

  globals.indent_width.value = 42;
  object = cJSON_CreateObject();

  result = CfgGlobals_AddToJson(object, &globals);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, cJSON_HasObjectItem(object, CfgGlobals_GetJsonKey(NULL)));
  globals_json = cJSON_GetObjectItem(object, CfgGlobals_GetJsonKey(NULL));
  CuAssertTrue(
      tc, cJSON_HasObjectItem(globals_json, CfgIndentWidth_GetJsonKey(NULL)));
  indent_width_json =
      cJSON_GetObjectItem(globals_json, CfgIndentWidth_GetJsonKey(NULL));
  CuAssertIntEquals(tc, 42, cJSON_GetNumberValue(indent_width_json));

  CfgGlobals_RemoveFromJson(object);
  cJSON_Delete(object);
}

static void Equals_SameGlobals_ReturnsTrue(CuTest* tc) {
  struct CfgGlobals lhs;

  lhs.indent_width.value = 4;

  CuAssertTrue(tc, CfgGlobals_Equals(&lhs, &lhs));
}

static void Equals_EqualGlobals_ReturnsTrue(CuTest* tc) {
  struct CfgGlobals lhs;
  struct CfgGlobals rhs;

  lhs.indent_width.value = 4;
  rhs.indent_width.value = 4;

  CuAssertTrue(tc, CfgGlobals_Equals(&lhs, &rhs));
}

static void Equals_DifferentGlobals_ReturnsFalse(CuTest* tc) {
  struct CfgGlobals lhs;
  struct CfgGlobals rhs;

  lhs.indent_width.value = 4;
  rhs.indent_width.value = 8;

  CuAssertTrue(tc, !CfgGlobals_Equals(&lhs, &rhs));
}

static void FromJson_Valid_Converts(CuTest* tc) {
  cJSON* global_json;
  struct CfgGlobals globals;
  struct CfgGlobals* result;

  global_json = cJSON_CreateObject();
  cJSON_AddNumberToObject(global_json, CfgIndentWidth_GetJsonKey(NULL), 42);

  result = CfgGlobals_FromJson(&globals, global_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 42, globals.indent_width.value);

  cJSON_DeleteItemFromObjectCaseSensitive(
      global_json, CfgIndentWidth_GetJsonKey(NULL));
  cJSON_Delete(global_json);
}

static void FromJson_MissingEntries_SetsEntriesToDefault(CuTest* tc) {
  cJSON* global_json;
  struct CfgGlobals globals;
  struct CfgGlobals* result;

  global_json = cJSON_CreateObject();

  result = CfgGlobals_FromJson(&globals, global_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgGlobals_Equals(&globals, CfgGlobals_GetDefault()));

  cJSON_Delete(global_json);
}

static void FromJson_TypeMismatch_SetsToDefault(CuTest* tc) {
  cJSON* global_json;
  struct CfgGlobals globals;
  struct CfgGlobals* result;

  global_json = cJSON_CreateNumber(42);

  result = CfgGlobals_FromJson(&globals, global_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgGlobals_Equals(&globals, CfgGlobals_GetDefault()));

  cJSON_Delete(global_json);
}

static void GetDefault_SubEntryAreDefaults(CuTest* tc) {
  const struct CfgGlobals* default_globals;

  default_globals = CfgGlobals_GetDefault();

  CuAssertPtrNotNull(tc, default_globals);
  CuAssertTrue(
      tc,
      CfgIndentWidth_Equals(
          &default_globals->indent_width, CfgIndentWidth_GetDefault()));
}

static void GetJsonKey_WithLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;
  size_t length;

  result = CfgGlobals_GetJsonKey(&length);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) == length);
}

static void GetJsonKey_WithNullLength_ReturnsJsonKey(CuTest* tc) {
  const char* result;

  result = CfgGlobals_GetJsonKey(NULL);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, strlen(result) > 0);
}

CuSuite* CfgGlobals_GetTestSuite(void) {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, AddToJson_AddsEntry);

  SUITE_ADD_TEST(suite, Equals_SameGlobals_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualGlobals_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentGlobals_ReturnsFalse);

  SUITE_ADD_TEST(suite, FromJson_Valid_Converts);
  SUITE_ADD_TEST(suite, FromJson_TypeMismatch_SetsToDefault);

  SUITE_ADD_TEST(suite, GetDefault_SubEntryAreDefaults);

  SUITE_ADD_TEST(suite, GetJsonKey_WithLength_ReturnsJsonKey);
  SUITE_ADD_TEST(suite, GetJsonKey_WithNullLength_ReturnsJsonKey);

  return suite;
}
