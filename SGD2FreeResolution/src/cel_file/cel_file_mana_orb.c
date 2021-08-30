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

#include "cel_file_mana_orb.h"

#include <stddef.h>

#include "../helper/custom_mpq.h"
#include "../cel_file_config.h"

static struct D2_CelFile* mana_orb_interface = NULL;
static struct D2_CelFile* mana_orb_blue = NULL;

static void InitManaOrbInterface(void) {
  if (mana_orb_interface != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  mana_orb_interface = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->mana_orb_interface.path,
      0
  );
}

static void InitManaOrbBlue(void) {
  if (mana_orb_blue != NULL) {
    return;
  }

  CustomMpq_LoadMpqOnce();

  mana_orb_blue = D2_D2Win_LoadCelFile(
      CelFileConfig_Get()->mana_orb_blue.path,
      0
  );
}

/**
 * External
 */

struct D2_CelFile* CelFile_ManaOrb_GetInterface(void) {
  InitManaOrbInterface();

  return mana_orb_interface;
}

void CelFile_ManaOrb_UnloadInterface(void) {
  if (mana_orb_interface == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(mana_orb_interface);
  mana_orb_interface = NULL;
}

struct D2_CelFile* CelFile_ManaOrb_GetBlue(void) {
  InitManaOrbBlue();

  return mana_orb_blue;
}

void CelFile_ManaOrb_UnloadBlue(void) {
  if (mana_orb_blue == NULL) {
    return;
  }

  D2_D2Win_UnloadCelFile(mana_orb_blue);
  mana_orb_blue = NULL;
}
