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

#include "d2client_draw_screen_background.hpp"

#include <windows.h>

#include <mdc/error/exit_on_error.hpp>
#include <mdc/wchar_t/filew.h>
#include <sgd2mapi.hpp>
#include "../../../config.hpp"
#include "../../../helper/cel_file_collection.hpp"
#include "../../../helper/game_resolution.hpp"
#include "../../../sgd2mapi_extension/sgd2mapi_extension.hpp"

namespace sgd2fr {
namespace {

constexpr std::string_view kOriginalScreenBorderFrameImagePath =
    "data\\global\\UI\\Panel\\800BorderFrame";

void DrawLeftScreenBackground() {
  ::d2::CelFile_Api& screen_background = GetCelFile(config::GetScreenBackgroundImagePath());

  std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  // Draw a black rectangle to stop transparent DC6 cheaters.
  ::d2::d2gfx::DrawRectangle(
      0,
      0,
      std::get<0>(width_and_height) / 2,
      std::get<1>(width_and_height),
      0,
      ::d2::DrawEffect::kNone
  );

  // Set up the frame options.
  ::d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = ::mapi::Rgba32BitColor();
  frame_options.draw_effect = ::d2::DrawEffect::kNone;
  frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  // Store an array of Cel_Views to determine Cel Width and Heights.
  std::vector<d2::Cel_View> cels;
  for (unsigned int i = 0; i < screen_background.GetNumFrames(); i += 1) {
    cels.push_back(d2::Cel_View(screen_background.GetCel(0, i)));
  }

  // Draw the background.
  const unsigned int half_num_frames = screen_background.GetNumFrames() / 2;

  int height_covered = 0;
  for (unsigned int row = 0; height_covered < std::get<0>(width_and_height); row += 1) {
    int width_covered = 0;
    unsigned int row_start_frame = (row % 2) * half_num_frames;

    for (unsigned int col = 0; width_covered < ((std::get<0>(width_and_height) / 2) - 1); col += 1) {
      unsigned int current_frame = row_start_frame + ((half_num_frames - 1) - (col % half_num_frames));

      screen_background.DrawFrame(
          (std::get<0>(width_and_height) / 2) - width_covered + cels.at(current_frame).GetOffsetX(),
          height_covered + cels.at(current_frame).GetOffsetY(),
          0,
          current_frame,
          frame_options
      );

      width_covered += cels.at(current_frame).GetWidth();
    }

    height_covered += cels.at(row_start_frame).GetHeight();
  }
}

void DrawRightScreenBackground() {
  ::d2::CelFile_Api& screen_background = GetCelFile(config::GetScreenBackgroundImagePath());

  std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  // Draw a black rectangle to stop transparent DC6 cheaters.
  ::d2::d2gfx::DrawRectangle(
      std::get<0>(width_and_height) / 2,
      0,
      std::get<0>(width_and_height),
      std::get<1>(width_and_height),
      0,
      ::d2::DrawEffect::kNone
  );

  // Set up the frame options.
  ::d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = ::mapi::Rgba32BitColor();
  frame_options.draw_effect = ::d2::DrawEffect::kNone;
  frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  // Store an array of Cel_Views to determine Cel Width and Heights.
  std::vector<d2::Cel_View> cels;
  for (unsigned int i = 0; i < screen_background.GetNumFrames(); i += 1) {
    cels.push_back(d2::Cel_View(screen_background.GetCel(0, i)));
  }

  // Draw the background.
  const unsigned int half_num_frames = screen_background.GetNumFrames() / 2;

  int height_covered = 0;
  for (unsigned int row = 0; height_covered < std::get<0>(width_and_height); row += 1) {
    int width_covered = 0;
    unsigned int row_start_frame = (row % 2) * half_num_frames;

    for (unsigned int col = 0; width_covered < ((std::get<0>(width_and_height) / 2) - 1); col += 1) {
      unsigned int current_frame = row_start_frame + (col % half_num_frames);

      screen_background.DrawFrame(
          (std::get<0>(width_and_height) / 2) + width_covered + cels.at(current_frame).GetOffsetX(),
          height_covered + cels.at(current_frame).GetOffsetY(),
          0,
          current_frame,
          frame_options
      );

      width_covered += cels.at(current_frame).GetWidth();
    }

    height_covered += cels.at(row_start_frame).GetHeight();
  }
}

/**
 * Drawing the original screen border frame requires significantly
 * different code due to its abnormal structure.
 */
void DrawOriginalLeftScreenBorderFrame() {
  ::d2::CelFile_Api& screen_border_frame = GetCelFile(kOriginalScreenBorderFrameImagePath);

  std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  const int left = (std::get<0>(width_and_height) - 640 - (800 - 640)) / 2;
  const int top = ((std::get<1>(width_and_height) - 480 - (600 - 480)) / 2) - 3;

  std::vector<d2::Cel_View> cels;
  for (unsigned int i = 0; i < screen_border_frame.GetNumFrames(); i += 1) {
    cels.push_back(screen_border_frame.GetCel(0, i));
  }

  ::d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = ::mapi::Rgba32BitColor();
  frame_options.draw_effect = ::d2::DrawEffect::kNone;
  frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_border_frame.DrawFrame(left, top, 0, 0, frame_options);

  screen_border_frame.DrawFrame(
      left + cels.at(0).GetWidth(),
      top,
      0,
      1,
      frame_options
  );

  screen_border_frame.DrawFrame(
      left,
      top + cels.at(0).GetHeight(),
      0,
      2,
      frame_options
  );

  screen_border_frame.DrawFrame(
      left,
      top + cels.at(0).GetHeight() + cels.at(2).GetHeight(),
      0,
      3,
      frame_options
  );

  screen_border_frame.DrawFrame(
      left + cels.at(3).GetWidth(),
      top + cels.at(0).GetHeight() + cels.at(2).GetHeight(),
      0,
      4,
      frame_options
  );
}

void DrawOriginalRightScreenBorderFrame() {
  ::d2::CelFile_Api& screen_border_frame = GetCelFile(kOriginalScreenBorderFrameImagePath);

  std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  const int right = (std::get<0>(width_and_height) + 640 + (800 - 640)) / 2;
  const int top = ((std::get<1>(width_and_height) - 480 - (600 - 480)) / 2) - 3;

  std::vector<d2::Cel_View> cels;
  for (unsigned int i = 0; i < screen_border_frame.GetNumFrames(); i += 1) {
    cels.push_back(screen_border_frame.GetCel(0, i));
  }

  ::d2::DrawCelFileFrameOptions frame_options;
  frame_options.color = ::mapi::Rgba32BitColor();
  frame_options.draw_effect = ::d2::DrawEffect::kNone;
  frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_border_frame.DrawFrame(right, top, 0, 6, frame_options);

  screen_border_frame.DrawFrame(
      right - cels.at(6).GetWidth(),
      top,
      0,
      5,
      frame_options
  );

  screen_border_frame.DrawFrame(
      right,
      top + cels.at(6).GetHeight(),
      0,
      7,
      frame_options
  );

  screen_border_frame.DrawFrame(
      right,
      top + cels.at(6).GetHeight() + cels.at(7).GetHeight(),
      0,
      8,
      frame_options
  );

  screen_border_frame.DrawFrame(
      right - cels.at(8).GetWidth(),
      top + cels.at(6).GetHeight() + cels.at(7).GetHeight(),
      0,
      9,
      frame_options
  );
}

void DrawCustomLeftScreenBorderFrame() {
  ::d2::CelFile_Api& screen_left_border = GetCelFile(config::GetCustomLeftScreenBorderLeftImagePath());
  ::d2::CelFile_Api& screen_top_border = GetCelFile(config::GetCustomLeftScreenBorderTopImagePath());
  ::d2::CelFile_Api& screen_top_right_border = GetCelFile(config::GetCustomLeftScreenBorderTopRightImagePath());
  ::d2::CelFile_Api& screen_bottom_border = GetCelFile(config::GetCustomLeftScreenBorderBottomImagePath());
  ::d2::CelFile_Api& screen_bottom_right_border = GetCelFile(config::GetCustomLeftScreenBorderBottomRightImagePath());

  const std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  // Determine border starting positions.
  const int screen_left = (std::get<0>(width_and_height) - 640) / 2;
  const int screen_top = (std::get<1>(width_and_height) - 480) / 2;

  int screen_left_border_height = 0;

  for (unsigned int frame = 0; frame < screen_left_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_left_border.GetCel(0, frame);
    screen_left_border_height += cel_view.GetHeight();
  }

  const int border_top = screen_top + (((256 + 176) - screen_left_border_height) / 2);
  const int border_bottom = screen_top + (((256 + 176) + screen_left_border_height) / 2);

  // Draw the left screen's top right border.
  int screen_top_right_border_width = 0;

  for (unsigned int frame = 0; frame < screen_top_right_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_top_right_border.GetCel(0, frame);
    screen_top_right_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_top_right_all_frame_options;
  screen_top_right_all_frame_options.cel_file_direction = 0;
  screen_top_right_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_right_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_right_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_top_right_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_top_right_border.DrawAllFrames(
      std::get<0>(width_and_height) / 2,
      border_top,
      screen_top_right_border.GetNumFrames(),
      1,
      screen_top_right_all_frame_options
  );

  // Draw the left screen's top border.
  int screen_top_border_width = 0;

  for (unsigned int frame = 0; frame < screen_top_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_top_border.GetCel(0, frame);
    screen_top_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_top_all_frame_options;
  screen_top_all_frame_options.cel_file_direction = 0;
  screen_top_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_top_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_top_border.DrawAllFrames(
      (std::get<0>(width_and_height) / 2) - screen_top_right_border_width,
      border_top,
      screen_top_border.GetNumFrames(),
      1,
      screen_top_all_frame_options
  );

  // Draw the left screen's bottom right border.
  int screen_bottom_right_border_width = 0;

  for (unsigned int frame = 0; frame < screen_bottom_right_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_bottom_right_border.GetCel(0, frame);
    screen_bottom_right_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_bottom_right_all_frame_options;
  screen_bottom_right_all_frame_options.cel_file_direction = 0;
  screen_bottom_right_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_right_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_right_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_bottom_right_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  screen_bottom_right_border.DrawAllFrames(
      std::get<0>(width_and_height) / 2,
      border_bottom,
      screen_bottom_right_border.GetNumFrames(),
      1,
      screen_bottom_right_all_frame_options
  );

  // Draw the left screen's bottom border.
  int screen_bottom_border_width = 0;

  for (unsigned int frame = 0; frame < screen_bottom_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_bottom_border.GetCel(0, frame);
    screen_bottom_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_bottom_all_frame_options;
  screen_bottom_all_frame_options.cel_file_direction = 0;
  screen_bottom_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_bottom_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  screen_bottom_border.DrawAllFrames(
      (std::get<0>(width_and_height) / 2) - screen_bottom_right_border_width,
      border_bottom,
      screen_bottom_border.GetNumFrames(),
      1,
      screen_bottom_all_frame_options
  );

  // Draw the left screen's left border.
  ::d2::DrawAllCelFileFramesOptions screen_left_all_frame_options;
  screen_left_all_frame_options.cel_file_direction = 0;
  screen_left_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_left_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_left_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_left_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_left_border.DrawAllFrames(
      (std::get<0>(width_and_height) - 640) / 2,
      border_top,
      1,
      screen_left_border.GetNumFrames(),
      screen_left_all_frame_options
  );
}

void DrawCustomRightScreenBorderFrame() {
  ::d2::CelFile_Api& screen_right_border = GetCelFile(config::GetCustomRightScreenBorderRightImagePath());
  ::d2::CelFile_Api& screen_top_border = GetCelFile(config::GetCustomRightScreenBorderTopImagePath());
  ::d2::CelFile_Api& screen_top_left_border = GetCelFile(config::GetCustomRightScreenBorderTopLeftImagePath());
  ::d2::CelFile_Api& screen_bottom_border = GetCelFile(config::GetCustomRightScreenBorderBottomImagePath());
  ::d2::CelFile_Api& screen_bottom_left_border = GetCelFile(config::GetCustomRightScreenBorderBottomLeftImagePath());

  const std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  // Determine border starting positions.
  const int screen_right = (std::get<0>(width_and_height) + 640) / 2;
  const int screen_top = (std::get<1>(width_and_height) - 480) / 2;

  int screen_right_border_height = 0;

  for (unsigned int frame = 0; frame < screen_right_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_right_border.GetCel(0, frame);
    screen_right_border_height += cel_view.GetHeight();
  }

  const int border_top = screen_top + (((256 + 176) - screen_right_border_height) / 2);
  const int border_bottom = screen_top + (((256 + 176) + screen_right_border_height) / 2);

  // Draw the right screen's top left border.
  int screen_top_left_border_width = 0;

  for (unsigned int frame = 0; frame < screen_top_left_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_top_left_border.GetCel(0, frame);
    screen_top_left_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_top_left_all_frame_options;
  screen_top_left_all_frame_options.cel_file_direction = 0;
  screen_top_left_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_left_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_left_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_top_left_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_top_left_border.DrawAllFrames(
      std::get<0>(width_and_height) / 2,
      border_top,
      screen_top_left_border.GetNumFrames(),
      1,
      screen_top_left_all_frame_options
  );

  // Draw the right screen's top border.
  int screen_top_border_width = 0;

  for (unsigned int frame = 0; frame < screen_top_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_top_border.GetCel(0, frame);
    screen_top_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_top_all_frame_options;
  screen_top_all_frame_options.cel_file_direction = 0;
  screen_top_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_top_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_top_border.DrawAllFrames(
      (std::get<0>(width_and_height) / 2) + screen_top_left_border_width,
      border_top,
      screen_top_border.GetNumFrames(),
      1,
      screen_top_all_frame_options
  );

  // Draw the right screen's bottom left border.
  int screen_bottom_left_border_width = 0;

  for (unsigned int frame = 0; frame < screen_bottom_left_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_bottom_left_border.GetCel(0, frame);
    screen_bottom_left_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_bottom_left_all_frame_options;
  screen_bottom_left_all_frame_options.cel_file_direction = 0;
  screen_bottom_left_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_left_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_left_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_bottom_left_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  screen_bottom_left_border.DrawAllFrames(
      std::get<0>(width_and_height) / 2,
      border_bottom,
      screen_bottom_left_border.GetNumFrames(),
      1,
      screen_bottom_left_all_frame_options
  );

  // Draw the right screen's bottom border.
  int screen_bottom_border_width = 0;

  for (unsigned int frame = 0; frame < screen_bottom_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_bottom_border.GetCel(0, frame);
    screen_bottom_border_width += cel_view.GetWidth();
  }

  ::d2::DrawAllCelFileFramesOptions screen_bottom_all_frame_options;
  screen_bottom_all_frame_options.cel_file_direction = 0;
  screen_bottom_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_bottom_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  screen_bottom_border.DrawAllFrames(
      (std::get<0>(width_and_height) / 2) + screen_bottom_left_border_width,
      border_bottom,
      screen_bottom_border.GetNumFrames(),
      1,
      screen_bottom_all_frame_options
  );

  // Draw the right screen's right border.
  ::d2::DrawAllCelFileFramesOptions screen_right_all_frame_options;
  screen_right_all_frame_options.cel_file_direction = 0;
  screen_right_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_right_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_right_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_right_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  screen_right_border.DrawAllFrames(
      screen_right,
      border_top,
      1,
      screen_right_border.GetNumFrames(),
      screen_right_all_frame_options
  );
}

void DrawLeftScreenBorderFrame() {
  if (!config::IsScreenBorderFrameEnabled()) {
    return;
  }

  if (config::IsUseOriginalScreenBorderFrame()) {
    DrawOriginalLeftScreenBorderFrame();
  } else {
    DrawCustomLeftScreenBorderFrame();
  }
}

void DrawRightScreenBorderFrame() {
  if (!config::IsScreenBorderFrameEnabled()) {
    return;
  }

  if (config::IsUseOriginalScreenBorderFrame()) {
    DrawOriginalRightScreenBorderFrame();
  } else {
    DrawCustomRightScreenBorderFrame();
  }
}

void DrawLeftScreenBackgroundRibbon() {
  ::d2::CelFile_Api& screen_border_horizontal_ribbon = GetCelFile(config::GetScreenBorderHorizontalRibbonImagePath());
  ::d2::CelFile_Api& screen_border_vertical_ribbon = GetCelFile(config::GetScreenBorderVerticalRibbonImagePath());

  ::d2::CelFile_Api& screen_left_border = GetCelFile(config::GetCustomLeftScreenBorderLeftImagePath());

  // Determine border starting positions.
  const std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  const int screen_left = (std::get<0>(width_and_height) - 640) / 2;
  const int screen_right = std::get<0>(width_and_height) / 2;
  const int screen_top = (std::get<1>(width_and_height) - 480) / 2;

  int screen_left_border_height = 0;

  for (unsigned int frame = 0; frame < screen_left_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_left_border.GetCel(0, frame);
    screen_left_border_height += cel_view.GetHeight();
  }

  const int border_top = screen_top + (((256 + 176) - screen_left_border_height) / 2);
  const int border_left = screen_left - ::d2::Cel_View(screen_left_border.GetCel(0, 0)).GetWidth();
  const int border_bottom = screen_top + (((256 + 176) + screen_left_border_height) / 2);

  // Draw horizontal bars.
  ::d2::DrawAllCelFileFramesOptions screen_top_horizontal_ribbon_all_frame_options;
  screen_top_horizontal_ribbon_all_frame_options.cel_file_direction = 0;
  screen_top_horizontal_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_horizontal_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_horizontal_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_top_horizontal_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  ::d2::DrawAllCelFileFramesOptions screen_bottom_horizontal_ribbon_all_frame_options;
  screen_bottom_horizontal_ribbon_all_frame_options.cel_file_direction = 0;
  screen_bottom_horizontal_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_horizontal_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_horizontal_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_bottom_horizontal_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  int screen_border_horizontal_ribbon_width = 0;
  for (unsigned int frame = 0; frame < screen_border_horizontal_ribbon.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_border_horizontal_ribbon.GetCel(0, frame);

    screen_border_horizontal_ribbon_width += cel_view.GetWidth();
  }

  int width_covered = 0;

  while (width_covered < border_left) {
    screen_border_horizontal_ribbon.DrawAllFrames(
        border_left - width_covered,
        border_top,
        screen_border_horizontal_ribbon.GetNumFrames(),
        1,
        screen_top_horizontal_ribbon_all_frame_options
    );

    screen_border_horizontal_ribbon.DrawAllFrames(
        border_left - width_covered,
        border_bottom,
        screen_border_horizontal_ribbon.GetNumFrames(),
        1,
        screen_bottom_horizontal_ribbon_all_frame_options
    );

    width_covered += screen_border_horizontal_ribbon_width;
  }

  // Draw top vertical bars.
  ::d2::DrawAllCelFileFramesOptions screen_top_left_vertical_ribbon_all_frame_options;
  screen_top_left_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_top_left_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_left_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_left_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_top_left_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  ::d2::DrawAllCelFileFramesOptions screen_top_right_vertical_ribbon_all_frame_options;
  screen_top_right_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_top_right_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_right_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_right_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_top_right_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  int screen_border_vertical_ribbon_height = 0;
  for (unsigned int frame = 0; frame < screen_border_vertical_ribbon.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_border_vertical_ribbon.GetCel(0, frame);

    screen_border_vertical_ribbon_height += cel_view.GetHeight();
  }

  int top_height_covered = 0;

  while (top_height_covered < border_top) {
    screen_border_vertical_ribbon.DrawAllFrames(
        border_left,
        border_top - top_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_top_left_vertical_ribbon_all_frame_options
    );

    screen_border_vertical_ribbon.DrawAllFrames(
        screen_right,
        border_top - top_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_top_right_vertical_ribbon_all_frame_options
    );

    top_height_covered += screen_border_vertical_ribbon_height;
  }

  // Draw bottom vertical bars.
  ::d2::DrawAllCelFileFramesOptions screen_bottom_left_vertical_ribbon_all_frame_options;
  screen_bottom_left_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_bottom_left_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_left_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_left_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_bottom_left_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  ::d2::DrawAllCelFileFramesOptions screen_bottom_right_vertical_ribbon_all_frame_options;
  screen_bottom_right_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_bottom_right_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_right_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_right_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_bottom_right_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  int bottom_height_covered = 0;

  while (bottom_height_covered < border_top) {
    screen_border_vertical_ribbon.DrawAllFrames(
        border_left,
        border_bottom + bottom_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_bottom_left_vertical_ribbon_all_frame_options
    );

    screen_border_vertical_ribbon.DrawAllFrames(
        screen_right,
        border_bottom + bottom_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_bottom_right_vertical_ribbon_all_frame_options
    );

    bottom_height_covered += screen_border_vertical_ribbon_height;
  }
}

void DrawRightScreenBackgroundRibbon() {
  ::d2::CelFile_Api& screen_border_horizontal_ribbon = GetCelFile(config::GetScreenBorderHorizontalRibbonImagePath());
  ::d2::CelFile_Api& screen_border_vertical_ribbon = GetCelFile(config::GetScreenBorderVerticalRibbonImagePath());

  ::d2::CelFile_Api& screen_right_border = GetCelFile(config::GetCustomRightScreenBorderRightImagePath());

  // Determine border starting positions.
  const std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  const int screen_left = std::get<0>(width_and_height) / 2;
  const int screen_right = (std::get<0>(width_and_height) + 640) / 2;
  const int screen_top = (std::get<1>(width_and_height) - 480) / 2;

  int screen_right_border_height = 0;

  for (unsigned int frame = 0; frame < screen_right_border.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_right_border.GetCel(0, frame);
    screen_right_border_height += cel_view.GetHeight();
  }

  const int border_top = screen_top + (((256 + 176) - screen_right_border_height) / 2);
  const int border_right = screen_right + ::d2::Cel_View(screen_right_border.GetCel(0, 0)).GetWidth();
  const int border_bottom = border_top + screen_right_border_height;

  // Draw horizontal bars.
  ::d2::DrawAllCelFileFramesOptions screen_top_horizontal_ribbon_all_frame_options;
  screen_top_horizontal_ribbon_all_frame_options.cel_file_direction = 0;
  screen_top_horizontal_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_horizontal_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_horizontal_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_top_horizontal_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  ::d2::DrawAllCelFileFramesOptions screen_bottom_horizontal_ribbon_all_frame_options;
  screen_bottom_horizontal_ribbon_all_frame_options.cel_file_direction = 0;
  screen_bottom_horizontal_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_horizontal_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_horizontal_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_bottom_horizontal_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  int screen_border_horizontal_ribbon_width = 0;
  for (unsigned int frame = 0; frame < screen_border_horizontal_ribbon.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_border_horizontal_ribbon.GetCel(0, frame);

    screen_border_horizontal_ribbon_width += cel_view.GetWidth();
  }

  int width_covered = 0;

  while (width_covered < (std::get<0>(width_and_height) - border_right)) {
    screen_border_horizontal_ribbon.DrawAllFrames(
        border_right + width_covered,
        border_top,
        screen_border_horizontal_ribbon.GetNumFrames(),
        1,
        screen_top_horizontal_ribbon_all_frame_options
    );

    screen_border_horizontal_ribbon.DrawAllFrames(
        border_right + width_covered,
        border_bottom,
        screen_border_horizontal_ribbon.GetNumFrames(),
        1,
        screen_bottom_horizontal_ribbon_all_frame_options
    );

    width_covered += screen_border_horizontal_ribbon_width;
  }

  // Draw top vertical bars.
  ::d2::DrawAllCelFileFramesOptions screen_top_left_vertical_ribbon_all_frame_options;
  screen_top_left_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_top_left_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_left_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_left_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_top_left_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  ::d2::DrawAllCelFileFramesOptions screen_top_right_vertical_ribbon_all_frame_options;
  screen_top_right_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_top_right_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_top_right_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_top_right_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_top_right_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kBottom;

  int screen_border_vertical_ribbon_height = 0;
  for (unsigned int frame = 0; frame < screen_border_vertical_ribbon.GetNumFrames(); frame += 1) {
    ::d2::Cel_View cel_view = screen_border_vertical_ribbon.GetCel(0, frame);

    screen_border_vertical_ribbon_height += cel_view.GetHeight();
  }

  int top_height_covered = 0;

  while (top_height_covered < border_top) {
    screen_border_vertical_ribbon.DrawAllFrames(
        screen_left,
        border_top - top_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_top_left_vertical_ribbon_all_frame_options
    );

    screen_border_vertical_ribbon.DrawAllFrames(
        border_right,
        border_top - top_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_top_right_vertical_ribbon_all_frame_options
    );

    top_height_covered += screen_border_vertical_ribbon_height;
  }

  // Draw bottom vertical bars.
  ::d2::DrawAllCelFileFramesOptions screen_bottom_left_vertical_ribbon_all_frame_options;
  screen_bottom_left_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_bottom_left_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_left_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_left_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kLeft;
  screen_bottom_left_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  ::d2::DrawAllCelFileFramesOptions screen_bottom_right_vertical_ribbon_all_frame_options;
  screen_bottom_right_vertical_ribbon_all_frame_options.cel_file_direction = 0;
  screen_bottom_right_vertical_ribbon_all_frame_options.color = ::mapi::Rgba32BitColor();
  screen_bottom_right_vertical_ribbon_all_frame_options.draw_effect = ::d2::DrawEffect::kNone;
  screen_bottom_right_vertical_ribbon_all_frame_options.position_x_behavior = ::d2::DrawPositionXBehavior::kRight;
  screen_bottom_right_vertical_ribbon_all_frame_options.position_y_behavior = ::d2::DrawPositionYBehavior::kTop;

  int bottom_height_covered = 0;

  while (bottom_height_covered < border_top) {
    screen_border_vertical_ribbon.DrawAllFrames(
        screen_left,
        border_bottom + bottom_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_bottom_left_vertical_ribbon_all_frame_options
    );

    screen_border_vertical_ribbon.DrawAllFrames(
        border_right,
        border_bottom + bottom_height_covered,
        1,
        screen_border_vertical_ribbon.GetNumFrames(),
        screen_bottom_right_vertical_ribbon_all_frame_options
    );

    bottom_height_covered += screen_border_vertical_ribbon_height;
  }
}

} // namespace

void Sgd2fr_D2Client_DrawScreenBackground() {
  ::d2::ScreenOpenMode screen_open_mode =
      ::d2::d2client::GetScreenOpenMode();

  switch (screen_open_mode) {
    case ::d2::ScreenOpenMode::kNone: {
      break;
    }

    case ::d2::ScreenOpenMode::kRight: {
      DrawRightScreenBackground();
      DrawRightScreenBorderFrame();
      DrawRightScreenBackgroundRibbon();

      break;
    }

    case ::d2::ScreenOpenMode::kLeft: {
      DrawLeftScreenBackground();
      DrawLeftScreenBorderFrame();
      DrawLeftScreenBackgroundRibbon();

      break;
    }

    case ::d2::ScreenOpenMode::kBoth: {
      DrawLeftScreenBackground();
      DrawLeftScreenBorderFrame();
      DrawLeftScreenBackgroundRibbon();

      DrawRightScreenBackground();
      DrawRightScreenBorderFrame();
      DrawRightScreenBackgroundRibbon();

      break;
    }

    default: {
      ::mdc::error::ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          static_cast<int>(screen_open_mode)
      );
    }
  }

  // Original code
  ::d2::d2client::DrawScreens();
}

} // namespace sgd2fr
