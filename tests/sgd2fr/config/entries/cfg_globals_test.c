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

#include <CuTest.h>

#include "cJSON.h"
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
  CuAssertTrue(tc, cJSON_HasObjectItem(object, CfgGlobals_kKey));
  globals_json = cJSON_GetObjectItem(object, CfgGlobals_kKey);
  CuAssertTrue(tc, cJSON_HasObjectItem(globals_json, CfgIndentWidth_kKey));
  indent_width_json = cJSON_GetObjectItem(globals_json, CfgIndentWidth_kKey);
  CuAssertIntEquals(tc, 42, cJSON_GetNumberValue(indent_width_json));

  CfgGlobals_RemoveFromJson(object);
  cJSON_Delete(object);
}

static void FromJson_Valid_Converts(CuTest* tc) {
  cJSON* global_json;
  struct CfgGlobals globals;
  struct CfgGlobals* result;

  global_json = cJSON_CreateObject();
  cJSON_AddNumberToObject(global_json, CfgIndentWidth_kKey, 42);

  result = CfgGlobals_FromJson(&globals, global_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 42, globals.indent_width.value);

  cJSON_DeleteItemFromObjectCaseSensitive(global_json, CfgIndentWidth_kKey);
  cJSON_Delete(global_json);
}

static void FromJson_MissingEntries_SetsEntriesToDefault(CuTest* tc) {
  cJSON* global_json;
  struct CfgGlobals globals;
  struct CfgGlobals* result;

  global_json = cJSON_CreateObject();

  result = CfgGlobals_FromJson(&globals, global_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(
      tc, CfgIndentWidth_GetDefault()->value, globals.indent_width.value);

  cJSON_Delete(global_json);
}

static void FromJson_TypeMismatch_SetsToDefault(CuTest* tc) {
  cJSON* global_json;
  struct CfgGlobals globals;
  struct CfgGlobals* result;

  global_json = cJSON_CreateNumber(42);

  result = CfgGlobals_FromJson(&globals, global_json);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(
      tc,
      CfgGlobals_GetDefault()->indent_width.value,
      globals.indent_width.value);

  cJSON_Delete(global_json);
}

CuSuite* CfgGlobals_GetTestSuite(void) {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, AddToJson_AddsEntry);
  SUITE_ADD_TEST(suite, FromJson_Valid_Converts);
  SUITE_ADD_TEST(suite, FromJson_TypeMismatch_SetsToDefault);

  return suite;
}
