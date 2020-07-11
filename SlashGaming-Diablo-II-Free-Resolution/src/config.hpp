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

#ifndef SGD2FR_CONFIG_HPP_
#define SGD2FR_CONFIG_HPP_

#include <windows.h>
#include <string_view>
#include <tuple>
#include <vector>

#include "dllexport_define.inc"

namespace sgd2fr::config {

const std::vector<std::tuple<int, int>>& GetIngameResolutions();
std::tuple<int, int> GetMainMenuResolution();

unsigned int GetIngameResolutionMode();
void SetIngameResolutionMode(unsigned int resolution_mode);

std::string_view GetScreenBackgroundImagePath();

std::string_view GetCustomLeftScreenBorderLeftImagePath();
std::string_view GetCustomLeftScreenBorderTopImagePath();
std::string_view GetCustomLeftScreenBorderTopRightImagePath();
std::string_view GetCustomLeftScreenBorderBottomImagePath();
std::string_view GetCustomLeftScreenBorderBottomRightImagePath();

std::string_view GetCustomRightScreenBorderRightImagePath();
std::string_view GetCustomRightScreenBorderTopImagePath();
std::string_view GetCustomRightScreenBorderTopLeftImagePath();
std::string_view GetCustomRightScreenBorderBottomImagePath();
std::string_view GetCustomRightScreenBorderBottomLeftImagePath();

std::string_view GetScreenBorderHorizontalRibbonImagePath();
std::string_view GetScreenBorderVerticalRibbonImagePath();

std::string_view GetInterfaceBarBackgroundCenterImagePath();
std::string_view GetInterfaceBarBackgroundLeftImagePath();
std::string_view GetInterfaceBarBackgroundRightImagePath();

bool IsScreenBorderFrameEnabled();
bool IsUseOriginalScreenBorderFrame();

bool Is800InterfaceBarEnabled();

bool LoadConfig();
bool WriteConfig();

} // namespace sgd2fr::config

#include "dllexport_undefine.inc"
#endif // SGD2FR_CONFIG_HPP_
