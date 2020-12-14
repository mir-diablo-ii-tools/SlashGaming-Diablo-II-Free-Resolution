/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2020  Mir Drualga
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

#include "required_patches.hpp"

#include <algorithm>

#include "d2client_disable_mouse_click_on_screen_patch/d2client_disable_mouse_click_on_screen_patch.hpp"
#include "d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch.hpp"
#include "d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch.hpp"
#include "d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height_patch.hpp"
#include "d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch.hpp"
#include "d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch.hpp"
#include "d2client_set_screen_shift_patch/d2client_set_screen_shift_patch.hpp"
#include "d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch.hpp"
#include "d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch.hpp"
#include "d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right_patch.hpp"
#include "d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch.hpp"
#include "d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch.hpp"
#include "d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch.hpp"
#include "d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch.hpp"
#include "d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch.hpp"
#include "d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch.hpp"
#include "glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch.hpp"

namespace sgd2fr::patches {

std::vector<mapi::GamePatch> MakeRequiredPatches() {
  std::vector<mapi::GamePatch> game_patches;

  std::vector d2client_disable_mouse_click_on_screen_patch =
      MakeD2ClientDisableMouseClickOnScreenPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2client_disable_mouse_click_on_screen_patch.begin()),
      std::make_move_iterator(d2client_disable_mouse_click_on_screen_patch.end())
  );

  std::vector d2client_draw_resolution_text_patch =
      MakeD2ClientDrawResolutionTextPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2client_draw_resolution_text_patch.begin()),
      std::make_move_iterator(d2client_draw_resolution_text_patch.end())
  );

  std::vector d2client_unload_cel_file_collection_patch =
      MakeD2ClientUnloadCelFileCollectionPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2client_unload_cel_file_collection_patch.begin()),
      std::make_move_iterator(d2client_unload_cel_file_collection_patch.end())
  );

  std::vector d2client_get_resolution_registry_patch =
      MakeD2ClientGetResolutionRegistryPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2client_get_resolution_registry_patch.begin()),
      std::make_move_iterator(d2client_get_resolution_registry_patch.end())
  );

  std::vector set_d2client_general_display_width_and_height_patch =
      MakeD2ClientSetGeneralDisplayWidthAndHeightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(set_d2client_general_display_width_and_height_patch.begin()),
      std::make_move_iterator(set_d2client_general_display_width_and_height_patch.end())
  );

  std::vector set_d2client_resolution_from_options_menu_patch =
      MakeD2ClientSetResolutionFromOptionsMenuPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(set_d2client_resolution_from_options_menu_patch.begin()),
      std::make_move_iterator(set_d2client_resolution_from_options_menu_patch.end())
  );

  std::vector set_d2client_resolution_registry_patch =
      MakeD2ClientSetResolutionRegistryPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(set_d2client_resolution_registry_patch.begin()),
      std::make_move_iterator(set_d2client_resolution_registry_patch.end())
  );

  std::vector set_d2client_screen_shift_patch = MakeD2ClientSetScreenShiftPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(set_d2client_screen_shift_patch.begin()),
      std::make_move_iterator(set_d2client_screen_shift_patch.end())
  );

  std::vector set_d2ddraw_bit_block_width_and_height_patch =
      MakeD2DDrawSetBitBlockWidthAndHeightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(set_d2ddraw_bit_block_width_and_height_patch.begin()),
      std::make_move_iterator(set_d2ddraw_bit_block_width_and_height_patch.end())
  );

  std::vector d2ddraw_set_cel_display_left_and_right_patch =
      MakeD2DDrawSetCelDisplayLeftAndRightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2ddraw_set_cel_display_left_and_right_patch.begin()),
      std::make_move_iterator(d2ddraw_set_cel_display_left_and_right_patch.end())
  );

  std::vector d2ddraw_set_display_width_and_height_patch =
      MakeSetD2DDrawDisplayWidthAndHeightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2ddraw_set_display_width_and_height_patch.begin()),
      std::make_move_iterator(d2ddraw_set_display_width_and_height_patch.end())
  );

  std::vector d2direct3d_set_display_width_and_height_patch =
      MakeSetD2Direct3DDisplayWidthAndHeightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2direct3d_set_display_width_and_height_patch.begin()),
      std::make_move_iterator(d2direct3d_set_display_width_and_height_patch.end())
  );

  std::vector d2gdi_set_bit_block_width_and_height_patch =
      MakeSetD2GDIBitBlockWidthAndHeightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2gdi_set_bit_block_width_and_height_patch.begin()),
      std::make_move_iterator(d2gdi_set_bit_block_width_and_height_patch.end())
  );

  std::vector d2gdi_set_cel_display_left_and_right_patch =
      MakeSetD2GDICelDisplayLeftAndRightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2gdi_set_cel_display_left_and_right_patch.begin()),
      std::make_move_iterator(d2gdi_set_cel_display_left_and_right_patch.end())
  );

  std::vector d2gfx_set_display_width_and_height_patch =
      MakeSetD2GFXDisplayWidthAndHeightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2gfx_set_display_width_and_height_patch.begin()),
      std::make_move_iterator(d2gfx_set_display_width_and_height_patch.end())
  );

  std::vector d2glide_set_display_width_and_height_patch =
      MakeSetD2GlideDisplayWidthAndHeightPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(d2glide_set_display_width_and_height_patch.begin()),
      std::make_move_iterator(d2glide_set_display_width_and_height_patch.end())
  );

  std::vector glide3x_gr_sset_win_open_patch =
      MakeGlide3xGrSstWinOpenPatch();
  game_patches.insert(
      game_patches.end(),
      std::make_move_iterator(glide3x_gr_sset_win_open_patch.begin()),
      std::make_move_iterator(glide3x_gr_sset_win_open_patch.end())
  );

  return game_patches;
}

} // namespace sgd2fr::patches
