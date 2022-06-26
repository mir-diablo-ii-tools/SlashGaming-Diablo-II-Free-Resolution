/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2022  Mir Drualga
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

#include "position_realignment.hpp"

#include "game_resolution.hpp"

namespace sgd2fr {

void RealignPositionFromCenter(
    ::d2::PositionalRectangle_Wrapper out_position_wrapper
) {
  std::tuple current_resolution = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const std::tuple<int, int>& source_resolution =
      GetSourceInventoryArrangeResolution();

  int source_width = std::get<0>(source_resolution);
  int source_height = std::get<1>(source_resolution);

  // Set left and right values.
  int dist_from_rect_left_to_display_center = out_position_wrapper.GetLeft()
      - (source_width / 2);

  int rectangle_width = out_position_wrapper.GetRight()
      - out_position_wrapper.GetLeft();

  out_position_wrapper.SetLeft(
      (std::get<0>(current_resolution) / 2)
          + dist_from_rect_left_to_display_center
  );

  out_position_wrapper.SetRight(
      out_position_wrapper.GetLeft() + rectangle_width
  );

  // Set top and bottom values.
  int dist_from_rect_top_to_display_center = out_position_wrapper.GetTop()
      - (source_height / 2);

  int rectangle_height = out_position_wrapper.GetBottom()
      - out_position_wrapper.GetTop();

  out_position_wrapper.SetTop(
      (std::get<1>(current_resolution) / 2)
          + dist_from_rect_top_to_display_center
  );

  out_position_wrapper.SetBottom(
      out_position_wrapper.GetTop() + rectangle_height
  );
}

void RealignPositionFromBottomCenter(
    ::d2::PositionalRectangle_Wrapper out_position_wrapper
) {
  std::tuple current_resolution = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const std::tuple<int, int>& source_resolution =
      GetSourceInventoryArrangeResolution();

  int source_width = std::get<0>(source_resolution);
  int source_height = std::get<1>(source_resolution);

  // Set left and right values.
  int dist_from_rect_left_to_display_center = out_position_wrapper.GetLeft()
      - (source_width / 2);

  int rectangle_width = out_position_wrapper.GetRight()
      - out_position_wrapper.GetLeft();

  out_position_wrapper.SetLeft(
      (std::get<0>(current_resolution) / 2)
          + dist_from_rect_left_to_display_center
  );

  out_position_wrapper.SetRight(
      out_position_wrapper.GetLeft() + rectangle_width
  );

  // Set top and bottom values.
  int dist_from_rect_top_to_display_bottom = 
      source_height - out_position_wrapper.GetTop();

  int rectangle_height = out_position_wrapper.GetBottom()
      - out_position_wrapper.GetTop();

  out_position_wrapper.SetTop(
      std::get<1>(current_resolution)
          - dist_from_rect_top_to_display_bottom
  );

  out_position_wrapper.SetBottom(
      out_position_wrapper.GetTop() + rectangle_height
  );
}

} // namespace sgd2fr

