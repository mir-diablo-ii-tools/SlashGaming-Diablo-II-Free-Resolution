/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2022  Mir Drualga
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

#include "d2client_set_tile_culling_bound.hpp"

#include <windows.h>

#include <mdc/std/stdint.h>

#include "../../../sgd2mapi_extension/game_variable/d2gfx/is_perspective_mode_enabled.hpp"

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
  SetRect(
      tile_culling_rect,
      -80,
      -80,
      GetGeneralDisplayWidth() + 80,
      GetGeneralDisplayHeight() + 80);
  if (GetIsPerspectiveModeEnabled()) {
    tile_culling_rect->top -= 160;
    tile_culling_rect->left -= 320;
    tile_culling_rect->right += 320;
  }

  culling_spec->flags |= 0x1;
}

}  // namespace sgd2fr::patches
