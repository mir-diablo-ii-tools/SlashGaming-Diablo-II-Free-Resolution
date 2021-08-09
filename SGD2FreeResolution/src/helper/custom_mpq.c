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

#include "custom_mpq.h"

#include <stddef.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/malloc/malloc.h>
#include <mdc/wchar_t/filew.h>
#include <mdc/wchar_t/wide_encoding.h>
#include <sgd2mapi.h>
#include "../user_config.h"

static int is_mpq_loaded = 0;
static struct D2_MpqArchiveHandle* mpq_archive_handle = NULL;

void CustomMpq_LoadMpqOnce(void) {
  char* custom_mpq_path_mb;
  size_t custom_mpq_path_mb_length;

  if (is_mpq_loaded) {
    return;
  }

  custom_mpq_path_mb_length = Mdc_Wide_EncodeDefaultMultibyteLength(
      UserConfig_Get()->custom_mpq_path
  );

  custom_mpq_path_mb = Mdc_malloc(
      (custom_mpq_path_mb_length + 1) * sizeof(custom_mpq_path_mb[0])
  );

  if (custom_mpq_path_mb == NULL) {
    Mdc_Error_ExitOnMemoryAllocError(__FILEW__, __LINE__);
    goto return_bad;
  }

  Mdc_Wide_EncodeDefaultMultibyte(
      custom_mpq_path_mb,
      UserConfig_Get()->custom_mpq_path
  );

  mpq_archive_handle = D2_D2Win_LoadMpq(custom_mpq_path_mb, 0, NULL, 5000);
  is_mpq_loaded = 1;

  return;

return_bad:
  return;
}

void CustomMpq_UnloadMpqOnce(void) {
  if (!is_mpq_loaded) {
    return;
  }

  D2_D2Win_UnloadMpq(mpq_archive_handle);
  is_mpq_loaded = 0;
}
