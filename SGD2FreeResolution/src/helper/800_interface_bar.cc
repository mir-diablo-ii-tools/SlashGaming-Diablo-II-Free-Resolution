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

#include "800_interface_bar.hpp"

#include <sgd2mapi.hpp>
#include "../game_resolution/game_resolution.hpp"
#include "../user_config.h"

namespace sgd2fr {
namespace {

// Display width and height constants.
enum {
  kSourceDisplayWidth = 800,
  kSourceDisplayHeight = 600,
};

// New Stats button constants.
enum {
  // In 800x600 mode, the New Stats button is normally positioned at:
  // left: 206, right: 240, top: 800 - 42, bottom: 800 - 8

  // Text is positioned at:
  // x: 221, y: 550

  // The constants have been positioned in a way to simplify customization.

  kSourceNewStatsButtonLeft = 206,
  kSourceNewStatsButtonTop = kSourceDisplayHeight - 42,

  kSourceNewStatsButtonWidth = 34,
  kSourceNewStatsButtonHeight = 34,

  kSourceNewStatsButtonRight = kSourceNewStatsButtonLeft
      + kSourceNewStatsButtonWidth,
  kSourceNewStatsButtonBottom = kSourceNewStatsButtonTop
      + kSourceNewStatsButtonHeight,

  kSourceNewStatsTextPositionX = kSourceNewStatsButtonLeft
      + (kSourceNewStatsButtonWidth / 2) - 2,
  kSourceNewStatsTextPositionY = kSourceNewStatsButtonTop - 8,
};

// New Skill button constants.
enum {
  // In 800x600 mode, the New Skill button is normally positioned at:
  // left: 563, right: 597, top: 800 - 42, bottom: 800 - 8

  // Text is positioned at:
  // x: 578, y: 550

  // The constants have been positioned in a way to simplify customization.

  kSourceNewSkillButtonLeft = 563,
  kSourceNewSkillButtonTop = kSourceDisplayHeight - 42,

  kSourceNewSkillButtonWidth = 34,
  kSourceNewSkillButtonHeight = 34,

  kSourceNewSkillButtonRight = kSourceNewSkillButtonLeft
      + kSourceNewSkillButtonWidth,
  kSourceNewSkillButtonBottom = kSourceNewSkillButtonTop
      + kSourceNewSkillButtonHeight,

  kSourceNewSkillTextPositionX = kSourceNewSkillButtonLeft
      + (kSourceNewSkillButtonWidth / 2) - 2,
  kSourceNewSkillTextPositionY = kSourceNewSkillButtonTop - 8,
};

} // namespace

unsigned int Get800InterfaceBarEnabledValue() {
  unsigned int resolution_mode = ::d2::d2gfx::GetResolutionMode();

  GameResolution resolution = GetIngameResolutionFromId(resolution_mode);

  if (resolution.width < 800
      || !UserConfig_Get()->is_use_800_interface_bar) {
    return 0;
  } else {
    return 2;
  }
}

d2::PositionalRectangle_Api GetNewStatsButtonPosition() {
  enum {
    kDistanceFromLeftToDisplayCenter = (kSourceDisplayWidth / 2)
        - kSourceNewStatsButtonLeft,
    kDistanceFromRightToDisplayCenter = (kSourceDisplayWidth / 2)
        - kSourceNewStatsButtonRight,
    kDistanceFromTopToDisplayBottom = kSourceDisplayHeight
        - kSourceNewStatsButtonTop,
    kDistanceFromBottomToDisplayBottom = kSourceDisplayHeight
        - kSourceNewStatsButtonBottom,
  };

  const GameResolution display_width_and_height = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const int display_half_width = display_width_and_height.width / 2;
  const int display_height = display_width_and_height.height;

  ::d2::PositionalRectangle_Api button_position(
      display_half_width - kDistanceFromLeftToDisplayCenter,
      display_half_width - kDistanceFromRightToDisplayCenter,
      display_height - kDistanceFromTopToDisplayBottom,
      display_height - kDistanceFromBottomToDisplayBottom
  );

  return button_position;
}

d2::PositionalRectangle_Api GetNewSkillButtonPosition() {
  enum {
    kDistanceFromLeftToDisplayCenter = (kSourceDisplayWidth / 2)
        - kSourceNewSkillButtonLeft,
    kDistanceFromRightToDisplayCenter = (kSourceDisplayWidth / 2)
        - kSourceNewSkillButtonRight,
    kDistanceFromTopToDisplayBottom = kSourceDisplayHeight
        - kSourceNewSkillButtonTop,
    kDistanceFromBottomToDisplayBottom = kSourceDisplayHeight
        - kSourceNewSkillButtonBottom,
  };

  const GameResolution display_width_and_height = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const int display_half_width = display_width_and_height.width / 2;
  const int display_height = display_width_and_height.height;

  ::d2::PositionalRectangle_Api button_position(
      display_half_width - kDistanceFromLeftToDisplayCenter,
      display_half_width - kDistanceFromRightToDisplayCenter,
      display_height - kDistanceFromTopToDisplayBottom,
      display_height - kDistanceFromBottomToDisplayBottom
  );

  return button_position;
}

GameResolution GetNewStatsPopupTextPosition() {
  enum {
    kDistanceFromPositionXToDisplayCenter = (kSourceDisplayWidth / 2)
        - kSourceNewStatsTextPositionX,
    kDistanceFromPositionYToDisplayBottom = kSourceDisplayHeight
        - kSourceNewStatsTextPositionY,
  };

  const GameResolution display_width_and_height = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const int display_half_width = display_width_and_height.width / 2;
  const int display_height = display_width_and_height.height;

  return {
      display_half_width - kDistanceFromPositionXToDisplayCenter,
      display_height - kDistanceFromPositionYToDisplayBottom
  };
}

GameResolution GetNewSkillPopupTextPosition() {
  enum {
    kDistanceFromPositionXToDisplayCenter = (kSourceDisplayWidth / 2)
        - kSourceNewSkillTextPositionX,
    kDistanceFromPositionYToDisplayBottom = kSourceDisplayHeight
        - kSourceNewSkillTextPositionY,
  };

  const GameResolution display_width_and_height = GetIngameResolutionFromId(
      ::d2::d2gfx::GetResolutionMode()
  );

  const int display_half_width = display_width_and_height.width / 2;
  const int display_height = display_width_and_height.height;

  return {
      display_half_width - kDistanceFromPositionXToDisplayCenter,
      display_height - kDistanceFromPositionYToDisplayBottom
  };
}

bool IsMouseOverNewStatsButton() {
  ::d2::PositionalRectangle_Api button_position = GetNewStatsButtonPosition();

  const int ingame_mouse_position_x =
      ::d2::d2client::GetIngameMousePositionX();
  const int ingame_mouse_position_y =
      ::d2::d2client::GetIngameMousePositionY();

  return ingame_mouse_position_x > button_position.GetLeft()
      && ingame_mouse_position_x < button_position.GetRight()
      && ingame_mouse_position_y > button_position.GetTop()
      && ingame_mouse_position_y < button_position.GetBottom();
}

bool IsMouseOverNewSkillButton() {
  ::d2::PositionalRectangle_Api button_position = GetNewSkillButtonPosition();

  const int ingame_mouse_position_x =
      ::d2::d2client::GetIngameMousePositionX();
  const int ingame_mouse_position_y =
      ::d2::d2client::GetIngameMousePositionY();

  return ingame_mouse_position_x > button_position.GetLeft()
      && ingame_mouse_position_x < button_position.GetRight()
      && ingame_mouse_position_y > button_position.GetTop()
      && ingame_mouse_position_y < button_position.GetBottom();
}

} // namespace sgd2fr
