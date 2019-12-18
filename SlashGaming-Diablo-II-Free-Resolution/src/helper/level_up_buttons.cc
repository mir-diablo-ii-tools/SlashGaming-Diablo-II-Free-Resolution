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

#include "level_up_buttons.hpp"

#include <sgd2mapi.hpp>
#include "get_resolution_from_id.hpp"

namespace sgd2fr {
namespace {

constexpr int source_display_width = 800;
constexpr int source_display_height = 600;

} // namespace

d2::PositionalRectangle_API GetNewStatsButtonPosition() {
  constexpr int dist_from_left_to_display_center =
      (source_display_width / 2) - 206;
  constexpr int dist_from_right_to_display_center =
      (source_display_width / 2) - 240;
  constexpr int dist_from_top_to_display_bottom = 42;
  constexpr int dist_from_bottom_to_display_bottom = 8;

  const std::tuple display_width_and_height = GetResolutionFromId(
      d2::d2gfx::GetResolutionMode()
  );

  const int display_half_width = (std::get<0>(display_width_and_height) / 2);
  const int display_height = std::get<1>(display_width_and_height);

  d2::PositionalRectangle_API button_position(
      display_half_width - dist_from_left_to_display_center,
      display_half_width - dist_from_right_to_display_center,
      display_height - dist_from_top_to_display_bottom,
      display_height - dist_from_bottom_to_display_bottom
  );

  return button_position;
}

std::tuple<int, int> GetNewStatsPopupTextPosition() {
  constexpr int dist_from_left_to_display_center =
      (source_display_width / 2) - 221;
  constexpr int dist_from_top_to_display_bottom =
      (source_display_height) - 550;

  const std::tuple display_width_and_height = GetResolutionFromId(
      d2::d2gfx::GetResolutionMode()
  );

  const int display_half_width = (std::get<0>(display_width_and_height) / 2);
  const int display_height = std::get<1>(display_width_and_height);

  return std::make_tuple(
      display_half_width - dist_from_left_to_display_center,
      display_height - dist_from_top_to_display_bottom
  );
}

bool IsMouseOverNewStatsButton() {
  d2::PositionalRectangle_API button_position = GetNewStatsButtonPosition();

  const int ingame_mouse_position_x =
      d2::d2client::GetIngameMousePositionX();
  const int ingame_mouse_position_y =
      d2::d2client::GetIngameMousePositionY();

  return ingame_mouse_position_x > button_position.GetLeft()
      && ingame_mouse_position_x < button_position.GetRight()
      && ingame_mouse_position_y > button_position.GetTop()
      && ingame_mouse_position_y < button_position.GetBottom();
}

bool IsMouseOverNewSkillButton() {
  return false;
}

} // namespace sgd2fr

