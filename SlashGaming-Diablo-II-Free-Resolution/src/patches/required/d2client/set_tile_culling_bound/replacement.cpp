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

#include "replacement.hpp"

#include <windows.h>

#include <mdc/std/stdint.h>

#include "../../../../sgd2mapi_extension/game_variable/d2gfx/is_perspective_mode_enabled.hpp"

namespace sgd2fr::patches {
namespace {

using ::d2::d2gfx::GetIsPerspectiveModeEnabled;
using ::d2::d2client::GetGeneralDisplayHeight;
using ::d2::d2client::GetGeneralDisplayWidth;

}  // namespace

struct CullingSpec {
  uint32_t flags;
  RECT draw_window_rect;
  RECT tile_culling_window;
};

static_assert(offsetof(CullingSpec, flags) == 0);
static_assert(offsetof(CullingSpec, draw_window_rect) == 4);
static_assert(offsetof(CullingSpec, tile_culling_window) == 20);

void __cdecl Sgd2fr_D2Client_SetTileCullingBound(
    CullingSpec* culling_spec, int left, int top, int right, int bottom) {
  if (culling_spec == NULL) {
    return;
  }

  SetRect(&culling_spec->draw_window_rect, left, top, right, bottom);

  RECT* tile_culling_rect = &culling_spec->tile_culling_window;
  int width = GetGeneralDisplayWidth();
  int height = GetGeneralDisplayHeight();
  SetRect(
      tile_culling_rect,
      -80,
      -80,
      width + 80,
      height + 40);
  if (GetIsPerspectiveModeEnabled()) {
    // Perspective mode works by multiplying an objects distance from the center
    // of the camera by a factor of it's distance along the camera's y-axis
    // (vertical along the screen).
    //
    // Equation for the factor is approximately `3000 / (3000 - 42y/3)` where `y`
    // is the distance in unit space with positive numbers heading towards the
    // bottom of the screen. Two things to note:
    // * This function is done with a precalculated table with rounding errors.
    // * The table is filled for the range (-204.375, 204.375). It is, however
    //   padded with the final value for double that range.
    //
    // This results in everything above the player rendering closer to the center
    // of the screen, and everything below the player rendering further away from
    // the center. To account for this we calculate approximately how much this
    // affects the top line of pixels rendered in order to avoid culling things on
    // the screen. As an optimization we also calculate this for the bottom row of
    // pixels in order to cull things which can no longer appear on the screen.

    int height2 = static_cast<double>(height) / 2;
    int width2 = static_cast<double>(width) / 2;
    double ratio;

    // `866` pixels up is equal to `-204.375` in unit space.
    if (height2 < 866.0) {
      // This slightly overshoots the games calculation, but converges at
      // `866`. After which it would start undershooting.
      ratio = 1732.0 / (1732.0 - height2) - 1.0;
    } else {
      ratio = 1.0;
    }

    tile_culling_rect->top -= static_cast<int>(height2 * ratio);
    tile_culling_rect->left -= static_cast<int>(width2 * ratio);
    tile_culling_rect->right += static_cast<int>(width2 * ratio);

    // This is close at any reasonable resolution, but wildly undershoots at
    // high resolutions. It also overshoots starting at 4.5 million height.
    ratio = 1.0 - 1500.0 / (1500.0 + height2);

    tile_culling_rect->bottom -= static_cast<int>(height2 * ratio);
  }

  culling_spec->flags |= 0x1;
}

}  // namespace sgd2fr::patches
