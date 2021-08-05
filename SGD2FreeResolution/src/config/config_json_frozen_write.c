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

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/wchar_t/filew.h>
#include <mdc/wchar_t/wide_encoding.h>
#include "../../third_party/frozen/frozen.h"
#include "config_key_value.h"

#define TO_STR_IMPL(lit) #lit
#define TO_STR(lit) TO_STR_IMPL(lit)

static int WriteMetadataVersion(struct json_out *out, va_list *ap) {
  const struct Config_Metadata_Version* version;
  int bytes_printed;

  version = va_arg(*ap, const struct Config_Metadata_Version*);

  bytes_printed = json_printf(
      out,
      "{"
          "%Q: %u,"
          "%Q: %u,"
          "%Q: %u,"
          "%Q: %u"
      "}",
      CONFIG_METADATA_VERSION_MINOR_HIGH,
      version->major_high,
      CONFIG_METADATA_VERSION_MAJOR_LOW,
      version->major_low,
      CONFIG_METADATA_VERSION_MINOR_HIGH,
      version->minor_high,
      CONFIG_METADATA_VERSION_MINOR_LOW,
      version->minor_low
  );

  return bytes_printed;
}

static int WriteMetadata(struct json_out *out, va_list *ap) {
  const struct Config_Metadata* metadata;
  int bytes_printed;

  metadata = va_arg(*ap, const struct Config_Metadata*);

  bytes_printed = 0;
  bytes_printed += json_printf(
      out,
      "{ %Q: %M }",
      CONFIG_METADATA_VERSION,
      &WriteMetadataVersion,
      &metadata->version
  );

  return bytes_printed;
}

static int WriteCustomMpqPath(struct json_out *out, va_list *ap) {
  const wchar_t* custom_mpq_path;
  int bytes_printed;

  size_t custom_mpq_path_utf8_length;
  char* custom_mpq_path_utf8;

  custom_mpq_path = va_arg(*ap, const wchar_t*);

  /* Convert custom MPQ path to null-terminated UTF-8 string. */
  custom_mpq_path_utf8_length = Mdc_Wide_EncodeUtf8Length(custom_mpq_path);
  custom_mpq_path_utf8 = Mdc_malloc(
      (custom_mpq_path_utf8_length + 1) * sizeof(custom_mpq_path_utf8[0])
  );

  if (custom_mpq_path_utf8 == NULL) {
    Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
    goto return_bad;
  }

  Mdc_Wide_EncodeUtf8(custom_mpq_path_utf8, custom_mpq_path);

  /* Output string to file. */
  bytes_printed = json_printf(
      out,
      "%Q",
      custom_mpq_path_utf8
  );

  Mdc_free(custom_mpq_path_utf8);

  return bytes_printed;

return_bad:
  return 0;
}

static int WriteResolution(struct json_out *out, va_list *ap) {
  const struct GameResolution* resolution;
  int bytes_printed;

  resolution = va_arg(*ap, const struct GameResolution*);

  bytes_printed = 0;
  bytes_printed += json_printf(
      out,
      "{ Width: %d, Height: %d }",
      resolution->width,
      resolution->height
  );

  return bytes_printed;
}

static int WriteIngameResolutions(struct json_out *out, va_list *ap) {
  size_t i;

  const struct Config* config;
  int bytes_printed;

  config = va_arg(*ap, const struct Config*);

  bytes_printed = 0;
  bytes_printed += json_printf(out, "[", 1);

  bytes_printed += json_printf(
      out,
      "%M",
      &WriteResolution,
      &config->ingame_resolutions.resolutions[0]
  );

  for (i = 1; i < config->ingame_resolutions.count; i += 1) {
    bytes_printed += json_printf(
        out,
        ", %M",
        &WriteResolution,
        &config->ingame_resolutions.resolutions[i]
    );
  }
  bytes_printed += json_printf(out, "]", 1);

  return bytes_printed;
}

static int WriteConfig(struct json_out *out, va_list *ap) {
  const struct Config* config;
  int bytes_printed;

  config = va_arg(*ap, const struct Config*);

  bytes_printed = 0;
  bytes_printed += json_printf(
      out,
      "{"
          "%Q: %M,"
          "%Q: %M,"
          "%Q: %u,"
          "%Q: %M,"
          "%Q: %B,"
          "%Q: %B,"
          "%Q: %B,"
          "%Q: %M"
      "}",
      CONFIG_METADATA,
      &WriteMetadataVersion,
      &config->metadata,
      CONFIG_CUSTOM_MPQ_PATH,
      &WriteCustomMpqPath,
      config->custom_mpq_path,
      CONFIG_INGAME_RESOLUTION_MODE,
      config->ingame_resolution_mode,
      CONFIG_INGAME_RESOLUTIONS,
      &WriteIngameResolutions,
      config,
      CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME,
      config->is_enable_screen_border_frame,
      CONFIG_IS_USE_800_INTERFACE_BAR,
      config->is_use_800_interface_bar,
      CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME,
      config->is_use_original_screen_border_frame,
      CONFIG_MAIN_MENU_RESOLUTION,
      &WriteResolution,
      &config->main_menu_resolution
  );

  return bytes_printed;
}

static void WritePrettifyFile(const wchar_t* path, const char* str) {
  int fclose_result;

  FILE* file = _wfopen(path, L"w");
  struct json_out out = JSON_OUT_FILE(file);

  json_prettify(str, strlen(str), &out);

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

return_bad:
  return;
}

static void PrettifyFile(const wchar_t* path) {
  size_t file_length;
  char* file_contents;

  file_length = Mapi_File_GetFileContentLength(path);
  file_contents = Mdc_malloc(file_length * sizeof(file_contents[0]));
  if (file_contents == NULL) {
    Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
    goto return_bad;
  }

  WritePrettifyFile(path, file_contents);

  Mdc_free(file_contents);

  return;

return_bad:
  return;
}

/**
 * External
 */

void ConfigJsonFrozen_Write(
    const struct Config* config,
    const wchar_t* path
) {
  int fclose_result;

  /*
   * In order to initialize the json_out with JSON_OUT_FILE,
   * initialization needs to be done during declaration.
   */

  FILE* file = _wfopen(path, L"w");
  struct json_out out = JSON_OUT_FILE(file);

  if (file == NULL) {
    Mdc_Error_ExitOnGeneralError(
        L"Error",
        L"_wfopen failed.",
        __FILEW__,
        __LINE__
    );

    goto return_bad;
  }

  json_printf(&out, "{ %Q: %M }", CONFIG_MAIN, &WriteConfig, config);

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

  PrettifyFile(path);

  return;

return_bad:
  return;
}
