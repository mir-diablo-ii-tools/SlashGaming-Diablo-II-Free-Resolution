/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019  Mir Drualga
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

#include "d2client_draw_interface_bar_background.hpp"

#include <windows.h>

#include <fmt/format.h>
#include <sgd2mapi.hpp>
#include "../../../config.hpp"
#include "../../../helper/get_resolution_from_id.hpp"

namespace sgd2fr::patches {
namespace {

d2::CelFile_API& GetInterfaceBarBackground() {
  static d2::CelFile_API interface_bar_background;

  return interface_bar_background;
}

void DrawLeftInterfaceBarBackground() {
  std::tuple width_and_height = GetResolutionFromId(d2::d2gfx::GetResolutionMode());

  d2::d2gfx::DrawRectangle(
      0,
      std::get<1>(width_and_height) - 47,
      std::get<0>(width_and_height) / 2,
      std::get<1>(width_and_height),
      0,
      d2::DrawEffect::kNone
  );

  return;
  d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = mapi::RGBA32BitColor();
  frame_options.draw_effect = d2::DrawEffect::kNone;
  frame_options.position_x_behavior = d2::DrawPositionXBehavior::kLeft;
  frame_options.position_y_behavior = d2::DrawPositionYBehavior::kTop;
}

void DrawRightInterfaceBarBackground() {
  std::tuple width_and_height = GetResolutionFromId(d2::d2gfx::GetResolutionMode());

  d2::d2gfx::DrawRectangle(
      std::get<0>(width_and_height) / 2,
      std::get<1>(width_and_height) - 47,
      std::get<0>(width_and_height),
      std::get<1>(width_and_height),
      0,
      d2::DrawEffect::kNone
  );
}

} // namespace

void __cdecl SGD2FR_D2ClientDrawInterfaceBarBackground() {
  DrawLeftInterfaceBarBackground();
  DrawRightInterfaceBarBackground();
}

} // namespace sgd2fr::patches
