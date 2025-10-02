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

#include "sgd2fr/config/cfg_config_test.h"

#include <stddef.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <shlwapi.h>

#include <cJSON.h>
#include <CuTest.h>

#include "sgd2fr/config/cfg_config.h"
#include "sgd2fr/config/cfg_entries.h"
#include "sgd2fr/common/resolution.h"

#define PrintConfig(config) PrintConfig_Impl(config, __LINE__)

static void PrintConfig_Impl(const struct CfgConfig* config, int line) {
  cJSON* object;

  object = cJSON_CreateObject();
  if (object == NULL) {
    printf("Could not print config.\n");
    goto error;
  }

  CfgEntries_AddToJson(&config->entries, object);
  printf("%s\n", cJSON_Print(object));

  cJSON_Delete(object);

error:
  return;
}

static void Precondition_CheckFiles(void) {
  static wchar_t kPathsToCheck[][MAX_PATH] = {
    L"../data/default.cfg",
    L"../data/empty.cfg",
    L"../data/standard_v2.cfg",
    L"../data/standard_v3.cfg",
    L"../data/utf-8.cfg"
  };
  enum {
    kPathsToCheckCount = sizeof(kPathsToCheck) / sizeof(kPathsToCheck[0])
  };
  size_t i;

  for (i = 0; i < kPathsToCheckCount; ++i) {
    if (!PathFileExistsW(kPathsToCheck[i])) {
      wprintf(L"File not found: %s\n", kPathsToCheck[i]);
    }
  }
}

static void InitDefault_ReturnsDefault(CuTest* tc) {
  struct CfgConfig config;
  struct CfgConfig* result;

  result = CfgConfig_InitDefault(&config);

  CuAssertPtrNotNull(tc, result);

  CfgConfig_Deinit(&config);
}

static void Read_Default_ReturnsDefault(CuTest* tc) {
  struct CfgConfig expected_config;
  struct CfgConfig config;
  struct CfgConfig* result;

  CfgConfig_InitDefault(&expected_config);

  result = CfgConfig_Read(&config, L"../data/default.cfg");

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfig_Equals(&config, &expected_config));

  CfgConfig_Deinit(&config);
  CfgConfig_Deinit(&expected_config);
}

static void Read_StandardV2_ReturnsUpgradedConfig(CuTest* tc) {
  static struct Resolution kResolutions[] = {
    { 640, 480 },
    { 800, 600 },
    { 1024, 768 }
  };
  static const struct CfgConfig kExpectedConfig = {
    {
      { {{ 3, 1, 0, 0 } } },
      { L"SGD2FreeRes.mpq", 15 },
      { 4 },
      { kResolutions, 3, 3 },
      { { 1024, 768 } },
      { { 800, 600 } }
    }
  };
  struct CfgConfig config;
  struct CfgConfig* result;

  result = CfgConfig_Read(&config, L"../data/standard_v2.cfg");

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfig_Equals(&config, &kExpectedConfig));

  CfgConfig_Deinit(&config);
}

static void Read_StandardV3_ReturnsConfig(CuTest* tc) {
  static struct Resolution kResolutions[] = {
    { 856, 480 },
    { 1068, 600 }
  };
  static const struct CfgConfig kExpectedConfig = {
    {
      { {{ 3, 4, 5, 0 } } },
      { L"Custom.mpq", 10 },
      { 3 },
      { kResolutions, 3, 2 },
      { { 1068, 600 } },
      { { 1024, 768 } }
    }
  };
  struct CfgConfig config;
  struct CfgConfig* result;

  result = CfgConfig_Read(&config, L"../data/standard_v3.cfg");

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfig_Equals(&config, &kExpectedConfig));

  CfgConfig_Deinit(&config);
}

static void Read_Empty_ReturnsDefault(CuTest* tc) {
  struct CfgConfig expected_config;
  struct CfgConfig config;
  struct CfgConfig* result;

  CfgConfig_InitDefault(&expected_config);

  result = CfgConfig_Read(&config, L"../data/empty.cfg");

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfig_Equals(&config, &expected_config));

  CfgConfig_Deinit(&config);
  CfgConfig_Deinit(&expected_config);
}

static void Read_Utf8_ReturnsConfig(CuTest* tc) {
  static struct Resolution kResolutions[] = {
    { 856, 480 },
    { 1068, 600 }
  };
  static const struct CfgConfig kExpectedConfig = {
    {
      { {{ 3, 4, 5, 0 } } },
      { L"A" L"\x30C7\x30A3\x30A2\x30D6\x30ED" L"Custom.mpq", 16 },
      { 3 },
      { kResolutions, 3, 2 },
      { { 1068, 600 } },
      { { 1024, 768 } }
    }
  };
  struct CfgConfig config;
  struct CfgConfig* result;

  result = CfgConfig_Read(&config, L"../data/utf-8.cfg");

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, CfgConfig_Equals(&config, &kExpectedConfig));

  CfgConfig_Deinit(&config);
}

static void Write_Default_WritesFile(CuTest* tc) {
  static const wchar_t kPath[] = L"../data/output_default.cfg";
  struct CfgConfig default_config;
  int write_succeeded;
  struct CfgConfig read_back_config;

  CfgConfig_InitDefault(&default_config);

  write_succeeded = CfgConfig_Write(&default_config, kPath);

  CuAssertTrue(tc, write_succeeded);
  CfgConfig_Read(&read_back_config, kPath);
  CuAssertTrue(tc, CfgConfig_Equals(&read_back_config, &default_config));

  CfgConfig_Deinit(&read_back_config);
  CfgConfig_Deinit(&default_config);
}

static void Write_Modified_WritesFile(CuTest* tc) {
  static const wchar_t kPath[] = L"../data/output_modified.cfg";
  struct CfgConfig source_config;
  int write_succeeded;
  struct CfgConfig read_back_config;

  CfgConfig_InitDefault(&source_config);
  source_config.entries.metadata.version.value.build_version = 1337;
  source_config.entries.indent_width.value = 12;

  write_succeeded = CfgConfig_Write(&source_config, kPath);

  CuAssertTrue(tc, write_succeeded);
  CfgConfig_Read(&read_back_config, kPath);
  CuAssertTrue(tc, CfgConfig_Equals(&read_back_config, &source_config));

  CfgConfig_Deinit(&read_back_config);
  CfgConfig_Deinit(&source_config);
}

static void Write_V2ToV3_WritesFile(CuTest* tc) {
  static struct Resolution kResolutions[] = {
    { 640, 480 },
    { 800, 600 },
    { 1024, 768 },
  };
  static const struct CfgConfig kExpectedConfig = {
    {
      { {{ 3, 1, 0, 0 } } },
      { L"SGD2FreeRes.mpq", 15 },
      { 4 },
      { kResolutions, 3, 3 },
      { { 1024, 768 } },
      { { 800, 600 } }
    }
  };
  static const wchar_t kSourcePath[] = L"../data/standard_v2.cfg";
  static const wchar_t kConvertedPath[] = L"../data/output_v2_to_v3.cfg";
  struct CfgConfig source_config;
  int write_succeeded;
  struct CfgConfig converted_config;

  CfgConfig_Read(&source_config, kSourcePath);

  write_succeeded = CfgConfig_Write(&source_config, kConvertedPath);

  CuAssertTrue(tc, write_succeeded);
  CfgConfig_Read(&converted_config, kConvertedPath);
  CuAssertTrue(tc, CfgConfig_Equals(&converted_config, &kExpectedConfig));

  CfgConfig_Deinit(&converted_config);
  CfgConfig_Deinit(&source_config);
}

static void Write_Utf8_WritesFile(CuTest* tc) {
  static const wchar_t kPath[] = L"../data/output_utf-8.cfg";
  static struct Resolution kResolutions[] = {
    { 856, 480 },
    { 1068, 600 }
  };
  static const struct CfgConfig kSourceConfig = {
    {
      { {{ 3, 4, 5, 0 } } },
      { L"A" L"\x30C7\x30A3\x30A2\x30D6\x30ED" L"Custom.mpq", 16 },
      { 3 },
      { kResolutions, 3, 2 },
      { { 1068, 600 } },
      { { 1024, 768 } }
    }
  };
  int write_succeeded;
  struct CfgConfig actual_config;

  write_succeeded =
      CfgConfig_Write(&kSourceConfig, kPath);

  CuAssertTrue(tc, write_succeeded);
  CfgConfig_Read(&actual_config, kPath);
  CuAssertTrue(tc, CfgConfig_Equals(&actual_config, &kSourceConfig));

  CfgConfig_Deinit(&actual_config);
}

/**
 * External
 */

CuSuite* CfgConfig_GetTestSuite(void) {
  CuSuite* suite;

  suite = CuSuiteNew();

  Precondition_CheckFiles();

  SUITE_ADD_TEST(suite, InitDefault_ReturnsDefault);

  SUITE_ADD_TEST(suite, Read_Default_ReturnsDefault);
  SUITE_ADD_TEST(suite, Read_StandardV2_ReturnsUpgradedConfig);
  SUITE_ADD_TEST(suite, Read_StandardV3_ReturnsConfig);
  SUITE_ADD_TEST(suite, Read_Empty_ReturnsDefault);
  SUITE_ADD_TEST(suite, Read_Utf8_ReturnsConfig);

  SUITE_ADD_TEST(suite, Write_Default_WritesFile);
  SUITE_ADD_TEST(suite, Write_Modified_WritesFile);
  SUITE_ADD_TEST(suite, Write_V2ToV3_WritesFile);
  SUITE_ADD_TEST(suite, Write_Utf8_WritesFile);

  return suite;
}
