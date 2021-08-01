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

#include "d2client_draw_interface_bar_background.hpp"

#include <sgd2mapi.hpp>
#include "../../../config.hpp"
#include "../../../cel_file/cel_file_interface_bar_background.h"
#include "../../../game_resolution/game_resolution.hpp"

namespace sgd2fr {
namespace {

static void DrawAntiCheatBlackRectangle() {
  static constexpr int interface_bar_height = 47;

  GameResolution width_and_height = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  // Draw a black rectangle to stop transparent DC6 cheaters.
  ::d2::d2gfx::DrawRectangle(
      0,
      width_and_height.height - interface_bar_height,
      width_and_height.width,
      width_and_height.height,
      0,
      ::d2::DrawEffect::kNone
  );
}

static void DrawLeftInterfaceBarBackground() {
  GameResolution width_and_height = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const int left_start = 117 + 48;
  int width_covered = 0;

  // Draw the left part of the interface bar background.
  ::d2::CelFile_Wrapper interface_bar_background_left =
      CelFile_InterfaceBarBackground_GetLeft();

  for (size_t frame_index = 0;
      frame_index < interface_bar_background_left.GetNumFrames();
      frame_index += 1
  ) {
    if ((left_start + width_covered) > (width_and_height.width / 2)) {
      break;
    }

    ::d2::Cel_Wrapper cel = interface_bar_background_left.GetCel(
        0,
        frame_index
    );

    interface_bar_background_left.DrawFrame(
        left_start + width_covered,
        width_and_height.height,
        0,
        frame_index
    );

    width_covered += cel.GetWidth();
  }

  // Draw the center part of the interface bar background.
  ::d2::CelFile_Wrapper interface_bar_background_center =
      CelFile_InterfaceBarBackground_GetCenter();

  for (size_t frame_index = 0;
      (left_start + width_covered) < (width_and_height.width / 2);
      frame_index += 1) {
    frame_index %= interface_bar_background_center.GetNumFrames();

    ::d2::Cel_Wrapper cel = interface_bar_background_center.GetCel(
        0,
        frame_index
    );

    interface_bar_background_center.DrawFrame(
        left_start + width_covered,
        width_and_height.height,
        0,
        frame_index
    );

    width_covered += cel.GetWidth();
  }
}

static void DrawRightInterfaceBarBackground() {
  GameResolution width_and_height = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const int right_start = width_and_height.width - (117 + 48);
  int width_covered = 0;

  // Draw the left part of the interface bar background.
  ::d2::CelFile_Wrapper interface_bar_background_right =
      CelFile_InterfaceBarBackground_GetRight();

  for (size_t frame_index = 0;
      frame_index < interface_bar_background_right.GetNumFrames();
      frame_index += 1) {
    if ((right_start - width_covered) < (width_and_height.width / 2)) {
      break;
    }

    ::d2::Cel_Wrapper cel = interface_bar_background_right.GetCel(
        0,
        frame_index
    );

    interface_bar_background_right.DrawFrame(
        right_start - width_covered - cel.GetWidth(),
        width_and_height.height,
        0,
        frame_index
    );

    width_covered += cel.GetWidth();
  }

  // Draw the center part of the interface bar background.
  ::d2::CelFile_Wrapper interface_bar_background_center =
      CelFile_InterfaceBarBackground_GetCenter();

  for (size_t frame_index = 0;
      (right_start - width_covered) > (width_and_height.width / 2);
      frame_index += 1
  ) {
    frame_index %= interface_bar_background_center.GetNumFrames();

    ::d2::Cel_Wrapper cel = interface_bar_background_center.GetCel(
        0,
        frame_index
    );

    interface_bar_background_center.DrawFrame(
        right_start - width_covered - cel.GetWidth(),
        width_and_height.height,
        0,
        frame_index
    );

    width_covered += cel.GetWidth();
  }
}

} // namespace

void __cdecl Sgd2fr_D2Client_DrawInterfaceBarBackground() {
  DrawAntiCheatBlackRectangle();
  DrawLeftInterfaceBarBackground();
  DrawRightInterfaceBarBackground();
}

} // namespace sgd2fr
