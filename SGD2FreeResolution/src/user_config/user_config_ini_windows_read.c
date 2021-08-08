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

#include "user_config_ini_windows.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <windows.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/wchar_t/filew.h>
#include "user_config_key_value.h"
#include "user_config_struct.h"
#include "user_config_value_default.h"

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
  kInt32StrCapacity = 10 + 1,
};

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
    wchar_t** buffer,
    size_t* buffer_capacity,
    const wchar_t* path,
    const wchar_t* section,
    const wchar_t* key
) {
  enum {
    kInitialCapacity = 512,
  };

  DWORD get_private_profile_string_result;

  if (*buffer_capacity < kInitialCapacity) {
    Mdc_free(*buffer);
    *buffer = Mdc_malloc(kInitialCapacity * sizeof(*buffer[0]));
    if (*buffer == NULL) {
      Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
      goto return_bad;
    }

    *buffer_capacity = kInitialCapacity;
  }

  /* Read the config string. */
  while (1) {
    get_private_profile_string_result = GetPrivateProfileStringW(
        section,
        key,
        INI_DEFAULT_STR,
        *buffer,
        *buffer_capacity,
        path
    );

    if (get_private_profile_string_result < (*buffer_capacity - 2)) {
      break;
    }

    Mdc_free(*buffer);
    *buffer = Mdc_malloc((*buffer_capacity * 2) * sizeof(*buffer[0]));
    if (*buffer == NULL) {
      Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
      goto return_bad;
    }

    *buffer_capacity *= 2;
  }

  return;

return_bad:
  return;
}

static void ReadMetadataVersion(
    struct UserConfig* config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MIN,
  };

  config->metadata.version.major_high = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_HIGH),
      kDefaultInvalidValue,
      path
  );

  if (config->metadata.version.major_high == 42) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_HIGH),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  config->metadata.version.major_low = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_LOW),
      kDefaultInvalidValue,
      path
  );

  if (config->metadata.version.major_low == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MAJOR_LOW),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  config->metadata.version.minor_high = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MINOR_HIGH),
      kDefaultInvalidValue,
      path
  );

  if (config->metadata.version.minor_high == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MINOR_HIGH),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  config->metadata.version.minor_low = GetPrivateProfileIntW(
      CONFIG_METADATA_VERSION_SECTION,
      TO_WIDE(CONFIG_METADATA_VERSION_MINOR_LOW),
      kDefaultInvalidValue,
      path
  );

  if (config->metadata.version.minor_low == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_METADATA_VERSION_SECTION,
        TO_WIDE(CONFIG_METADATA_VERSION_MINOR_LOW),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

return_bad:
  return;
}

static void ReadMetadata(
    struct UserConfig* config,
    const wchar_t* path
) {
  ReadMetadataVersion(config, path);
}

static void ReadCustomMpqPath(
    struct UserConfig* config,
    const wchar_t* path
) {
  wchar_t* custom_mpq_path;
  size_t custom_mpq_path_capacity;

  custom_mpq_path = NULL;
  custom_mpq_path_capacity = 0;
  MallocIniStringW(
      &custom_mpq_path,
      &custom_mpq_path_capacity,
      path,
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_CUSTOM_MPQ_PATH)
  );

  config->custom_mpq_path = custom_mpq_path;

  if (wcscmp(config->custom_mpq_path, INI_DEFAULT_STR) == 0) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_CUSTOM_MPQ_PATH),
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadIngameResolutionMode(
    struct UserConfig* config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MIN,
  };

  config->ingame_resolution_mode = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_INGAME_RESOLUTION_MODE),
      kDefaultInvalidValue,
      path
  );

  if (config->ingame_resolution_mode == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_INGAME_RESOLUTION_MODE),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

return_bad:
  return;
}

static void ReadIngameResolution(
    struct GameResolution* resolution,
    const struct GameResolution* default_resolution,
    size_t resolution_index,
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

  wchar_t width_key[kWidthKeyCapacity];
  wchar_t height_key[kHeightKeyCapacity];

  _snwprintf(
      width_key,
      kWidthKeyCapacity,
      L"Resolution %u.Width",
      resolution_index
  );
  width_key[kWidthKeyCapacity - 1] = L'\0';

  _snwprintf(
      height_key,
      kHeightKeyCapacity,
      L"Resolution %u.Height",
      resolution_index
  );
  height_key[kHeightKeyCapacity - 1] = L'\0';

  resolution->width = GetPrivateProfileIntW(
      CONFIG_INGAME_RESOLUTIONS_SECTION,
      width_key,
      default_resolution->width,
      path
  );

  resolution->height = GetPrivateProfileIntW(
      CONFIG_INGAME_RESOLUTIONS_SECTION,
      height_key,
      default_resolution->height,
      path
  );
}

static void ReadIngameResolutions(
    struct UserConfig* config,
    const wchar_t* path
) {
  static const struct GameResolution kDefaultResolution = { 0, 0 };

  size_t i;

  struct GameResolution resolution;

  /*
   * Determine the number of resolutions in the config.
   */
  i = 0;
  do {
    ReadIngameResolution(&resolution, &kDefaultResolution, i, path);
    i += 1;
  } while (resolution.width != kDefaultResolution.width
        && resolution.height != kDefaultResolution.height);

  config->ingame_resolutions.count = i - 1;

  if (config->ingame_resolutions.count == 0) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        CONFIG_INGAME_RESOLUTIONS_SECTION,
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  config->ingame_resolutions.resolutions = Mdc_malloc(
      config->ingame_resolutions.count
          * sizeof(config->ingame_resolutions.resolutions[0])
  );

  if (config->ingame_resolutions.resolutions == NULL) {
    Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
    goto return_bad;
  }

  /* Read the resolution from the config. */
  for (i = 0; i < config->ingame_resolutions.count; i += 1) {
    ReadIngameResolution(
        &config->ingame_resolutions.resolutions[i],
        &kDefaultResolution,
        i,
        path
    );
  }

  return;

return_bad:
  return;
}

static void ReadIsEnableScreenBorderFrame(
    struct UserConfig* config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config->is_enable_screen_border_frame = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME),
      kDefaultInvalidValue,
      path
  );

  if (config->is_enable_screen_border_frame == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

return_bad:
  return;
}

static void ReadIsUseOriginalScreenBorderFrame(
    struct UserConfig* config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config->is_use_original_screen_border_frame = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME),
      kDefaultInvalidValue,
      path
  );

  if (config->is_use_original_screen_border_frame == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

return_bad:
  return;
}

static void ReadIsUse800InterfaceBar(
    struct UserConfig* config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config->is_use_800_interface_bar = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_IS_USE_800_INTERFACE_BAR),
      kDefaultInvalidValue,
      path
  );

  if (config->is_use_800_interface_bar == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME),
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

return_bad:
  return;
}

static void ReadMainMenuResolution(
    struct UserConfig* config,
    const wchar_t* path
) {
  enum {
    kDefaultInvalidValue = INT_MAX,
  };

  config->main_menu_resolution.width = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Width",
      kDefaultInvalidValue,
      path
  );

  if (config->main_menu_resolution.width == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Width",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  config->main_menu_resolution.height = GetPrivateProfileIntW(
      CONFIG_MAIN_SECTION,
      TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Height",
      kDefaultInvalidValue,
      path
  );

  if (config->main_menu_resolution.height == kDefaultInvalidValue) {
    ExitOnInvalidConfigValue(
        CONFIG_MAIN_SECTION,
        TO_WIDE(CONFIG_MAIN_MENU_RESOLUTION) L".Height",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

return_bad:
  return;
}

/**
 * External
 */

void ConfigIniWindows_Read(struct UserConfig* config, const wchar_t* path) {
  ReadMetadata(config, path);
  ReadCustomMpqPath(config, path);
  ReadIngameResolutionMode(config, path);
  ReadIngameResolutions(config, path);
  ReadIsEnableScreenBorderFrame(config, path);
  ReadIsUse800InterfaceBar(config, path);
  ReadIsUseOriginalScreenBorderFrame(config, path);
  ReadMainMenuResolution(config, path);
}

void ConfigIniWindows_CleanUp(struct UserConfig* config) {
  Mdc_free(config->ingame_resolutions.resolutions);
  Mdc_free(config->custom_mpq_path);
}
