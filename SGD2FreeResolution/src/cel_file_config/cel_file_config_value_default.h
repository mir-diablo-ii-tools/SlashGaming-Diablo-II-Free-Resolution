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

#ifndef SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_VALUE_DEFAULT_H_
#define SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_VALUE_DEFAULT_H_

#include "../compile_time_switch.h"

#if !defined(COMPILE_TIME_CEL_FILE_PATH_VERSION)
#error COMPILE_TIME_CEL_FILE_PATH_VERSION not defined.
#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

/**
 * Interface bar 
 */

#if COMPILE_TIME_CEL_FILE_PATH_VERSION == 2

#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_LEFT_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertLeft"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_LEFT_CENTER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertHorizontalBar"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_RIGHT_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertRight"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_RIGHT_CENTER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertHorizontalBar"

#elif COMPILE_TIME_CEL_FILE_PATH_VERSION == 3

#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_LEFT_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\InterfaceBarBackground\\Left"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_LEFT_CENTER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\InterfaceBarBackground\\LeftCenter"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_RIGHT_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\InterfaceBarBackground\\Right"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_RIGHT_CENTER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\InterfaceBarBackground\\RightCenter"

#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

/**
 * Life orb
 */

#define CEL_FILE_CONFIG_LIFE_ORB_INTERFACE_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\LifeOrbInterface"
#define CEL_FILE_CONFIG_LIFE_ORB_RED_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\LifeOrbRed"
#define CEL_FILE_CONFIG_LIFE_ORB_GREEN_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\LifeOrbGreen"

/**
 * Mana orb
 */

#define CEL_FILE_CONFIG_MANA_ORB_INTERFACE_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ManaOrbInterface"
#define CEL_FILE_CONFIG_MANA_ORB_BLUE_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ManaOrbBlue"

/**
 * Left and right screen background
 */

#if COMPILE_TIME_CEL_FILE_PATH_VERSION == 2

#define CEL_FILE_CONFIG_LEFT_SCREEN_BACKGROUND_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRStoneBack"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BACKGROUND_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRStoneBack"

#elif COMPILE_TIME_CEL_FILE_PATH_VERSION == 3

#define CEL_FILE_CONFIG_LEFT_SCREEN_BACKGROUND_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBackground\\LeftScreen"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BACKGROUND_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBackground\\RightScreen"

#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

/**
 * Left and right screen background border
 */

#if COMPILE_TIME_CEL_FILE_PATH_VERSION == 2

#define CEL_FILE_CONFIG_LEFT_SCREEN_BACKGROUND_BORDER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyVerticalBar"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BACKGROUND_BORDER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyVerticalBar"

#elif COMPILE_TIME_CEL_FILE_PATH_VERSION == 3

#define CEL_FILE_CONFIG_LEFT_SCREEN_BACKGROUND_BORDER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBackgroundBorder\\LeftScreen"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BACKGROUND_BORDER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBackgroundBorder\\RightScreen"

#endif /* COMPILE_TIME_CEL_FILE_PATH_VERSION */

/**
 * Left and right screen border
 */

#define CEL_FILE_CONFIG_LEFT_SCREEN_BORDER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBorder\\LeftScreenBorder"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BORDER_PATH_DEFAULT \
    "data\\SGD2FreeResolution\\ui\\PANEL\\ScreenBorder\\RightScreenBorder"
#define CEL_FILE_CONFIG_VANILLA_SCREEN_BORDER_PATH_DEFAULT \
    "data\\global\\UI\\Panel\\800BorderFrame"

#endif /* SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_VALUE_DEFAULT_H_ */
