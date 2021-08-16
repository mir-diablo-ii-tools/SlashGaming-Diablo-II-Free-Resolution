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

#ifndef SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_KEY_H_
#define SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_KEY_H_

/**
 * Point percent
 */

#define CEL_FILE_CONFIG_POINT_PERCENT_X_KEY "x"
#define CEL_FILE_CONFIG_POINT_PERCENT_Y_KEY "y"

/**
 * Point value
 */

#define CEL_FILE_CONFIG_POINT_VALUE_X_KEY "x"
#define CEL_FILE_CONFIG_POINT_VALUE_Y_KEY "y"

/**
 * Origin point
 */

/*
 * The type is not needed, as either percent or value are used to
 * detect the type.
 */

#define CEL_FILE_CONFIG_ORIGIN_POINT_PERCENT_KEY "percent"
#define CEL_FILE_CONFIG_ORIGIN_POINT_VALUE_KEY "value"

/**
 * Dest position
 */

#define CEL_FILE_CONFIG_DEST_POSITION_POSITION_KEY "position"
#define CEL_FILE_CONFIG_DEST_POSITION_OFFSET_KEY "offset"

/**
 * Draw setting
 */

#define CEL_FILE_CONFIG_DRAW_SETTING_ORIGIN_KEY "origin"
#define CEL_FILE_CONFIG_DRAW_SETTING_DESTINATION_KEY "destination"
#define CEL_FILE_CONFIG_DRAW_SETTING_WIDTH_KEY "width"
#define CEL_FILE_CONFIG_DRAW_SETTING_HEIGHT_KEY "height"

/**
 * Repeat draw setting
 */

#define CEL_FILE_CONFIG_REPEAT_DRAW_SETTING_ALIGN_HORIZONTAL_KEY \
    "alignHorizontal"
#define CEL_FILE_CONFIG_REPEAT_DRAW_SETTING_ALIGN_VERTICAL_KEY \
    "alignVertical"
#define CEL_FILE_CONFIG_REPEAT_DRAW_SETTING_DESTINATION_KEY "destination"
#define CEL_FILE_CONFIG_REPEAT_DRAW_SETTING_WIDTH_KEY "width"
#define CEL_FILE_CONFIG_REPEAT_DRAW_SETTING_HEIGHT_KEY "height"

/**
 * Cel file
 */

#define CEL_FILE_CONFIG_CEL_FILE_PATH_KEY "path"
#define CEL_FILE_CONFIG_CEL_FILE_DRAW_SETTING_KEY "drawSetting"

/**
 * Repeat cel file
 */

#define CEL_FILE_CONFIG_REPEAT_CEL_FILE_PATH_KEY "path"
#define CEL_FILE_CONFIG_REPEAT_CEL_FILE_DRAW_SETTING_KEY "drawSetting"

/**
 * Cel file config
 */

#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_LEFT \
    "interfaceBarBackgroundLeft"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_LEFT_CENTER \
    "interfaceBarBackgroundLeftCenter"

#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_RIGHT \
    "interfaceBarBackgroundRight"
#define CEL_FILE_CONFIG_INTERFACE_BAR_BACKGROUND_RIGHT_CENTER \
    "interfaceBarBackgroundRightCenter"

#define CEL_FILE_CONFIG_LEFT_SCREEN_BACKGROUND "leftScreenBackground"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BACKGROUND "rightScreenBackground"

#define CEL_FILE_CONFIG_LEFT_SCREEN_BACKGROUND_BORDER \
    "leftScreenBackgroundBorder"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BACKGROUND_BORDER \
    "rightScreenBackgroundBorder"

#define CEL_FILE_CONFIG_LEFT_SCREEN_BORDER "leftScreenBorder"
#define CEL_FILE_CONFIG_RIGHT_SCREEN_BORDER "rightScreenBorder"

#endif /* SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_KEY_H_ */
