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

#include "glide3x_gr_sst_win_open_patch.hpp"

#include "../../../helper/glide3x_version.hpp"

namespace sgd2fr::patches::glide3x {

GrSstWinOpenPatch::GrSstWinOpenPatch()
  : patch_(MakePatch()) {
}

void GrSstWinOpenPatch::Apply() {
  if (this->patch_.has_value()) {
    std::visit([](auto& patch) {
      patch.Apply();
    }, this->patch_.value());
  }
}

void GrSstWinOpenPatch::Remove() {
  if (this->patch_.has_value()) {
    std::visit([](auto& patch) {
      patch.Remove();
    }, this->patch_.value());
  }
}

GrSstWinOpenPatch::PatchType
GrSstWinOpenPatch::MakePatch() {
  d2::VideoMode video_mode = d2::DetermineVideoMode();
  if (video_mode != d2::VideoMode::kGlide) {
    return std::nullopt;
  }

  Glide3xVersion running_glide3x_version = glide3x_version::GetRunning();

  switch (running_glide3x_version) {
    case Glide3xVersion::kSven1_4_4_21:
    case Glide3xVersion::kSven1_4_6_1: {
      return GrSstWinOpenPatch_Sven_1_4_4_21();
    }

    case Glide3xVersion::kSven1_4_8_3: {
      return GrSstWinOpenPatch_Sven_1_4_8_3();
    }

    case Glide3xVersion::kNGlide3_10_0_658: {
      return GrSstWinOpenPatch_NGlide_3_10_0_658();
    }

    case Glide3xVersion::kD2dx: {
      // The D2DX API extensions are used instead.
      return ::std::nullopt;
    }
  }
}

} // namespace sgd2fr::patches::glide3x
