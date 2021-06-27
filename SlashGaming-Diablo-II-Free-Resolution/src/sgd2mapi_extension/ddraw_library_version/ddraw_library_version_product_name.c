/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2021  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Modding API for C++. It
 * has been copied and retooled for reading glide3x.dll.
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

#include "ddraw_library_version_product_name.h"

#include <stdlib.h>
#include <windows.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/std/wchar.h>
#include <mdc/wchar_t/filew.h>
#include "../glide3x_library.h"

struct VersionTableEntry {
  const wchar_t* key;
  enum D2_DDrawLibraryVersion value;
};

static const struct VersionTableEntry kVersionSortedTable[] = {
  { L"cnc-ddraw", D2_DDrawLibraryVersion_kCnC },
};

enum {
  kVersionSortedTableCount = sizeof(kVersionSortedTable)
      / sizeof(kVersionSortedTable[0])
};

static int VersionTableEntry_CompareKey(
    const struct VersionTableEntry* entry1,
    const struct VersionTableEntry* entry2
) {
  return wcscmp(entry1->key, entry2->key);
}

static int VersionTableEntry_CompareKeyAsVoid(
    const void* entry1,
    const void* entry2
) {
  return VersionTableEntry_CompareKey(entry1, entry2);
}

static enum D2_DDrawLibraryVersion SearchVersionTable(
    const wchar_t* product_name
) {
  struct VersionTableEntry search_key = { product_name };
  const struct VersionTableEntry* search_result;

  search_result = bsearch(
      &search_key,
      kVersionSortedTable,
      kVersionSortedTableCount,
      sizeof(kVersionSortedTable[0]),
      &VersionTableEntry_CompareKeyAsVoid
  );

  /*
  * The product name is only useful enough to locate CnC-DDraw. This
  * does not necessarily confirm the library version to be the Windows
  * Default.
  */
  if (search_result == NULL) {
    return D2_DDrawLibraryVersion_kWindowsDefault;
  }

  return search_result->value;
}

/**
 * External
 */

enum D2_DDrawLibraryVersion GuessDDrawLibraryVersion(void) {
  enum D2_DDrawLibraryVersion ddraw_library_version;

  const wchar_t* product_name;

  product_name = D2_Glide3xLibrary_QueryFileVersionInfoString(
      L"\\StringFileInfo\\040904B0\\ProductName"
  );

  ddraw_library_version = SearchVersionTable(product_name);

  return ddraw_library_version;
}
