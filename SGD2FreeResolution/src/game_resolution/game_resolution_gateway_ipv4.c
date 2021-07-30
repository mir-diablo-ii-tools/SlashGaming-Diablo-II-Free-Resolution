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

#include "game_resolution_gateway_ipv4.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "game_resolution.h"
#include "gateway/game_resolution_d2lod_net.h"
#include "gateway/game_resolution_diablo_09.h"
#include "gateway/game_resolution_project_diablo_2.h"
#include "gateway/game_resolution_resurgence.h"
#include "gateway/game_resolution_slash_diablo.h"

struct IngameResolutionsTableEntry {
  const char* key;
  struct IngameResolutions value;
};

static int IngameResolutionsTableEntry_Compare(
    const struct IngameResolutionsTableEntry* entry1,
    const struct IngameResolutionsTableEntry* entry2
) {
  return strcmp(entry1->key, entry2->key);
}

static int IngameResolutionsTableEntry_CompareAsVoid(
    const void* entry1,
    const void* entry2
) {
  return IngameResolutionsTableEntry_Compare(entry1, entry2);
}

static struct IngameResolutionsTableEntry kIngameResolutionsSortedTable[] = {
    {
        /* evnt.slashdiablo.net */
        "207.252.75.177",
        {
            Resurgence_kIngameResolutionsCount,
            Resurgence_kIngameResolutions
        }
    },
    {
        /* play.slashdiablo.net */
        "209.222.25.91",
        {
            SlashDiablo_kIngameResolutionsCount,
            SlashDiablo_kIngameResolutions
        }
    },
    {
        /* Project Diablo 2 */
        "35.225.107.249",
        {
            ProjectDiablo2_kIngameResolutionsCount,
            ProjectDiablo2_kIngameResolutions
        }
    },
    {
        /* ip.d2lod.net */
        "51.222.51.12",
        {
            D2LodNet_kIngameResolutionsCount,
            D2LodNet_kIngameResolutions
        }
    },
    {
        /* realm.diablo09.com */
        "95.179.228.126",
        {
            Diablo09_kIngameResolutionsCount,
            Diablo09_kIngameResolutions
        }
    },
};

enum {
  kIngameResolutionsSortedTableCount = sizeof(kIngameResolutionsSortedTable)
      / sizeof(kIngameResolutionsSortedTable[0]),
};

/**
 * External
 */

const struct IngameResolutions* GatewayIpv4_GetIngameResolutions(
    const char* gateway_ipv4
) {
  const struct IngameResolutionsTableEntry* search_result;

  /*
   * The gateway_ipv4 may be aliased to IngameResolutionsTableEntry,
   * because the compare function only accesses the key.
   */
  search_result = bsearch(
      gateway_ipv4,
      kIngameResolutionsSortedTable,
      kIngameResolutionsSortedTableCount,
      sizeof(kIngameResolutionsSortedTable[0]),
      &IngameResolutionsTableEntry_CompareAsVoid
  );

  if (search_result == NULL) {
    return &IngameResolution_kDefault;
  }

  return &search_result->value;
}
