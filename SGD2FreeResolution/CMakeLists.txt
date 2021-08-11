# SlashGaming Diablo II Free Resolution
# Copyright (C) 2019-2021  Mir Drualga
#
# This file is part of SlashGaming Diablo II Free Resolution.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Additional permissions under GNU Affero General Public License version 3
# section 7
#
# If you modify this Program, or any covered work, by linking or combining
# it with Diablo II (or a modified version of that game and its
# libraries), containing parts covered by the terms of Blizzard End User
# License Agreement, the licensors of this Program grant you additional
# permission to convey the resulting work. This additional permission is
# also extended to any combination of expansions, mods, and remasters of
# the game.
#
# If you modify this Program, or any covered work, by linking or combining
# it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
# Glide, OpenGL, or Rave wrapper (or modified versions of those
# libraries), containing parts not covered by a compatible license, the
# licensors of this Program grant you additional permission to convey the
# resulting work.
#
# If you modify this Program, or any covered work, by linking or combining
# it with any library (or a modified version of that library) that links
# to Diablo II (or a modified version of that game and its libraries),
# containing parts not covered by a compatible license, the licensors of
# this Program grant you additional permission to convey the resulting
# work.

cmake_minimum_required(VERSION 3.10)

project(SGD2FreeRes)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED true)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Header and source files
set(INCLUDE_HEADERS
    "include/dllexport_define.inc"
    "include/dllexport_undefine.inc"

    "include/license.h"
    "include/sgd2fml_mod_exports.h"
)

enable_language(ASM_NASM)

set(SRC_CEL_FILE
    "src/cel_file/cel_file_legacy_asm.asm"

    "src/cel_file/cel_file_interface_bar_background.c"
    "src/cel_file/cel_file_legacy.c"
    "src/cel_file/cel_file_screen_background.c"
    "src/cel_file/cel_file_screen_background_border.c"
    "src/cel_file/cel_file_screen_border.c"

    "src/cel_file/cel_file_interface_bar_background.h"
    "src/cel_file/cel_file_legacy.h"
    "src/cel_file/cel_file_screen_background.h"
    "src/cel_file/cel_file_screen_background_border.h"
    "src/cel_file/cel_file_screen_border.h"
)

set(SRC_GAME_RESOLUTION
    "src/game_resolution/game_resolution.c"
    "src/game_resolution/game_resolution_cxx.cc"
    "src/game_resolution/game_resolution_gateway_ipv4.c"
    "src/game_resolution/game_resolution_setting.c"

    "src/game_resolution/game_resolution.h"
    "src/game_resolution/game_resolution.hpp"
    "src/game_resolution/game_resolution_gateway_ipv4.h"
    "src/game_resolution/game_resolution_setting.h"

    "src/game_resolution/gateway/game_resolution_d2lod_net.c"
    "src/game_resolution/gateway/game_resolution_diablo_09.c"
    "src/game_resolution/gateway/game_resolution_project_diablo_2.c"
    "src/game_resolution/gateway/game_resolution_resurgence.c"
    "src/game_resolution/gateway/game_resolution_slash_diablo.c"

    "src/game_resolution/gateway/game_resolution_d2lod_net.h"
    "src/game_resolution/gateway/game_resolution_diablo_09.h"
    "src/game_resolution/gateway/game_resolution_project_diablo_2.h"
    "src/game_resolution/gateway/game_resolution_resurgence.h"
    "src/game_resolution/gateway/game_resolution_slash_diablo.h"
)

set(SRC_PATCHES_DRAW_PATCHES
    # ASM
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_1_09d_shim.asm"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_lod_1_14c_shim.asm"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_lod_1_14d_shim.asm"

    "src/patches/draw/d2client_draw_screen_background_patch/d2client_draw_screen_background_patch_1_09d_shim.asm"

    # Sources
    "src/patches/draw/draw_patches.cc"

    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background.cc"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch.cc"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_1_09d.cc"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_lod_1_14c.cpp"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_lod_1_14d.cpp"

    "src/patches/draw/d2client_draw_screen_background_patch/d2client_draw_screen_background.cc"
    "src/patches/draw/d2client_draw_screen_background_patch/d2client_draw_screen_background_patch.cc"
    "src/patches/draw/d2client_draw_screen_background_patch/d2client_draw_screen_background_patch_1_09d.cc"

    # Headers
    "src/patches/draw/draw_patches.hpp"

    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background.hpp"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch.hpp"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_1_09d.hpp"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_lod_1_14c.hpp"
    "src/patches/draw/d2client_draw_interface_bar_background_patch/d2client_draw_interface_bar_background_patch_lod_1_14d.hpp"

    "src/patches/draw/d2client_draw_screen_background_patch/d2client_draw_screen_background.hpp"
    "src/patches/draw/d2client_draw_screen_background_patch/d2client_draw_screen_background_patch.hpp"
    "src/patches/draw/d2client_draw_screen_background_patch/d2client_draw_screen_background_patch_1_09d.hpp"
)

set(SRC_PATCHES_INTERFACE_BAR_PATCHES
    # ASM
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch_1_09d_shim.asm"
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch_1_13c_shim.asm"

    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch_1_09d_shim.asm"
    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch_1_13c_shim.asm"

    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch_1_09d_shim.asm"
    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch_1_13c_shim.asm"

    # Sources
    "src/patches/interface_bar/interface_bar_patches.cc"

    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar.cc"
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch.cc"
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch_1_09d.cc"
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch_1_13c.cc"

    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button.cc"
    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch.cc"
    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch_1_09d.cc"
    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch_1_13c.cc"

    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button.cc"
    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch.cc"
    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch_1_09d.cc"
    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch_1_13c.cc"

    # Headers
    "src/patches/interface_bar/interface_bar_patches.hpp"

    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar.hpp"
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch.hpp"
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch_1_09d.hpp"
    "src/patches/interface_bar/d2client_enable_800_interface_bar_patch/d2client_enable_800_interface_bar_patch_1_13c.hpp"

    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button.hpp"
    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch.hpp"
    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch_1_09d.hpp"
    "src/patches/interface_bar/d2client_enable_800_new_skill_button_patch/d2client_enable_800_new_skill_button_patch_1_13c.hpp"

    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button.hpp"
    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch.hpp"
    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch_1_09d.hpp"
    "src/patches/interface_bar/d2client_enable_800_new_stats_button_patch/d2client_enable_800_new_stats_button_patch_1_13c.hpp"
)

set(SRC_PATCHES_INVENTORY_PATCHES
    # ASM
    "src/patches/inventory/d2common_get_global_belt_record_patch/d2common_get_global_belt_record_patch_1_09d_shim.asm"

    "src/patches/inventory/d2common_get_global_belt_slot_position_patch/d2common_get_global_belt_slot_position_patch_1_09d_shim.asm"

    "src/patches/inventory/d2common_get_global_equipment_slot_layout_patch/d2common_get_global_equipment_slot_layout_patch_1_09d_shim.asm"

    "src/patches/inventory/d2common_get_global_inventory_grid_layout_patch/d2common_get_global_inventory_grid_layout_patch_1_09d_shim.asm"

    "src/patches/inventory/d2common_get_global_inventory_position_patch/d2common_get_global_inventory_position_patch_1_09d_shim.asm"

    # Sources
    "src/patches/inventory/inventory_patches.cc"

    "src/patches/inventory/d2common_get_global_belt_record_patch/d2common_get_global_belt_record.cc"
    "src/patches/inventory/d2common_get_global_belt_record_patch/d2common_get_global_belt_record_patch.cc"
    "src/patches/inventory/d2common_get_global_belt_record_patch/d2common_get_global_belt_record_patch_1_09d.cc"

    "src/patches/inventory/d2common_get_global_belt_slot_position_patch/d2common_get_global_belt_slot_position.cc"
    "src/patches/inventory/d2common_get_global_belt_slot_position_patch/d2common_get_global_belt_slot_position_patch.cc"
    "src/patches/inventory/d2common_get_global_belt_slot_position_patch/d2common_get_global_belt_slot_position_patch_1_09d.cc"

    "src/patches/inventory/d2common_get_global_equipment_slot_layout_patch/d2common_get_global_equipment_slot_layout.cc"
    "src/patches/inventory/d2common_get_global_equipment_slot_layout_patch/d2common_get_global_equipment_slot_layout_patch.cc"
    "src/patches/inventory/d2common_get_global_equipment_slot_layout_patch/d2common_get_global_equipment_slot_layout_patch_1_09d.cc"

    "src/patches/inventory/d2common_get_global_inventory_grid_layout_patch/d2common_get_global_inventory_grid_layout.cc"
    "src/patches/inventory/d2common_get_global_inventory_grid_layout_patch/d2common_get_global_inventory_grid_layout_patch.cc"
    "src/patches/inventory/d2common_get_global_inventory_grid_layout_patch/d2common_get_global_inventory_grid_layout_patch_1_09d.cc"

    "src/patches/inventory/d2common_get_global_inventory_position_patch/d2common_get_global_inventory_position.cc"
    "src/patches/inventory/d2common_get_global_inventory_position_patch/d2common_get_global_inventory_position_patch.cc"
    "src/patches/inventory/d2common_get_global_inventory_position_patch/d2common_get_global_inventory_position_patch_1_09d.cc"

    # Headers
    "src/patches/inventory/inventory_patches.hpp"

    "src/patches/inventory/d2common_get_global_belt_record_patch/d2common_get_global_belt_record.hpp"
    "src/patches/inventory/d2common_get_global_belt_record_patch/d2common_get_global_belt_record_patch.hpp"
    "src/patches/inventory/d2common_get_global_belt_record_patch/d2common_get_global_belt_record_patch_1_09d.hpp"

    "src/patches/inventory/d2common_get_global_belt_slot_position_patch/d2common_get_global_belt_slot_position.hpp"
    "src/patches/inventory/d2common_get_global_belt_slot_position_patch/d2common_get_global_belt_slot_position_patch.hpp"
    "src/patches/inventory/d2common_get_global_belt_slot_position_patch/d2common_get_global_belt_slot_position_patch_1_09d.hpp"

    "src/patches/inventory/d2common_get_global_equipment_slot_layout_patch/d2common_get_global_equipment_slot_layout.hpp"
    "src/patches/inventory/d2common_get_global_equipment_slot_layout_patch/d2common_get_global_equipment_slot_layout_patch.hpp"
    "src/patches/inventory/d2common_get_global_equipment_slot_layout_patch/d2common_get_global_equipment_slot_layout_patch_1_09d.hpp"

    "src/patches/inventory/d2common_get_global_inventory_grid_layout_patch/d2common_get_global_inventory_grid_layout.hpp"
    "src/patches/inventory/d2common_get_global_inventory_grid_layout_patch/d2common_get_global_inventory_grid_layout_patch.hpp"
    "src/patches/inventory/d2common_get_global_inventory_grid_layout_patch/d2common_get_global_inventory_grid_layout_patch_1_09d.hpp"

    "src/patches/inventory/d2common_get_global_inventory_position_patch/d2common_get_global_inventory_position.hpp"
    "src/patches/inventory/d2common_get_global_inventory_position_patch/d2common_get_global_inventory_position_patch.hpp"
    "src/patches/inventory/d2common_get_global_inventory_position_patch/d2common_get_global_inventory_position_patch_1_09d.hpp"
)

set(SRC_PATCHES_REQUIRED_PATCHES
    # ASM
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_1_09d_shim.asm"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_1_13c_shim.asm"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_lod_1_14c_shim.asm"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_lod_1_14d_shim.asm"

    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_1_09d_shim.asm"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_1_13c_shim.asm"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_lod_1_14c_shim.asm"

    "src/patches/required/d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height_patch_1_09_shim.asm"

    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch_1_09_shim.asm"
    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch_1_13c_shim.asm"

    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_1_09d_shim.asm"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_1_13c_shim.asm"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_lod_1_14c_shim.asm"

    "src/patches/required/d2client_set_screen_shift_patch/d2client_set_screen_shift_patch_1_09d_shim.asm"

    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch_1_09d_shim.asm"
    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch_1_13c_shim.asm"

    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch_1_09d_shim.asm"
    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch_1_13c_shim.asm"

    "src/patches/required/d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right_patch_1_09d_shim.asm"

    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch_1_09d_shim.asm"
    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch_1_13c_shim.asm"

    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch_1_09d_shim.asm"
    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch_1_13c_shim.asm"

    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_1_09d_shim.asm"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_1_13c_shim.asm"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_lod_1_14a_shim.asm"

    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch_1_09d_shim.asm"
    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch_1_13c_shim.asm"

    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window_patch_1_13c_shim.asm"

    "src/patches/required/d2gfx_is_need_restore_down_window_patch/d2gfx_is_need_restore_down_window_patch_1_13c_shim.asm"

    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch_1_09d_shim.asm"
    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch_1_13c_shim.asm"

    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch_1_09d_shim.asm"
    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch_1_13c_shim.asm"

    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_1_13c_shim.asm"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_lod_1_14c_shim.asm"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_lod_1_14d_shim.asm"

    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_nglide_3_10_0_658_shim.asm"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_sven_1_4_4_21_shim.asm"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_sven_1_4_8_3_shim.asm"

    # Sources
    "src/patches/required/required_patches.cc"

    "src/patches/required/d2client_disable_mouse_click_on_screen_patch/d2client_disable_mouse_click_on_screen_patch.cc"
    "src/patches/required/d2client_disable_mouse_click_on_screen_patch/d2client_disable_mouse_click_on_screen_patch_1_09d.cc"
    "src/patches/required/d2client_disable_mouse_click_on_screen_patch/d2client_disable_mouse_click_on_screen_patch_1_13c.cc"

    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text.cc"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch.cc"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_1_09d.cc"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_1_13c.cc"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_lod_1_14c.cpp"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_lod_1_14d.cpp"

    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry.cc"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch.cc"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_1_09d.cc"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_1_13c.cc"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_lod_1_14c.cpp"

    "src/patches/required/d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height.cc"
    "src/patches/required/d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height_patch.cc"
    "src/patches/required/d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height_patch_1_09.cc"

    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu.cc"
    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch.cc"
    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch_1_09.cc"
    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch_1_13c.cc"

    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry.cc"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch.cc"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_1_09d.cc"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_1_13c.cc"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_lod_1_14c.cpp"

    "src/patches/required/d2client_set_screen_shift_patch/d2client_set_screen_shift.cc"
    "src/patches/required/d2client_set_screen_shift_patch/d2client_set_screen_shift_patch.cc"
    "src/patches/required/d2client_set_screen_shift_patch/d2client_set_screen_shift_patch_1_09d.cc"

    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection.c"
    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch.cc"
    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch_1_09d.cc"
    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch_1_13c.cc"

    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height.cc"
    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch.cc"
    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch_1_09d.cc"
    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch_1_13c.cc"

    "src/patches/required/d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right.cc"
    "src/patches/required/d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right_patch.cc"
    "src/patches/required/d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right_patch_1_09d.cc"

    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height.cc"
    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch.cc"
    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch_1_09d.cc"
    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch_1_13c.cc"

    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height.cc"
    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch.cc"
    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch_1_09d.cc"
    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch_1_13c.cc"

    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height.cc"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch.cc"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_1_09d.cc"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_1_13c.cc"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_lod_1_14a.cpp"

    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right.cc"
    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch.cc"
    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch_1_09d.cc"
    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch_1_13c.cc"

    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window.cc"
    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window_patch.cc"
    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window_patch_1_13c.cc"
    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window_patch_1_13d.cpp"

    "src/patches/required/d2gfx_is_need_restore_down_window_patch/d2gfx_is_need_restore_down_window.cc"
    "src/patches/required/d2gfx_is_need_restore_down_window_patch/d2gfx_is_need_restore_down_window_patch.cc"
    "src/patches/required/d2gfx_is_need_restore_down_window_patch/d2gfx_is_need_restore_down_window_patch_1_13c.cc"

    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height.cc"
    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch.cc"
    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch_1_09d.cc"
    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch_1_13c.cc"

    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height.cc"
    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch.cc"
    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch_1_09d.cc"
    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch_1_13c.cc"

    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize.cc"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch.cc"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_1_13c.cc"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_lod_1_14c.cpp"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_lod_1_14d.cpp"

    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open.cc"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch.cc"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_nglide_3_10_0_658.cc"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_sven_1_4_4_21.cc"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_sven_1_4_8_3.cc"

    # Headers
    "src/patches/required/required_patches.hpp"

    "src/patches/required/d2client_disable_mouse_click_on_screen_patch/d2client_disable_mouse_click_on_screen_patch.hpp"
    "src/patches/required/d2client_disable_mouse_click_on_screen_patch/d2client_disable_mouse_click_on_screen_patch_1_09d.hpp"
    "src/patches/required/d2client_disable_mouse_click_on_screen_patch/d2client_disable_mouse_click_on_screen_patch_1_13c.hpp"

    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text.hpp"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch.hpp"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_1_09d.hpp"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_1_13c.hpp"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_lod_1_14c.hpp"
    "src/patches/required/d2client_draw_resolution_text_patch/d2client_draw_resolution_text_patch_lod_1_14d.hpp"

    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry.hpp"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch.hpp"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_1_09d.hpp"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_1_13c.hpp"
    "src/patches/required/d2client_get_resolution_registry_patch/d2client_get_resolution_registry_patch_lod_1_14c.hpp"

    "src/patches/required/d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height.hpp"
    "src/patches/required/d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height_patch.hpp"
    "src/patches/required/d2client_set_general_display_width_and_height_patch/d2client_set_general_display_width_and_height_patch_1_09.hpp"

    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu.hpp"
    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch.hpp"
    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch_1_09.hpp"
    "src/patches/required/d2client_set_resolution_from_options_menu_patch/d2client_set_resolution_from_options_menu_patch_1_13c.hpp"

    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry.hpp"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch.hpp"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_1_09d.hpp"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_1_13c.hpp"
    "src/patches/required/d2client_set_resolution_registry_patch/d2client_set_resolution_registry_patch_lod_1_14c.hpp"

    "src/patches/required/d2client_set_screen_shift_patch/d2client_set_screen_shift.hpp"
    "src/patches/required/d2client_set_screen_shift_patch/d2client_set_screen_shift_patch.hpp"
    "src/patches/required/d2client_set_screen_shift_patch/d2client_set_screen_shift_patch_1_09d.hpp"

    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection.h"
    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch.hpp"
    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch_1_09d.hpp"
    "src/patches/required/d2client_unload_cel_file_collection_patch/d2client_unload_cel_file_collection_patch_1_13c.hpp"

    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height.hpp"
    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch.hpp"
    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch_1_09d.hpp"
    "src/patches/required/d2ddraw_set_bit_block_width_and_height_patch/d2ddraw_set_bit_block_width_and_height_patch_1_13c.hpp"

    "src/patches/required/d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right.hpp"
    "src/patches/required/d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right_patch.hpp"
    "src/patches/required/d2ddraw_set_cel_display_left_and_right_patch/d2ddraw_set_cel_display_left_and_right_patch_1_09d.hpp"

    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height.hpp"
    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch.hpp"
    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch_1_09d.hpp"
    "src/patches/required/d2ddraw_set_display_width_and_height_patch/d2ddraw_set_display_width_and_height_patch_1_13c.hpp"

    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height.hpp"
    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch.hpp"
    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch_1_09d.hpp"
    "src/patches/required/d2direct3d_set_display_width_and_height_patch/d2direct3d_set_display_width_and_height_patch_1_13c.hpp"

    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height.hpp"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch.hpp"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_1_09d.hpp"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_1_13c.hpp"
    "src/patches/required/d2gdi_set_bit_block_width_and_height_patch/d2gdi_set_bit_block_width_and_height_patch_lod_1_14a.hpp"

    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right.hpp"
    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch.hpp"
    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch_1_09d.hpp"
    "src/patches/required/d2gdi_set_cel_display_left_and_right_patch/d2gdi_set_cel_display_left_and_right_patch_1_13c.hpp"

    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window.hpp"
    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window_patch.hpp"
    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window_patch_1_13c.hpp"
    "src/patches/required/d2gfx_is_need_resize_window_patch/d2gfx_is_need_resize_window_patch_1_13d.hpp"

    "src/patches/required/d2gfx_is_need_restore_down_window_patch/d2gfx_is_need_restore_down_window.hpp"
    "src/patches/required/d2gfx_is_need_restore_down_window_patch/d2gfx_is_need_restore_down_window_patch.hpp"
    "src/patches/required/d2gfx_is_need_restore_down_window_patch/d2gfx_is_need_restore_down_window_patch_1_13c.hpp"

    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height.hpp"
    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch.hpp"
    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch_1_09d.hpp"
    "src/patches/required/d2gfx_set_display_width_and_height_patch/d2gfx_set_display_width_and_height_patch_1_13c.hpp"

    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height.hpp"
    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch.hpp"
    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch_1_09d.hpp"
    "src/patches/required/d2glide_set_display_width_and_height_patch/d2glide_set_display_width_and_height_patch_1_13c.hpp"

    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize.hpp"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch.hpp"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_1_13c.hpp"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_lod_1_14c.hpp"
    "src/patches/required/d2win_resize_window_on_maximize_patch/d2win_resize_window_on_maximize_patch_lod_1_14d.hpp"

    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open.hpp"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch.hpp"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_nglide_3_10_0_658.hpp"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_sven_1_4_4_21.hpp"
    "src/patches/required/glide3x_gr_sst_win_open_patch/glide3x_gr_sst_win_open_patch_sven_1_4_8_3.hpp"
)

set(SRC_SGD2MAPI_EXTENSION
    "src/sgd2mapi_extension/ddraw_library.c"
    "src/sgd2mapi_extension/ddraw_library_cpp98.cpp"
    "src/sgd2mapi_extension/ddraw_library_version.c"
    "src/sgd2mapi_extension/ddraw_library_version_cpp98.cpp"
    "src/sgd2mapi_extension/glide3x_library.c"
    "src/sgd2mapi_extension/glide3x_library_cpp98.cpp"
    "src/sgd2mapi_extension/glide3x_library_version.c"
    "src/sgd2mapi_extension/glide3x_library_version_cpp98.cpp"

    "src/sgd2mapi_extension/ddraw_library.h"
    "src/sgd2mapi_extension/ddraw_library.hpp"
    "src/sgd2mapi_extension/ddraw_library_version.h"
    "src/sgd2mapi_extension/ddraw_library_version.hpp"
    "src/sgd2mapi_extension/game_function.h"
    "src/sgd2mapi_extension/game_function.hpp"
    "src/sgd2mapi_extension/glide3x_library.h"
    "src/sgd2mapi_extension/glide3x_library.hpp"
    "src/sgd2mapi_extension/glide3x_library_version.h"
    "src/sgd2mapi_extension/glide3x_library_version.hpp"
    "src/sgd2mapi_extension/sgd2mapi_extension.hpp"

    # DDraw library version
    "src/sgd2mapi_extension/ddraw_library_version/ddraw_library_version_product_name.c"

    "src/sgd2mapi_extension/ddraw_library_version/ddraw_library_version_product_name.h"

    # File
    "src/sgd2mapi_extension/file/file_content.c"

    "src/sgd2mapi_extension/file/file_content.h"

    # Game function
    "src/sgd2mapi_extension/game_function/d2client_function.h"
    "src/sgd2mapi_extension/game_function/d2client_function.hpp"

    "src/sgd2mapi_extension/game_function/d2client/d2client_draw_screens.c"
    "src/sgd2mapi_extension/game_function/d2client/d2client_draw_screens_cpp98.cpp"

    "src/sgd2mapi_extension/game_function/d2client/d2client_draw_screens.h"
    "src/sgd2mapi_extension/game_function/d2client/d2client_draw_screens.hpp"

    # Glide3x library D2DX
    "src/sgd2mapi_extension/glide3x_library_d2dx/glide3x_library_d2dx.c"
    "src/sgd2mapi_extension/glide3x_library_d2dx/glide3x_library_d2dx_cpp98.cpp"

    "src/sgd2mapi_extension/glide3x_library_d2dx/glide3x_library_d2dx.h"

    # Glide3x library version
    "src/sgd2mapi_extension/glide3x_library_version/glide3x_library_version_file_version.c"

    "src/sgd2mapi_extension/glide3x_library_version/glide3x_library_version_file_version.h"
)

set(SRC_USER_CONFIG
    "src/user_config.c"
    "src/user_config.h"

    "src/user_config/user_config_ini_windows_read.c"
    "src/user_config/user_config_ini_windows_write.c"
    "src/user_config/user_config_json_frozen_read.c"
    "src/user_config/user_config_json_frozen_write.c"
    "src/user_config/user_config_struct.c"

    "src/user_config/user_config_ini_windows.h"
    "src/user_config/user_config_json_frozen.h"
    "src/user_config/user_config_json_key_value.h"
    "src/user_config/user_config_key_value.h"
    "src/user_config/user_config_struct.h"
    "src/user_config/user_config_value_default.h"
)

set(SRC_C
    # Helpers
    "src/helper/800_interface_bar.cc"
    "src/helper/abstract_multiversion_patch.cpp"
    "src/helper/abstract_version_patch.cpp"
    "src/helper/custom_mpq.c"
    "src/helper/evaluation.c"
    "src/helper/patch_address_and_size.cpp"
    "src/helper/position_realignment.cc"

    # Patches
    "src/patches/patches.cc"

    "src/dll_main.cc"
    "src/license.c"
    "src/sgd2fml_mod_exports.cc"
)

set(SRC_HEADERS
    # Helpers
    "src/helper/800_interface_bar.hpp"
    "src/helper/abstract_multiversion_patch.hpp"
    "src/helper/abstract_version_patch.hpp"
    "src/helper/custom_mpq.h"
    "src/helper/evaluation.h"
    "src/helper/patch_address_and_size.hpp"
    "src/helper/position_realignment.hpp"

    "src/patches/patches.hpp"

    "src/compile_time_switch.h"
    "src/compile_time_switch.hpp"
)

# frozen doesn't have CMakeLists, so this has to be done manually.
set(FROZEN_FILES
    "../third_party/frozen/frozen.h"
    "../third_party/frozen/frozen.c"
)

# Output DLL
add_library(SGD2FreeRes SHARED
    ${SRC_C}
    ${SRC_HEADERS}

    ${SRC_CEL_FILE}
    ${SRC_GAME_RESOLUTION}
    ${SRC_PATCHES_DRAW_PATCHES}
    ${SRC_PATCHES_INTERFACE_BAR_PATCHES}
    ${SRC_PATCHES_INVENTORY_PATCHES}
    ${SRC_PATCHES_REQUIRED_PATCHES}
    ${SRC_SGD2MAPI_EXTENSION}
    ${SRC_USER_CONFIG}

    ${INCLUDE_HEADERS}
    ${FROZEN_FILES}
)

target_compile_definitions(SGD2FreeRes PRIVATE SGD2FR_DLLEXPORT)
target_compile_definitions(SGD2FreeRes INTERFACE SGD2FR_DLLIMPORT)

target_include_directories(SGD2FreeRes PUBLIC "include")

target_link_libraries(SGD2FreeRes libSGD2MAPIcxx98 libSGD2MAPIc libMDCcpp98 libMDCc)
add_dependencies(SGD2FreeRes libSGD2MAPIcxx98 libSGD2MAPIc libMDCcpp98 libMDCc)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        ${SRC_ASM}
        ${SRC_C}
        ${SRC_HEADERS}
        ${INCLUDE_HEADERS}

        ${SRC_CEL_FILE}
        ${SRC_GAME_RESOLUTION}
        ${SRC_PATCHES_DRAW_PATCHES}
        ${SRC_PATCHES_INTERFACE_BAR_PATCHES}
        ${SRC_PATCHES_INVENTORY_PATCHES}
        ${SRC_PATCHES_REQUIRED_PATCHES}
        ${SRC_SGD2MAPI_EXTENSION}
        ${SRC_USER_CONFIG}
)

install(TARGETS SGD2FreeRes)
