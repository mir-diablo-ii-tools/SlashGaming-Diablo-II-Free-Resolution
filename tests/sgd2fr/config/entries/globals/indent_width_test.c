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

#include "sgd2fr/config/entries/globals/indent_width_test.h"

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/config/entries/globals/indent_width.h"

/**
 * External
 */

static void AddToJson_AddsEntry(CuTest* tc) {
  struct IndentWidth indent_width = { 42 };
  cJSON* object;
  cJSON* result;
  cJSON* entry;

  object = cJSON_CreateObject();
  result = IndentWidth_AddToJson(object, &indent_width);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, cJSON_HasObjectItem(object, IndentWidth_kKey));
  entry = cJSON_GetObjectItem(object, IndentWidth_kKey);
  CuAssertIntEquals(tc, 42, cJSON_GetNumberValue(entry));

  cJSON_DeleteItemFromObjectCaseSensitive(object, IndentWidth_kKey);
  cJSON_Delete(object);
}

static void FromJson_Valid_Converts(CuTest* tc) {
  cJSON* value;
  struct IndentWidth indent_width;
  struct IndentWidth* result;

  value = cJSON_CreateNumber(42);

  result = IndentWidth_FromJson(&indent_width, value);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 42, indent_width.value);

  cJSON_Delete(value);
}

static void FromJson_Negative_SetsToDefault(CuTest* tc) {
  cJSON* value;
  struct IndentWidth indent_width;
  struct IndentWidth* result;

  value = cJSON_CreateNumber(-42);

  result = IndentWidth_FromJson(&indent_width, value);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, IndentWidth_kDefault.value, indent_width.value);

  cJSON_Delete(value);
}

static void FromJson_Zero_SetsToDefault(CuTest* tc) {
  cJSON* value;
  struct IndentWidth indent_width;
  struct IndentWidth* result;

  value = cJSON_CreateNumber(0);

  result = IndentWidth_FromJson(&indent_width, value);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, IndentWidth_kDefault.value, indent_width.value);

  cJSON_Delete(value);
}

static void FromJson_TypeMismatch_SetsToDefault(CuTest* tc) {
  cJSON* value;
  struct IndentWidth indent_width;
  struct IndentWidth* result;

  value = cJSON_CreateString("42");

  result = IndentWidth_FromJson(&indent_width, value);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, IndentWidth_kDefault.value, indent_width.value);

  cJSON_Delete(value);
}

CuSuite* IndentWidth_GetTestSuite() {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, AddToJson_AddsEntry);
  SUITE_ADD_TEST(suite, FromJson_Valid_Converts);
  SUITE_ADD_TEST(suite, FromJson_Negative_SetsToDefault);
  SUITE_ADD_TEST(suite, FromJson_Zero_SetsToDefault);
  SUITE_ADD_TEST(suite, FromJson_TypeMismatch_SetsToDefault);

  return suite;
}
