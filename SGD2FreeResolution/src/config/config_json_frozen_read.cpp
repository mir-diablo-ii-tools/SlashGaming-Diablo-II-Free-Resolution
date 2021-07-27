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

#include "config_json_frozen.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

#include <mdc/error/exit_on_error.h>
#include <mdc/wchar_t/filew.h>
#include <mdc/wchar_t/wide_decoding.h>
#include "../../third_party/frozen/frozen.h"
#include "config_struct.hpp"

static void ExitOnInvalidConfig(
    const wchar_t* key_path,
    const wchar_t* file_path,
    int line
) {
  Mdc_Error_ExitOnGeneralError(
      L"Error",
      L"Invalid JSON config value for \"%ls\". The program will "
          L"now close.",
      file_path,
      line,
      key_path
  );
}

static void ReadMetadataVersion(const char *str, int len, void *user_data) {
  typedef Config::Config_Metadata::Config_Metadata_Version
      Config_Metadata_Version;
  Config_Metadata_Version* version;
  int json_scanf_result;

  version = (Config_Metadata_Version*) user_data;

  json_scanf_result = json_scanf(
      str,
      len,
      "{"
          CONFIG_METADATA_VERSION_MINOR_HIGH ": %u,"
          CONFIG_METADATA_VERSION_MAJOR_LOW ": %u,"
          CONFIG_METADATA_VERSION_MINOR_HIGH ": %u,"
          CONFIG_METADATA_VERSION_MINOR_LOW ": %u"
      "}",
      &version->major_high,
      &version->major_low,
      &version->minor_high,
      &version->minor_low
  );

  if (json_scanf_result < 4) {
    ExitOnInvalidConfig(
        CONFIG_MAIN L"." CONFIG_METADATA L"." CONFIG_METADATA_VERSION,
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadMetadata(const char *str, int len, void *user_data) {
  typedef Config::Config_Metadata Config_Metadata;
  Config_Metadata* metadata;
  int json_scanf_result;

  metadata = (Config_Metadata*) user_data;

  json_scanf_result = json_scanf(
      str,
      len,
      "{"
          CONFIG_METADATA_VERSION ": %M"
      "}",
      &ReadMetadataVersion,
      &metadata->version
  );

  if (json_scanf_result < 1) {
    ExitOnInvalidConfig(
        CONFIG_MAIN L"." CONFIG_METADATA,
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadCustomMpqPath(const char *str, int len, void *user_data) {
  struct Config* config;
  int json_scanf_result;
  const char* custom_mpq_path_utf8;

  size_t custom_mpq_path_length;

  config = (struct Config*) user_data;

  json_scanf_result = json_scanf(
      str,
      len,
      "{" CONFIG_CUSTOM_MPQ_PATH ": %Q }",
      &custom_mpq_path_utf8
  );

  if (json_scanf_result < 1) {
    ExitOnInvalidConfig(
        CONFIG_MAIN L"." CONFIG_CUSTOM_MPQ_PATH,
        __FILEW__,
        __LINE__
    );

    return;
  }

  custom_mpq_path_length = Mdc_Wide_DecodeUtf8Length(custom_mpq_path_utf8);
  config->impl->custom_mpq_path.resize(custom_mpq_path_length);
  Mdc_Wide_DecodeUtf8(
      &config->impl->custom_mpq_path[0],
      custom_mpq_path_utf8
  );

  free((void*) custom_mpq_path_utf8);

  config->custom_mpq_path = config->impl->custom_mpq_path.c_str();
}

static void ReadResolution(const char *str, int len, void *user_data) {
  struct GameResolution* resolution;
  int json_scanf_result;

  resolution = (struct GameResolution*) user_data;

  json_scanf_result = json_scanf(
      str,
      len,
      "{ Width: %d, Height: %d }",
      &resolution->width,
      &resolution->height
  );

  if (json_scanf_result < 2) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"Invalid JSON config resolution. The program will now close.",
        __FILEW__,
        __LINE__
    );
  }
}

static void ReadIngameResolutions(const char *str, int len, void *user_data) {
  size_t i;

  struct Config* config;
  struct json_token token;
  int json_scanf_result;

  config = (struct Config*) user_data;

  for (i = 0; json_scanf_array_elem(str, len, "", i, &token) > 0; i += 1) {
    config->impl->ingame_resolutions.push_back(GameResolution());

    json_scanf_result = json_scanf(
        token.ptr,
        token.len,
        "%M",
        &ReadResolution,
        &config->impl->ingame_resolutions[i]
    );

    if (json_scanf_result < 1) {
      Mdc_Error_ExitOnGeneralError(
          L"Error",
          L"Invalid JSON config value for \"%ls[%u]\". The program "
              L"will now close.",
          __FILEW__,
          __LINE__,
          CONFIG_MAIN L"." CONFIG_INGAME_RESOLUTIONS,
          i
      );

      return;
    }
  }

  config->ingame_resolutions = config->impl->ingame_resolutions.data();
  config->ingame_resolutions_count = config->impl->ingame_resolutions.size();
}

static void ReadConfig(const char *str, int len, void *user_data) {
  struct Config* config;
  int json_scanf_result;

  config = (struct Config*) user_data;

  json_scanf_result = json_scanf(
      str,
      len,
      "{"
          CONFIG_METADATA ": %M,"
          CONFIG_CUSTOM_MPQ_PATH ": %M,"
          CONFIG_INGAME_RESOLUTION_MODE ": %u,"
          CONFIG_INGAME_RESOLUTIONS ": %M,"
          CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME ": %B,"
          CONFIG_IS_USE_800_INTERFACE_BAR ": %B,"
          CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME ": %B,"
          CONFIG_MAIN_MENU_RESOLUTION ": %M"
      "}",
      &ReadMetadata,
      &config->metadata,
      &ReadCustomMpqPath,
      config,
      &config->ingame_resolution_mode,
      &ReadIngameResolutions,
      config,
      &config->is_enable_screen_border_frame,
      &config->is_use_800_interface_bar,
      &config->is_use_original_screen_border_frame,
      &ReadResolution,
      &config->main_menu_resolution
  );

  if (json_scanf_result < 8) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"Invalid JSON config. The program will now close.",
        __FILEW__,
        __LINE__
    );
  }
}

static void MallocFileContent(
    ::std::vector<char>& buffer,
    const wchar_t* path
) {
  enum {
    kReadCount = 256,
  };

  FILE* file;
  size_t required_size;

  char* fget_result;
  int ferror_result;
  int fclose_result;

  file = _wfopen(path, L"r");
  if (file == NULL) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"_wfopen failed.",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  required_size = kReadCount;
  while (feof(file) != EOF) {
    if (buffer.size() < required_size) {
      buffer.resize(required_size);
    }

    fget_result = fgets(buffer.data(), required_size, file);
    ferror_result = ferror(file);
    if (fget_result == NULL && ferror_result != 0) {
      Mdc_Error_ExitOnGeneralError(
          L"Error",
          L"fgets failed: %d.",
          __FILEW__,
          __LINE__,
          ferror_result
      );

      goto fclose_file;
    }

    required_size += kReadCount;
  }

  fclose_result = fclose(file);
  if (fclose_result == EOF) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"fclose failed.",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  return;

fclose_file:
  fclose(file);

return_bad:
  return;
}

/**
 * External
 */

void ConfigJsonFrozen_Read(struct Config* config, const wchar_t* path) {
  ::std::vector<char> buffer(256);
  size_t buffer_length;

  MallocFileContent(buffer, path);
  buffer_length = strlen(buffer.data());

  config->impl = new Config_Implmentation();

  json_scanf(
      buffer.data(),
      buffer_length,
      "{ \"" CONFIG_MAIN "\": %M }",
      &ReadConfig,
      config
  );
}
