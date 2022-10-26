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

/*
 * Thanks goes to PhrozenKeep, specifically Szumigajowy, for providing
 * the starting point for this patch.
 */

#include "patch.hpp"

#include <stddef.h>

#include "../../../../helper/abstract_multiversion_patch.hpp"
#include "../../../../helper/abstract_version_patch.hpp"
#include "patch_1_07.hpp"
#include "patch_1_11.hpp"

namespace sgd2fr {
namespace d2client {
namespace {

using ::d2::GameVersion;
using ::d2::game_version::GetRunning;

}  // namespace

SetTileCullingBoundPatch::SetTileCullingBoundPatch()
    : AbstractMultiversionPatch(IsApplicable(), InitPatch()) {
}

bool SetTileCullingBoundPatch::IsApplicable() {
  return true;
}

AbstractVersionPatch* SetTileCullingBoundPatch::InitPatch() {
  if (!IsApplicable()) {
    return NULL;
  }

  GameVersion running_game_version = GetRunning();
  switch (running_game_version) {
    case GameVersion::k1_07Beta:
    case GameVersion::k1_07:
    case GameVersion::k1_08:
    case GameVersion::k1_09:
    case GameVersion::k1_09B:
    case GameVersion::k1_09D:
    case GameVersion::k1_10Beta:
    case GameVersion::k1_10SBeta:
    case GameVersion::k1_10:
    case GameVersion::kClassic1_14A:
    case GameVersion::kLod1_14A:
    case GameVersion::kClassic1_14B:
    case GameVersion::kLod1_14B:
    case GameVersion::kClassic1_14C:
    case GameVersion::kLod1_14C:
    case GameVersion::kClassic1_14D:
    case GameVersion::kLod1_14D: {
      return new SetTileCullingBoundPatch_1_07();
    }

    case GameVersion::k1_11:
    case GameVersion::k1_12A:
    case GameVersion::k1_13ABeta:
    case GameVersion::k1_13C:
    case GameVersion::k1_13D: {
      return new SetTileCullingBoundPatch_1_11();
    }
  }
}

}  // namespace d2client
}  // namespace sgd2fr
