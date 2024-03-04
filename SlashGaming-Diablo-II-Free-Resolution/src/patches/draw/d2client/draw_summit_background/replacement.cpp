/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2023  Mir Drualga
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
#include "../../../../helper/game_resolution.hpp"

namespace sgd2fr {

  extern "C" void __stdcall Sgd2fr_D2Client_DrawSummitBackground(
      d2::CelContext *cel_context,
      int32_t start_x,
      int32_t, int32_t, int32_t, int32_t)
  {
    std::tuple width_and_height = GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());
    d2::CelContext_Wrapper cel_wrapper(cel_context);

    uint32_t start_frame = cel_wrapper.GetFrameIndex();

    if (start_x > 0) {
      start_x = start_x - 256;
      start_frame = (start_frame - 1) & 3;
    }

    for (int32_t y = 0, frame = start_frame, frame_shift = 0;
         y < std::get<1>(width_and_height);
         frame = start_frame, frame_shift = (frame_shift + 4) % 12)
    {
      y += 256;
      for (int32_t x = start_x;
           x < std::get<0>(width_and_height);
           x += 256, frame = (frame + 1) & 3)
      {
        cel_wrapper.SetFrameIndex(frame | frame_shift);
        cel_wrapper.DrawFrame(x, y);
      }
    }
  }

} // namespace sgd2fr
