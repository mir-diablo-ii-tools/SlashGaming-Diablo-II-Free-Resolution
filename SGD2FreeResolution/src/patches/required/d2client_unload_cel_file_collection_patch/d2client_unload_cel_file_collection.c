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

#include "d2client_unload_cel_file_collection.h"

#include "../../../cel_file/cel_file_interface_bar.h"
#include "../../../cel_file/cel_file_interface_bar_background.h"
#include "../../../cel_file/cel_file_legacy.h"
#include "../../../cel_file/cel_file_life_orb.h"
#include "../../../cel_file/cel_file_mana_orb.h"
#include "../../../cel_file/cel_file_screen_background.h"
#include "../../../cel_file/cel_file_screen_background_border.h"
#include "../../../cel_file/cel_file_screen_border.h"
#include "../../../compile_time_switch.h"

#if !defined(COMPILE_TIME_CEL_FILE_PATH_VERSION)
#error COMPILE_TIME_CEL_FILE_PATH_VERSION not defined.
#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

void __cdecl Sgd2fr_D2Client_UnloadCelFileCollection() {
  CelFile_InterfaceBar_Unload();

  CelFile_InterfaceBarBackground_UnloadLeft();
  CelFile_InterfaceBarBackground_UnloadLeftCenter();
  CelFile_InterfaceBarBackground_UnloadRight();
  CelFile_InterfaceBarBackground_UnloadRightCenter();

#if COMPILE_TIME_CEL_FILE_PATH_VERSION == 2

  CelFile_LeftScreenBorder_UnloadLeft();
  CelFile_LeftScreenBorder_UnloadTop();
  CelFile_LeftScreenBorder_UnloadTopRight();
  CelFile_LeftScreenBorder_UnloadBottom();
  CelFile_LeftScreenBorder_UnloadBottomRight();

  CelFile_RightScreenBorder_UnloadRight();
  CelFile_RightScreenBorder_UnloadTop();
  CelFile_RightScreenBorder_UnloadTopLeft();
  CelFile_RightScreenBorder_UnloadBottom();
  CelFile_RightScreenBorder_UnloadBottomLeft();

  CelFile_ScreenBorderRibbon_UnloadHorizontal();
  CelFile_ScreenBorderRibbon_UnloadVertical();

  CelFile_LifeOrb_UnloadInterface();
  CelFile_LifeOrb_UnloadRed();
  CelFile_LifeOrb_UnloadGreen();

  CelFile_ManaOrb_UnloadInterface();
  CelFile_ManaOrb_UnloadBlue();

#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

  CelFile_LeftScreenBackground_Unload();
  CelFile_RightScreenBackground_Unload();

  CelFile_LeftScreenBackgroundBorder_Unload();
  CelFile_RightScreenBackgroundBorder_Unload();

#if COMPILE_TIME_CEL_FILE_PATH_VERSION == 3

  CelFile_LeftScreenBorder_Unload();
  CelFile_RightScreenBorder_Unload();

#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

  CelFile_VanillaScreenBorder_Unload();
}
