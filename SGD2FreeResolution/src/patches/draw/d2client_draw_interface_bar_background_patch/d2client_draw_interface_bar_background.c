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

#include "d2client_draw_interface_bar_background.h"

#include <stddef.h>

#include <sgd2mapi.h>
#include "../../../cel_file/cel_file_interface_bar_background.h"
#include "../../../game_resolution/game_resolution.h"
#include "../../../game_resolution/game_resolution_global.h"

static void DrawAntiCheatBlackRectangle(
    const struct GameResolution* resolution
) {
  size_t i;

  struct D2_CelFile* background_left_center;
  unsigned int num_rows;
  int rect_height;

  background_left_center = CelFile_InterfaceBarBackground_GetLeftCenter();
  num_rows = D2_CelFile_GetNumDirections(background_left_center);
  rect_height = 0;

  for (i = 0; i < num_rows; i += 1) {
    struct D2_CelContext_Api cel_context;
    struct D2_Cel* cel;

    cel_context = D2_CelContext_Api_Init(background_left_center, i, 0);
    cel = D2_D2CMP_GetCelFromCelContext(D2_CelContext_Api_Get(&cel_context));

    rect_height += D2_Cel_GetHeight(cel);

    D2_CelContext_Api_Deinit(&cel_context);
  }

  D2_D2GFX_DrawRectangle(
      0,
      resolution->height - rect_height,
      resolution->width,
      resolution->height,
      0,
      D2_DrawEffect_kNone
  );
}

static void DrawLeftInterfaceBarBackground(
    const struct GameResolution* resolution
) {
  enum {
    /* TODO (Mir Drualga): Remove this hardcoding. */
    kLeft = 117 + 48,
  };

  size_t row;
  size_t column;

  unsigned int num_columns;
  unsigned int num_rows;

  int width_covered;
  int height_covered;

  struct D2_CelFile* background_left;

  struct D2_CelFile* background_center;

  /* Draw the left part of the interface bar background. */
  background_left = CelFile_InterfaceBarBackground_GetLeft();
  num_columns = D2_CelFile_GetNumFrames(background_left);
  num_rows = D2_CelFile_GetNumDirections(background_left);

  height_covered = 0;

  for (row = num_rows; row > 0; row -= 1) {
    size_t actual_row;
    struct D2_Cel* cel;

    actual_row = row - 1;
    width_covered = 0;

    for (column = 0; column < num_columns; column += 1) {
      struct D2_CelContext_Api cel_context;

      cel_context = D2_CelContext_Api_Init(
          background_left,
          actual_row,
          column
      );

      D2_D2GFX_DrawCelContext(
          D2_CelContext_Api_Get(&cel_context),
          kLeft + width_covered,
          resolution->height - height_covered - 1,
          0xFFFFFFFF,
          D2_DrawEffect_kNone,
          NULL
      );

      cel = D2_D2CMP_GetCelFromCelContext(
          D2_CelContext_Api_Get(&cel_context)
      );

      width_covered += D2_Cel_GetWidth(cel);

      D2_CelContext_Api_Deinit(&cel_context);
    }

    height_covered += D2_Cel_GetHeight(cel);
  }

  /* Draw the center part of the interface bar background. */
  background_center = CelFile_InterfaceBarBackground_GetLeftCenter();
  num_columns = D2_CelFile_GetNumFrames(background_center);
  num_rows = D2_CelFile_GetNumDirections(background_center);

  height_covered = 0;

  for (row = num_rows; row > 0; row -= 1) {
    size_t actual_row;
    struct D2_Cel* cel;

    actual_row = row - 1;
    width_covered = 0;

    for (column = 0; column < num_columns; column += 1) {
      struct D2_CelContext_Api cel_context;

      cel_context = D2_CelContext_Api_Init(
          background_center,
          actual_row,
          column
      );

      D2_D2GFX_DrawCelContext(
          D2_CelContext_Api_Get(&cel_context),
          kLeft + width_covered,
          resolution->height - height_covered - 1,
          0xFFFFFFFF,
          D2_DrawEffect_kNone,
          NULL
      );

      cel = D2_D2CMP_GetCelFromCelContext(
          D2_CelContext_Api_Get(&cel_context)
      );

      width_covered += D2_Cel_GetWidth(cel);

      D2_CelContext_Api_Deinit(&cel_context);
    }

    height_covered += D2_Cel_GetHeight(cel);
  }
}

static void DrawRightInterfaceBarBackground(
    const struct GameResolution* resolution
) {
}

/**
 * External
 */

void __cdecl Sgd2fr_D2Client_DrawInterfaceBarBackground(void) {
  struct GameResolution resolution;

  Global_GetIngameResolution(&resolution, D2_D2GFX_GetResolutionMode());

  DrawAntiCheatBlackRectangle(&resolution);
  DrawLeftInterfaceBarBackground(&resolution);
  DrawRightInterfaceBarBackground(&resolution);
}
