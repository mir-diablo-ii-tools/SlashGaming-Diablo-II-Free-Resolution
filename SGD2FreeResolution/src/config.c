/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2021  Mir Drualga
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

#include "config.h"

#include <stddef.h>
#include <windows.h>
#include <shlwapi.h>

#include "compile_time_switch.h"
#include "config/config_ini.h"
#include "config/config_json_frozen.h"
#include "config/config_key_value.h"

/**
 * Config read/write
 */

#define CONFIG_INI_PATH L"./SGD2FreeResolution.user.ini"
#define CONFIG_JSON_PATH L"SGD2FreeResolution.user.json"

enum ConfigType {
  ConfigType_kIniWindows,
  ConfigType_kJsonFrozen,

  ConfigType_kDefaultConfig,
};

enum {
  kNumConfigTypes = ConfigType_kDefaultConfig
};

struct ConfigReadWriteFunctions {
  void (*read)(struct Config* config, const wchar_t* path);
  void (*write)(const struct Config* config, const wchar_t* path);
  void (*clean_up)(struct Config* config);
};

const struct ConfigReadWriteFunctions
kConfigReadWriteTable[kNumConfigTypes] = {
    {
        &ConfigIni_Read,
        &ConfigIni_Write,
        &ConfigIni_CleanUp,
    },
    {
        &ConfigJsonFrozen_Read,
        &ConfigJsonFrozen_Write,
        &ConfigJsonFrozen_CleanUp,
    },
};

const wchar_t* const kConfigPathTable[kNumConfigTypes] = {
    CONFIG_INI_PATH,
    CONFIG_JSON_PATH,
};

static int is_config_init = 0;
static struct Config config;
static enum ConfigType config_type;

static void InitConfig(void) {
  size_t i;

  if (is_config_init) {
    return;
  }

  config = kDefaultConfig;

  for (i = 0; i < kNumConfigTypes; i += 1) {
    if (PathFileExistsW(kConfigPathTable[i])) {
      ConfigJsonFrozen_Read(&config, kConfigPathTable[i]);
      config_type = i;
      is_config_init = 1;
      return;
    }
  }

  config_type = COMPILE_TIME_CREATE_CONFIG_FORMAT;
  kConfigReadWriteTable[config_type].write(
      &config,
      kConfigPathTable[config_type]
  );

  is_config_init = 1;
}

/**
 * External
 */

struct Config* GetConfig(void) {
  InitConfig();

  return &config;
}

void LoadConfig(void) {
  if (is_config_init) {
    kConfigReadWriteTable[config_type].clean_up(&config);
    is_config_init = 0;
  }

  InitConfig();
}

void WriteConfig(void) {
  InitConfig();

  kConfigReadWriteTable[config_type].write(
      &config,
      kConfigPathTable[config_type]
  );
}
