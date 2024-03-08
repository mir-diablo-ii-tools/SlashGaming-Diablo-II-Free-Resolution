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

#include "patch.hpp"

#include <stddef.h>

#include <sgd2mapi.hpp>
#include "patch_1_09d.hpp"
#include "patch_1_13c.hpp"

namespace sgd2fr {
namespace d2glide {

SetDisplayWidthAndHeightPatch::SetDisplayWidthAndHeightPatch()
    : AbstractMultiversionPatch(IsApplicable(), InitPatch()) {
}

bool SetDisplayWidthAndHeightPatch::IsApplicable() {
  ::d2::VideoMode video_mode = ::d2::DetermineVideoMode();
  return (video_mode == ::d2::VideoMode::kGlide);
}

AbstractVersionPatch*
SetDisplayWidthAndHeightPatch::InitPatch() {
  if (!IsApplicable()) {
    return NULL;
  }

  ::d2::GameVersion running_game_version = ::d2::game_version::GetRunning();

  switch (running_game_version) {
    case ::d2::GameVersion::k1_07Beta:
    case ::d2::GameVersion::k1_07:
    case ::d2::GameVersion::k1_08:
    case ::d2::GameVersion::k1_09D:
    case ::d2::GameVersion::k1_10Beta:
    case ::d2::GameVersion::k1_10SBeta:
    case ::d2::GameVersion::k1_10: {
      return new SetDisplayWidthAndHeightPatch_1_09D();
    }

    case ::d2::GameVersion::k1_11:
    case ::d2::GameVersion::k1_12A:
    case ::d2::GameVersion::k1_13ABeta:
    case ::d2::GameVersion::k1_13C:
    case ::d2::GameVersion::k1_13D:
    case ::d2::GameVersion::kLod1_14A:
    case ::d2::GameVersion::kLod1_14B:
    case ::d2::GameVersion::kLod1_14C:
    case ::d2::GameVersion::kLod1_14D: {
      return new SetDisplayWidthAndHeightPatch_1_13C();
    }
  }
}

} // namespace d2glide
} // namespace sgd2fr
