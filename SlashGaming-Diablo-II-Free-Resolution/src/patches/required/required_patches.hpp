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

#ifndef SGD2FR_PATCHES_REQUIRED_REQUIRED_PATCHES_HPP_
#define SGD2FR_PATCHES_REQUIRED_REQUIRED_PATCHES_HPP_

#include "d2client/disable_mouse_click_on_screen/patch.hpp"
#include "d2client/draw_resolution_text/patch.hpp"
#include "d2client/get_resolution_registry/patch.hpp"
#include "d2client/set_general_display_width_and_height/patch.hpp"
#include "d2client/set_resolution_from_options_menu/patch.hpp"
#include "d2client/set_resolution_registry/patch.hpp"
#include "d2client_set_screen_shift_patch/d2client_set_screen_shift_patch.hpp"
#include "d2client_set_tile_culling_bound_patch/d2client_set_tile_culling_bound_patch.hpp"
#include "d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch.hpp"
#include "d2ddraw/set_bit_block_width_and_height/patch.hpp"
#include "d2ddraw/set_cel_display_left_and_right/patch.hpp"
#include "d2ddraw/set_display_width_and_height/patch.hpp"
#include "d2direct3d/set_display_width_and_height/patch.hpp"
#include "d2gdi/set_bit_block_width_and_height/patch.hpp"
#include "d2gdi/set_cel_display_left_and_right/patch.hpp"
#include "d2gfx/is_need_resize_window/patch.hpp"
#include "d2gfx/is_need_restore_down_window/patch.hpp"
#include "d2gfx/set_display_width_and_height/patch.hpp"
#include "d2glide/set_display_width_and_height/patch.hpp"
#include "d2win/resize_window_on_maximize/patch.hpp"
#include "glide3x/gr_sst_win_open/patch.hpp"

namespace sgd2fr {

class RequiredPatches {
 public:
  void Apply();
  void Remove();

 private:
  d2client::DisableMouseClickOnScreenPatch
      d2client_disable_mouse_click_on_screen_patch_;

  d2client::DrawResolutionTextPatch
      d2client_draw_resolution_text_patch_;

  d2client::GetResolutionRegistryPatch
      d2client_get_resolution_registry_patch_;

  d2client::SetGeneralDisplayWidthAndHeightPatch
      d2client_set_general_display_width_and_height_patch_;

  d2client::SetResolutionFromOptionsMenuPatch
      d2client_set_resolution_from_options_menu_patch_;

  d2client::SetResolutionRegistryPatch
      d2client_set_resolution_registry_patch_;

  d2client::SetScreenShiftPatch
      d2client_set_screen_shift_patch_;

  d2client::SetTileCullingBoundPatch
      d2client_set_tile_culling_bound_patch_;

  d2client::UnloadCelFileCollectionPatch
      d2client_unload_cel_file_collection_patch_;

  d2ddraw::SetBitBlockWidthAndHeightPatch
      d2ddraw_set_bit_block_width_and_height_patch_;

  d2ddraw::SetCelDisplayLeftAndRightPatch
      d2ddraw_set_cel_display_left_and_right_patch_;

  d2ddraw::SetDisplayWidthAndHeightPatch
      d2ddraw_set_display_width_and_height_patch_;

  d2direct3d::SetDisplayWidthAndHeightPatch
      d2direct3d_set_display_width_and_height_patch_;

  d2gdi::SetBitBlockWidthAndHeightPatch
      d2gdi_set_bit_block_width_and_height_patch_;

  d2gdi::SetCelDisplayLeftAndRightPatch
      d2gdi_set_cel_display_left_and_right_patch_;

  d2gfx::IsNeedResizeWindowPatch
      d2gfx_is_need_resize_window_patch_;

  d2gfx::IsNeedRestoreDownWindowPatch
      d2gfx_is_need_restore_down_window_patch_;

  d2gfx::SetDisplayWidthAndHeightPatch
      d2gfx_set_display_width_and_height_patch_;

  d2glide::SetDisplayWidthAndHeightPatch
      d2glide_set_display_width_and_height_patch_;

  d2win::ResizeWindowOnMaximizePatch
      d2win_resize_window_on_maximize_patch_;

  glide3x::GrSstWinOpenPatch
      glide3x_gr_sst_win_open_patch_;
};

} // namespace sgd2fr

#endif // SGD2FR_PATCHES_REQUIRED_REQUIRED_PATCHES_HPP_
