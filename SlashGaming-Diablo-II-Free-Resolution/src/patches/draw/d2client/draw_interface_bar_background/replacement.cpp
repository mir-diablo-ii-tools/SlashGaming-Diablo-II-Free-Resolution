/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2024  Mir Drualga
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

#include "replacement.hpp"

#include <sgd2mapi.hpp>
#include "../../../../config.hpp"
#include "../../../../helper/cel_file_collection.hpp"
#include "../../../../helper/game_resolution.hpp"

namespace sgd2fr {
namespace {

static void DrawAntiCheatBlackRectangle() {
  static constexpr int interface_bar_height = 47;

  Resolution resolution =
      GetIngameResolutionFromId(::d2::d2gfx::GetResolutionMode());

  // Draw a black rectangle to stop transparent DC6 cheaters.
  ::d2::d2gfx::DrawRectangle(
      0,
      resolution.height - interface_bar_height,
      resolution.width,
      resolution.height,
      0,
      ::d2::DrawEffect::kNone);
}

static void DrawLeftInterfaceBarBackground() {
  Resolution resolution =
      GetIngameResolutionFromId(::d2::d2gfx::GetResolutionMode());

  ::d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = ::mapi::Rgba32BitColor();
  frame_options.draw_effect = ::d2::DrawEffect::kNone;
  frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  int width_covered = 117 + 48;

  // Draw the left part of the interface bar background.
  ::d2::CelFile_Api& interface_bar_background_left =
      GetCelFile(config::GetInterfaceBarBackgroundLeftImagePath());

  for (unsigned int frame = 0;
      frame < interface_bar_background_left.GetNumFrames()
          && width_covered < (resolution.width / 2);
      frame += 1) {
    interface_bar_background_left.DrawFrame(
        width_covered,
        resolution.height - 1,
        0,
        frame,
        frame_options);

    width_covered += interface_bar_background_left
        .GetCel(0, frame)
        .GetWidth();
  }

  // Draw the center part of the interface bar background.
  ::d2::CelFile_Api& interface_bar_background_center =
      GetCelFile(config::GetInterfaceBarBackgroundCenterImagePath());

  std::vector<d2::Cel_View> center_cels;
  for (unsigned int i = 0;
      i < interface_bar_background_center.GetNumFrames();
      i += 1) {
    center_cels.push_back(interface_bar_background_center.GetCel(0, i));
  }

  for (unsigned int frame = 0;
      width_covered < (resolution.width / 2);
      frame += 1) {
    unsigned int frame_to_draw =
        frame % interface_bar_background_center.GetNumFrames();

    interface_bar_background_center.DrawFrame(
        width_covered,
        resolution.height - 1,
        0,
        frame_to_draw,
        frame_options);

    width_covered += center_cels.at(frame_to_draw).GetWidth();
  }
}

static void DrawRightInterfaceBarBackground() {
  Resolution resolution =
      GetIngameResolutionFromId(::d2::d2gfx::GetResolutionMode());

  ::d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = ::mapi::Rgba32BitColor();
  frame_options.draw_effect = ::d2::DrawEffect::kNone;
  frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  int width_covered = 117 + 48;

  // Draw the left part of the interface bar background.
  ::d2::CelFile_Api& interface_bar_background_right =
      GetCelFile(config::GetInterfaceBarBackgroundRightImagePath());

  for (unsigned int frame = 0;
      frame < interface_bar_background_right.GetNumFrames()
          && width_covered < (resolution.width / 2);
      frame += 1) {
    interface_bar_background_right.DrawFrame(
        resolution.width - width_covered,
        resolution.height - 1,
        0,
        frame,
        frame_options);

    width_covered += interface_bar_background_right
        .GetCel(0, frame)
        .GetWidth();
  }

  // Draw the center part of the interface bar background.
  ::d2::CelFile_Api& interface_bar_background_center =
      GetCelFile(config::GetInterfaceBarBackgroundCenterImagePath());

  std::vector<d2::Cel_View> center_cels;
  for (unsigned int frame = 0;
      frame < interface_bar_background_center.GetNumFrames();
      frame += 1) {
    center_cels.push_back(interface_bar_background_center.GetCel(0, frame));
  }

  for (unsigned int frame = 0;
      width_covered < (resolution.width / 2);
      frame += 1) {
    unsigned int frame_to_draw =
        frame % interface_bar_background_center.GetNumFrames();

    interface_bar_background_center.DrawFrame(
        resolution.width - width_covered,
        resolution.height - 1,
        0,
        frame_to_draw,
        frame_options);

    width_covered += center_cels.at(frame_to_draw).GetWidth();
  }
}

} // namespace

void __cdecl Sgd2fr_D2Client_DrawInterfaceBarBackground() {
  DrawAntiCheatBlackRectangle();
  DrawLeftInterfaceBarBackground();
  DrawRightInterfaceBarBackground();
}

} // namespace sgd2fr
