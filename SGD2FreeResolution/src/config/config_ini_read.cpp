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

#include "config_ini.h"

#include <limits.h>
#include <stdio.h>
#include <windows.h>

#include <map>
#include <vector>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/wchar_t/filew.h>
#include "config_key_value.h"
#include "config_struct.hpp"

#define TO_WIDE_IMPL(str_lit) L##str_lit
#define TO_WIDE(str_lit) TO_WIDE_IMPL(str_lit)

#define CONFIG_MAIN_SECTION TO_WIDE(CONFIG_MAIN)

#define CONFIG_INGAME_RESOLUTIONS_SECTION \
    CONFIG_MAIN_SECTION L"." TO_WIDE(CONFIG_INGAME_RESOLUTIONS)

#define CONFIG_METADATA_SECTION \
    CONFIG_MAIN_SECTION L"." TO_WIDE(CONFIG_METADATA)

#define CONFIG_METADATA_VERSION_SECTION \
    CONFIG_METADATA_SECTION L"." TO_WIDE(CONFIG_METADATA_VERSION)

/* These specific characters are unlikely to be used in text. */
#define INI_DEFAULT_STR L"\a\b\f"

enum {
  kIniDefaultStrLength = sizeof(INI_DEFAULT_STR)
      / sizeof(INI_DEFAULT_STR[0]) - 1,
};

static void ExitOnInvalidConfigKey(
    const wchar_t* section_name,
    const wchar_t* config_key,
    const wchar_t* file_path,
    int line
) {
  Mdc_Error_ExitOnGeneralError(
      L"Error",
      L"Invalid INI config key \"%ls.%ls\". The program will now "
          L"close.",
      file_path,
      line,
      section_name,
      config_key
  );
}

static void ExitOnInvalidConfigValue(
    const wchar_t* section_name,
    const wchar_t* config_key,
    const wchar_t* file_path,
    int line
) {
  Mdc_Error_ExitOnGeneralError(
      L"Error",
      L"Invalid INI config value for \"%ls.%ls\". The program will "
          L"now close.",
      file_path,
      line,
      section_name,
      config_key
  );
}

static void ExitOnResolutionParseError(
    const wchar_t* key,
    const wchar_t* file_path,
    int line
) {
  Mdc_Error_ExitOnGeneralError(
      L"Error",
      L"Could not parse config value mapped to key: %ls",
      file_path,
      line,
      key
  );
}

static void MallocIniStringW(
    ::std::vector<wchar_t>& buffer,
    const wchar_t* path,
    const wchar_t* section,
    const wchar_t* key
) {
  DWORD get_private_profile_string_result;

  if (buffer.size() == 0) {
    buffer.resize(16);
  }

  /* Read the config string. */
  while (1) {
    get_private_profile_string_result = GetPrivateProfileStringW(
        section,
        key,
        INI_DEFAULT_STR,
        buffer.data(),
        buffer.size(),
        path
    );

    if (get_private_profile_string_result < (buffer.size() - 2)) {
      break;
    }

    buffer.resize(buffer.size() * 2);
  }
}

static void ReadMetadataVersion(
    struct Config& config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config.metadata.version.major_high = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_HIGH),
      kDefaultInvalidValue,
      path
  );

  if (config.metadata.version.major_high == 42) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_HIGH),
        __FILEW__,
        __LINE__
    );
  }

  config.metadata.version.major_low = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_LOW),
      kDefaultInvalidValue,
      path
  );

  if (config.metadata.version.major_low == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_LOW),
        __FILEW__,
        __LINE__
    );
  }

  config.metadata.version.minor_high = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MINOR_HIGH),
      kDefaultInvalidValue,
      path
  );

  if (config.metadata.version.minor_high == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MINOR_HIGH),
        __FILEW__,
        __LINE__
    );
  }

  config.metadata.version.minor_low = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MINOR_LOW),
      kDefaultInvalidValue,
      path
  );

  if (config.metadata.version.minor_low == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MINOR_LOW),
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadMetadata(
    struct Config& config,
    const wchar_t* path
) {
  ReadMetadataVersion(config, path);
}

static void ReadCustomMpqPath(
    struct Config& config,
    const wchar_t* path
) {
  ::std::vector<wchar_t> buffer;

  MallocIniStringW(
      buffer,
      path,
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_CUSTOM_MPQ_PATH)
  );

  config.impl->custom_mpq_path = buffer.data();
  config.custom_mpq_path = config.impl->custom_mpq_path.c_str();

  if (wcscmp(config.custom_mpq_path, INI_DEFAULT_STR) == 0) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_CUSTOM_MPQ_PATH),
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadIngameResolutionMode(
    struct Config& config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config.ingame_resolution_mode = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_INGAME_RESOLUTION_MODE),
      kDefaultInvalidValue,
      path
  );

  if (config.ingame_resolution_mode == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_INGAME_RESOLUTION_MODE),
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadIngameResolutions(
    struct Config& config,
    const wchar_t* path
) {
  enum {
    kResolutionStrLength = sizeof("Resolution ") - 1,
  };

  ::std::vector<wchar_t> keys;

  size_t key_start_index;
  size_t key_length;

  ::std::vector<wchar_t> resolution_str;

  typedef ::std::map<size_t, GameResolution> ResolutionsMap;
  ResolutionsMap resolutions;
  wchar_t* resolution_str_end;
  size_t resolution_index;

  MallocIniStringW(
      keys,
      path,
      CONFIG_INGAME_RESOLUTIONS_SECTION,
      NULL
  );

  /*
   * Read each value associated with keys and convert to resolutions.
   * Key-value should be in the format: `Resolution 0.Width = 1068`.
   *
   * Keys do not need to be consecutive, and will simply choose the
   * next highest value. The starting index is 0.
   */

  key_start_index = 0;
  key_length = wcslen(&keys[0]);

  while (key_length > 0) {
    /* Key prefix is "Resolution " */
    if (wcsncmp(
            &keys[key_start_index],
            L"Resolution ",
            kResolutionStrLength
        ) != 0) {
      ExitOnInvalidConfigKey(
          CONFIG_INGAME_RESOLUTIONS_SECTION,
          &keys[key_start_index],
          __FILEW__,
          __LINE__
      );

      return;
    }

    resolution_index = wcstoul(
        &keys[key_start_index + kResolutionStrLength],
        &resolution_str_end,
        10
    );

    if (wcscmp(resolution_str_end, L".Width") == 0) {
      resolutions[resolution_index].width = GetPrivateProfileIntW(
          CONFIG_INGAME_RESOLUTIONS_SECTION,
          &keys[key_start_index],
          0,
          path
      );
    } else if (wcscmp(resolution_str_end, L".Height") == 0) {
      resolutions[resolution_index].height = GetPrivateProfileIntW(
          CONFIG_INGAME_RESOLUTIONS_SECTION,
          &keys[key_start_index],
          0,
          path
      );
    } else {
      ExitOnInvalidConfigKey(
          CONFIG_INGAME_RESOLUTIONS_SECTION,
          &keys[key_start_index],
          __FILEW__,
          __LINE__
      );

      return;
    }

    key_start_index += key_length + 1;
    key_length = wcslen(&keys[key_start_index]);
  }

  for (ResolutionsMap::const_iterator it = resolutions.begin();
      it != resolutions.end();
      ++it
  ) {
    const GameResolution& resolution = it->second;
    if (resolution.width <= 0 || resolution.height <= 0) {
      continue;
    }

    config.impl->ingame_resolutions.push_back(it->second);
  }

  config.ingame_resolutions.count = config.impl->ingame_resolutions.size();
  config.ingame_resolutions.resolutions = config.impl->ingame_resolutions.data();
}

static void ReadIsEnableScreenBorderFrame(
    struct Config& config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config.is_enable_screen_border_frame = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME),
      2,
      path
  );

  if (config.is_enable_screen_border_frame == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME),
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadIsUseOriginalScreenBorderFrame(
    struct Config& config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config.is_use_original_screen_border_frame = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME),
      0,
      path
  );

  if (config.is_use_original_screen_border_frame == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME),
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadIsUse800InterfaceBar(
    struct Config& config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config.is_use_800_interface_bar = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_USE_800_INTERFACE_BAR),
      0,
      path
  );

  if (config.is_use_800_interface_bar == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME),
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadMainMenuResolution(
    struct Config& config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config.main_menu_resolution.width = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Width",
      CONFIG_MAIN_MENU_RESOLUTION_WIDTH_DEFAULT,
      path
  );

  if (config.main_menu_resolution.width == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Width",
        __FILEW__,
        __LINE__
    );
  }

  config.main_menu_resolution.height = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Height",
      CONFIG_MAIN_MENU_RESOLUTION_HEIGHT_DEFAULT,
      path
  );

  if (config.main_menu_resolution.height == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Height",
        __FILEW__,
        __LINE__
    );
  }
}

/**
 * External
 */

void ConfigIni_Read(Config* config, const wchar_t* path) {
  config->impl = new Config_Implmentation();

  ReadMetadata(*config, path);
  ReadCustomMpqPath(*config, path);
  ReadIngameResolutionMode(*config, path);
  ReadIngameResolutions(*config, path);
  ReadIsEnableScreenBorderFrame(*config, path);
  ReadIsUse800InterfaceBar(*config, path);
  ReadIsUseOriginalScreenBorderFrame(*config, path);
  ReadMainMenuResolution(*config, path);
}