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

#ifndef SGD2FR_CONFIG_CONFIG_KEY_VALUE_H_
#define SGD2FR_CONFIG_CONFIG_KEY_VALUE_H_

#define CONFIG_MAIN "SGD2FreeResolution"

#define CONFIG_METADATA "!!!Metadata(Do not modify)!!!"

#define CONFIG_METADATA_VERSION "Version"

#define CONFIG_METADATA_VERSION_MAJOR_HIGH "MajorHigh"
#define CONFIG_METADATA_VERSION_MAJOR_HIGH_DEFAULT 3
#define CONFIG_METADATA_VERSION_MAJOR_LOW "MajorLow"
#define CONFIG_METADATA_VERSION_MAJOR_LOW_DEFAULT 0
#define CONFIG_METADATA_VERSION_MINOR_HIGH "MinorHigh"
#define CONFIG_METADATA_VERSION_MINOR_HIGH_DEFAULT 2
#define CONFIG_METADATA_VERSION_MINOR_LOW "MinorLow"
#define CONFIG_METADATA_VERSION_MINOR_LOW_DEFAULT 1

#define CONFIG_INGAME_RESOLUTION_MODE "IngameResolutionMode"
#define CONFIG_INGAME_RESOLUTION_MODE_DEFAULT 3
#define CONFIG_INGAME_RESOLUTIONS "IngameResolutions"

#define CONFIG_MAIN_MENU_RESOLUTION "MainMenuResolution"
#define CONFIG_MAIN_MENU_RESOLUTION_WIDTH_DEFAULT 800
#define CONFIG_MAIN_MENU_RESOLUTION_HEIGHT_DEFAULT 600

#define CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME "EnableScreenBorderFrame?"
#define CONFIG_IS_ENABLE_SCREEN_BORDER_FRAME_DEFAULT 1
#define CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME \
    "UseOriginalScreenBorderFrame?"
#define CONFIG_IS_USE_ORIGINAL_SCREEN_BORDER_FRAME_DEFAULT 0
#define CONFIG_IS_USE_800_INTERFACE_BAR "Use800InterfaceBar?"
#define CONFIG_IS_USE_800_INTERFACE_BAR_DEFAULT 1

#define CONFIG_CUSTOM_MPQ_PATH "CustomMPQPath"
#define CONFIG_CUSTOM_MPQ_PATH_DEFAULT "SGD2FreeRes.mpq"

#endif /* SGD2FR_CONFIG_CONFIG_KEY_VALUE_H_ */
