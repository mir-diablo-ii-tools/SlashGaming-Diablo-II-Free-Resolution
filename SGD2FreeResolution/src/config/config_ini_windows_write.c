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

#include "config_ini_windows.h"

#include <stddef.h>
#include <windows.h>

#include "config_key_value.h"

#define TO_STR_IMPL(lit) #lit
#define TO_STR(lit) TO_STR_IMPL(lit)

#define TO_WIDE_IMPL(str_lit) L##str_lit
#define TO_WIDE(str_lit) TO_WIDE_IMPL(str_lit)

#define CONFIG_MAIN_SECTION TO_WIDE(CONFIG_MAIN)

#define CONFIG_INGAME_RESOLUTIONS_SECTION \
    CONFIG_MAIN_SECTION L"." TO_WIDE(CONFIG_INGAME_RESOLUTIONS)

#define CONFIG_METADATA_SECTION \
    CONFIG_MAIN_SECTION L"." TO_WIDE(CONFIG_METADATA)

#define CONFIG_METADATA_VERSION_SECTION \
    CONFIG_METADATA_SECTION L"." TO_WIDE(CONFIG_METADATA_VERSION)

enum {
  kInt32StrCapacity = 10 + 1,
};

static void WriteMetadata(
    const struct Config* config,
    const wchar_t* path
) {
  BOOL is_write_success;
  wchar_t str[kInt32StrCapacity];

  _snwprintf(
      str,
      kInt32StrCapacity,
      L"%d",
      config->metadata.version.major_high
  );
  str[kInt32StrCapacity - 1] = L'\0';

  is_write_success = WritePrivateProfileStringW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_HIGH),
      str,
      path
  );

  _snwprintf(
      str,
      kInt32StrCapacity,
      L"%d",
      config->metadata.version.major_low
  );
  str[kInt32StrCapacity - 1] = L'\0';

  is_write_success = WritePrivateProfileStringW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_LOW),
      str,
      path
  );

  _snwprintf(
      str,
      kInt32StrCapacity,
      L"%d",
      config->metadata.version.minor_high
  );
  str[kInt32StrCapacity - 1] = L'\0';

  is_write_success = WritePrivateProfileStringW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MINOR_HIGH),
      str,
      path
  );

  _snwprintf(
      str,
      kInt32StrCapacity,
      L"%d",
      config->metadata.version.minor_low
  );
  str[kInt32StrCapacity - 1] = L'\0';

  is_write_success = WritePrivateProfileStringW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MINOR_LOW),
      str,
      path
  );
}

static void WriteCustomMpqPath(
    const struct Config* config,
    const wchar_t* path
) {
  BOOL is_write_success;

  is_write_success = WritePrivateProfileStringW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_CUSTOM_MPQ_PATH),
      config->custom_mpq_path,
      path
  );
}

static void WriteIngameResolutionMode(
    const struct Config* config,
    const wchar_t* path
) {
  BOOL is_write_success;

  wchar_t str[kInt32StrCapacity];

  _snwprintf(
      str,
      kInt32StrCapacity,
      L"%u",
      config->ingame_resolution_mode
  );
  str[kInt32StrCapacity - 1] = L'\0';

  is_write_success = WritePrivateProfileStringW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_INGAME_RESOLUTION_MODE),
      str,
      path
  );
}

static void WriteIngameResolutions(
    const struct Config* config,
    const wchar_t* path
) {
  enum {
    kWidthKeyMinCapacity = sizeof(L"Resolution .Width")
        / sizeof(wchar_t),
    kWidthKeyCapacity = kWidthKeyMinCapacity + kInt32StrCapacity - 1,

    kHeightKeyMinCapacity = sizeof(L"Resolution .Height")
        / sizeof(wchar_t),
    kHeightKeyCapacity = kHeightKeyMinCapacity + kInt32StrCapacity - 1,
  };

  size_t i;

  BOOL is_write_success;

  wchar_t width_key[kWidthKeyCapacity];
  wchar_t width_str[kInt32StrCapacity];
  wchar_t height_key[kHeightKeyCapacity];
  wchar_t height_str[kInt32StrCapacity];

  for (i = 0; i < config->ingame_resolutions.count; i += 1) {
    _snwprintf(
        width_key,
        kWidthKeyCapacity,
        L"Resolution %u.Width",
        i
    );
    width_key[kWidthKeyCapacity - 1] = L'\0';

    _snwprintf(
        width_str,
        kInt32StrCapacity,
        L"%d",
        config->ingame_resolutions.resolutions[i].width
    );
    width_str[kInt32StrCapacity - 1] = L'\0';

    _snwprintf(
        height_key,
        kHeightKeyCapacity,
        L"Resolution %u.Height",
        i
    );
    height_key[kHeightKeyCapacity - 1] = L'\0';

    _snwprintf(
        height_str,
        kInt32StrCapacity,
        L"%d",
        config->ingame_resolutions.resolutions[i].height
    );
    height_str[kInt32StrCapacity - 1] = L'\0';

    is_write_success = WritePrivateProfileStringW(
        CONFIG_INGAME_RESOLUTIONS_SECTION,
        width_key,
        width_str,
        path
    );

    is_write_success = WritePrivateProfileStringW(
        CONFIG_INGAME_RESOLUTIONS_SECTION,
        height_key,
        height_str,
        path
    );
  }
}

static void WriteIsEnableScreenBorderFrame(
    const struct Config* config,
    const wchar_t* path
) {
  BOOL is_write_success;

  is_write_success = WritePrivateProfileStringW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME),
      config->is_enable_screen_border_frame ? L"1" : L"0",
      path
  );
}

static void WriteIsUse800InterfaceBar(
    const struct Config* config,
    const wchar_t* path
) {
  BOOL is_write_success;

  is_write_success = WritePrivateProfileStringW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_USE_800_INTERFACE_BAR),
      config->is_use_800_interface_bar ? L"1" : L"0",
      path
  );
}

static void WriteIsUseOriginalScreenBorderFrame(
    const struct Config* config,
    const wchar_t* path
) {
  BOOL is_write_success;

  is_write_success = WritePrivateProfileStringW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME),
      config->is_use_original_screen_border_frame ? L"1" : L"0",
      path
  );
}

static void WriteMainMenuResolution(
    const struct Config* config,
    const wchar_t* path
) {
  BOOL is_write_success;
  wchar_t width_str[kInt32StrCapacity];
  wchar_t height_str[kInt32StrCapacity];

  _snwprintf(
      width_str,
      kInt32StrCapacity,
      L"%d",
      config->main_menu_resolution.width
  );
  width_str[kInt32StrCapacity - 1] = L'\0';

  _snwprintf(
      height_str,
      kInt32StrCapacity,
      L"%d",
      config->main_menu_resolution.height
  );
  height_str[kInt32StrCapacity - 1] = L'\0';

  is_write_success = WritePrivateProfileStringW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Width",
      width_str,
      path
  );

  is_write_success = WritePrivateProfileStringW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Height",
      height_str,
      path
  );
}

/**
 * External
 */

void ConfigIniWindows_Write(
    const struct Config* config,
    const wchar_t* path
) {
  WriteMetadata(config, path);
  WriteCustomMpqPath(config, path);
  WriteIngameResolutionMode(config, path);
  WriteIngameResolutions(config, path);
  WriteIsEnableScreenBorderFrame(config, path);
  WriteIsUse800InterfaceBar(config, path);
  WriteIsUseOriginalScreenBorderFrame(config, path);
  WriteMainMenuResolution(config, path);
}
