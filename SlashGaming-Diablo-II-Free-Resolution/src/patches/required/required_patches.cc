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

#include "required_patches.hpp"

namespace sgd2fr::patches {

RequiredPatches::RequiredPatches() = default;

void RequiredPatches::Apply() {
  this->d2client_disable_mouse_click_on_screen_patch_.Apply();
  this->d2client_draw_resolution_text_patch_.Apply();
  this->d2client_get_resolution_registry_patch_.Apply();
  this->d2client_set_general_display_width_and_height_patch_.Apply();
  this->d2client_set_resolution_from_options_menu_patch_.Apply();
  this->d2client_set_resolution_registry_patch_.Apply();
  this->d2client_set_screen_shift_patch_.Apply();
  this->d2client_unload_cel_file_collection_patch_.Apply();
  this->d2ddraw_set_bit_block_width_and_height_patch_.Apply();
  this->d2ddraw_set_cel_display_left_and_right_patch_.Apply();
  this->d2ddraw_set_display_width_and_height_patch_.Apply();
  this->d2direct3d_set_display_width_and_height_patch_.Apply();
  this->d2gdi_set_bit_block_width_and_height_patch_.Apply();
  this->d2gdi_set_cel_display_left_and_right_patch_.Apply();
  this->d2gfx_is_need_resize_window_patch_.Apply();
  this->d2gfx_is_need_restore_down_window_patch_.Apply();
  this->d2gfx_set_display_width_and_height_patch_.Apply();
  this->d2glide_set_display_width_and_height_patch_.Apply();
  this->d2win_resize_window_on_maximize_patch_.Apply();
  this->glide3x_gr_sst_win_open_patch_.Apply();
}

void RequiredPatches::Remove() {
  this->glide3x_gr_sst_win_open_patch_.Remove();
  this->d2win_resize_window_on_maximize_patch_.Remove();
  this->d2glide_set_display_width_and_height_patch_.Remove();
  this->d2gfx_set_display_width_and_height_patch_.Remove();
  this->d2gfx_is_need_restore_down_window_patch_.Remove();
  this->d2gfx_is_need_resize_window_patch_.Remove();
  this->d2gdi_set_cel_display_left_and_right_patch_.Remove();
  this->d2gdi_set_bit_block_width_and_height_patch_.Remove();
  this->d2direct3d_set_display_width_and_height_patch_.Remove();
  this->d2ddraw_set_display_width_and_height_patch_.Remove();
  this->d2ddraw_set_cel_display_left_and_right_patch_.Remove();
  this->d2ddraw_set_bit_block_width_and_height_patch_.Remove();
  this->d2client_unload_cel_file_collection_patch_.Remove();
  this->d2client_set_screen_shift_patch_.Remove();
  this->d2client_set_resolution_registry_patch_.Remove();
  this->d2client_set_resolution_from_options_menu_patch_.Remove();
  this->d2client_set_general_display_width_and_height_patch_.Remove();
  this->d2client_get_resolution_registry_patch_.Remove();
  this->d2client_draw_resolution_text_patch_.Remove();
  this->d2client_disable_mouse_click_on_screen_patch_.Remove();
}

} // namespace sgd2fr::patches
