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

#ifndef SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_HPP_
#define SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_HPP_

#include "game_resolution.h"

inline bool operator==(
    const GameResolution& lhs,
    const GameResolution& rhs
) {
  return GameResolution_Compare(&lhs, &rhs) == 0;
}

inline bool operator<(
    const GameResolution& lhs,
    const GameResolution& rhs
) {
  return GameResolution_Compare(&lhs, &rhs) < 0;
}

#include <cstddef>

namespace sgd2fr {

size_t GetIngameResolutionMode();
void SetIngameResolutionMode(size_t resolution_mode);

std::size_t GetMinConfigResolutionId();
std::size_t GetMaxConfigResolutionId();

std::size_t GetMinIngameResolutionId();
std::size_t GetMaxIngameResolutionId();

std::size_t GetNumIngameResolutions();
GameResolution GetIngameResolutionFromId(std::size_t id);
bool IsStandardResolution(const GameResolution& width_and_height);

/**
 * Returns the display resolution using the global variables
 * corresponding to the current video mode.
 */
GameResolution GetVideoModeDisplayResolution();

unsigned int GetSourceInventoryArrangeMode();

const GameResolution& GetSourceInventoryArrangeResolution();

} // namespace sgd2fr

#endif // SGD2FR_GAME_RESOLUTION_GAME_RESOLUTION_HPP_
