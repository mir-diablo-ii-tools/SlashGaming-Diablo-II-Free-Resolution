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

#include "d2client_draw_800_interface_bar.hpp"

#include <sgd2mapi.hpp>
#include "../../../helper/get_resolution_from_id.hpp"

namespace sgd2fr::patches {

mapi::bool32 __cdecl SGD2FR_D2Client_Draw800InterfaceBar(
    d2::CelContext* cel_context
) {
  // Grab the CelFile from the CelContext.
  d2::CelContext_Wrapper cel_context_wrapper(cel_context);
  d2::CelFile_Wrapper cel_file_wrapper(cel_context_wrapper.GetCelFile());

  // Determine the width and height of the interface bar. Note that only
  // frames 1 - 4 should be drawn.
  unsigned int interface_bar_width = 0;

  for (unsigned int frame = 1; frame <= 4; frame += 1) {
    d2::Cel_View cel_view(cel_file_wrapper.GetCel(0, frame));

    interface_bar_width += cel_view.GetWidth();
  }

  unsigned int interface_bar_height = d2::Cel_View(
      cel_file_wrapper.GetCel(0, 0)
  ).GetHeight();

  // Determine the start draw positions of the interface bar.
  const std::tuple display_width_and_height = GetResolutionFromId(
      d2::d2gfx::GetResolutionMode()
  );

  int draw_position_x =
      (std::get<0>(display_width_and_height) - interface_bar_width) / 2;

  // Draw the interface bar. Note that only frames 1 - 4 should be drawn.
  d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = mapi::RGBA32BitColor();
  frame_options.draw_effect = d2::DrawEffect::kNone;
  frame_options.position_x_behavior = d2::DrawPositionXBehavior::kLeft;
  frame_options.position_y_behavior = d2::DrawPositionYBehavior::kBottom;

  mapi::bool32 total_result = true;
  for (unsigned int frame = 1; frame <= 4; frame += 1) {
    bool result = cel_file_wrapper.DrawFrame(
        draw_position_x,
        std::get<1>(display_width_and_height),
        0,
        frame,
        frame_options
    );

    d2::Cel_View cel_view(cel_file_wrapper.GetCel(0, frame));
    draw_position_x += cel_view.GetWidth();

    total_result = total_result && result;
  }

  return total_result;
}

} // namespace sgd2fr::patches
