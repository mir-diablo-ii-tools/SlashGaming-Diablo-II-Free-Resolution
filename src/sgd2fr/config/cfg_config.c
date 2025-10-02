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

#include "sgd2fr/config/cfg_config.h"

#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <wchar.h>
#include <windows.h>

#include <cJSON.h>

#include "sgd2fr/config/cfg_entries.h"

static FILE* CfgConfig_wfopen_r(const wchar_t* path) {
  HANDLE file;
  int osfhandle;
  FILE* c_file;

  file = CreateFileW(
      path,
      GENERIC_READ,
      FILE_SHARE_READ,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
  if (file == INVALID_HANDLE_VALUE) {
    goto error;
  }

  osfhandle = _open_osfhandle(file, _O_RDONLY | _O_TEXT);
  if (osfhandle == -1) {
    CloseHandle(file);
    goto error;
  }

  c_file = _wfdopen(osfhandle, L"r");
  if (c_file == NULL) {
    _close(osfhandle);
    goto error;
  }

  return c_file;

error:
  return NULL;
}

static FILE* CfgConfig_wfopen_w(const wchar_t* path) {
  HANDLE file;
  int osfhandle;
  FILE* c_file;

  file = CreateFileW(
      path,
      GENERIC_WRITE,
      0,
      NULL,
      OPEN_ALWAYS,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
  if (file == INVALID_HANDLE_VALUE) {
    goto error;
  }

  osfhandle = _open_osfhandle(file, _O_WRONLY | _O_TEXT);
  if (osfhandle == -1) {
    CloseHandle(file);
    goto error;
  }

  c_file = _wfdopen(osfhandle, L"w");
  if (c_file == NULL) {
    _close(osfhandle);
    goto error;
  }

  return c_file;

error:
  return NULL;
}

static void* AllocForFile(FILE* file, size_t* file_size) {
  int fseek_failed;
  long old_pos;
  long file_size_as_long;
  char* buffer;

  old_pos = ftell(file);
  if (old_pos == -1L) {
    goto error;
  }

  fseek_failed = fseek(file, 0, SEEK_END);
  if (fseek_failed) {
    goto error;
  }

  file_size_as_long = ftell(file);
  if (file_size_as_long == -1L) {
    goto error;
  }

  fseek_failed = fseek(file, old_pos, SEEK_SET);
  if (fseek_failed) {
    goto error;
  }

  buffer = malloc(file_size_as_long);
  if (buffer == NULL) {
    goto error;
  }

  if (file_size != NULL) {
    *file_size = file_size_as_long;
  }

  return buffer;

error:
  return NULL;
}

/**
 * External
 */

struct CfgConfig* CfgConfig_InitDefault(struct CfgConfig* config) {
  void* result;

  result = CfgEntries_InitDefault(&config->entries);
  if (result == NULL) {
    goto error;
  }

  return config;

error:
  return NULL;
}

void CfgConfig_Deinit(struct CfgConfig* config) {
  CfgEntries_Deinit(&config->entries);
}

int CfgConfig_Equals(const struct CfgConfig* lhs, const struct CfgConfig* rhs) {
  return CfgEntries_Equals(&lhs->entries, &rhs->entries);
}

struct CfgConfig* CfgConfig_Read(
    struct CfgConfig* config, const wchar_t* path) {
  void* from_json_result;

  FILE* file;
  size_t file_size;
  char* buffer;
  cJSON* json_entries;

  file = CfgConfig_wfopen_r(path);
  if (file == NULL) {
    goto error;
  }

  buffer = AllocForFile(file, &file_size);
  if (buffer == NULL) {
    goto error_close_file;
  }

  fread(buffer, sizeof(buffer[0]), file_size + 1, file);
  if (!feof(file)) {
    goto error_free_buffer;
  }

  json_entries = cJSON_Parse(buffer);
  from_json_result = CfgEntries_FromV1Json(&config->entries, json_entries);
  if (from_json_result == NULL) {
    from_json_result = CfgEntries_FromV2Json(&config->entries, json_entries);
    if (from_json_result == NULL) {
      goto error_delete_json_entries;
    }
  }

  /* Clean up allocations. */
  cJSON_Delete(json_entries);
  free(buffer);
  fclose(file);

  CfgConfigVersion_UpgradeToCurrent(&config->entries.metadata.version);

  return config;

error_delete_json_entries:
  cJSON_Delete(json_entries);

error_free_buffer:
  free(buffer);

error_close_file:
  fclose(file);

error:
  return NULL;
}

int CfgConfig_Write(const struct CfgConfig* config, const wchar_t* path) {
  void* add_result;

  cJSON* object;
  char* buffer;
  FILE* file;

  object = cJSON_CreateObject();
  if (object == NULL) {
    goto error;
  }

  add_result = CfgEntries_AddToJson(&config->entries, object);
  if (add_result == NULL) {
    goto error_delete_object;
  }

  buffer = cJSON_PrintBuffered(object, 2048, 1);

  file = CfgConfig_wfopen_w(path);
  if (file == NULL) {
    goto error_free_buffer;
  }

  fwrite(buffer, sizeof(buffer[0]), strlen(buffer), file);

  fclose(file);
  free(buffer);
  cJSON_Delete(object);

  return 1;

error_free_buffer:
  free(buffer);

error_delete_object:
  cJSON_Delete(object);

error:
  return 0;
}
