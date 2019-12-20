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

#include "game_resolution.hpp"

#include <algorithm>
#include <mutex>
#include <set>
#include <unordered_map>

#include <sgd2mapi.hpp>
#include "../config.hpp"

namespace sgd2fr {
namespace {

std::vector<std::tuple<int, int>> GetResolutionsFromIpV4(std::string_view ipv4_address) {
  std::unordered_map<
      std::string_view,
      std::vector<std::tuple<int, int>>
  > acceptable_resolutions_from_ipv4 = {
      { "", { std::make_tuple(1068, 600) } },
  };

  return acceptable_resolutions_from_ipv4.contains(ipv4_address)
      ? acceptable_resolutions_from_ipv4.at(ipv4_address)
      : std::vector{ std::make_tuple(640, 480), std::make_tuple(800, 600) };
}

const std::set<std::tuple<int, int>>& GetStandardResolutions() {
  static std::once_flag init_once_flag;
  static std::set<std::tuple<int, int>> standard_resolutions;

  std::call_once(
      init_once_flag,
      [=] () {
        DEVMODEW dev_mode;
        dev_mode.dmSize = sizeof(dev_mode);

        for (DWORD i = 0; EnumDisplaySettingsW(nullptr, i, &dev_mode); i += 1) {
            standard_resolutions.insert(
                std::make_tuple(
                    static_cast<int>(dev_mode.dmPelsWidth),
                    static_cast<int>(dev_mode.dmPelsHeight)
                )
            );
        }
      }
  );

  return standard_resolutions;
}

std::vector<std::tuple<int, int>> GetNonCrashingIngameResolutions() {
  static std::once_flag init_once_flag;
  static std::vector non_crashing_ingame_resolutions = config::GetIngameResolutions();

  std::call_once(
      init_once_flag,
      [=] () {
        d2::VideoMode current_video_mode = d2::d2gfx::GetVideoMode();

        if (current_video_mode == d2::VideoMode::kDirect3D
            || current_video_mode == d2::VideoMode::kDirectDraw) {
          std::remove_if(
              non_crashing_ingame_resolutions.begin(),
              non_crashing_ingame_resolutions.end(),
              &IsStandardResolution
          );
        }
      }
  );

  return non_crashing_ingame_resolutions;
}

} // namespace

std::tuple<int, int> GetResolutionFromId(std::size_t id) {
  if (id == 1) {
    return config::GetMainMenuResolution();
  }

  const auto& ingame_resolutions = GetNonCrashingIngameResolutions();

  std::size_t ingame_resolution_index = (id == 0)
      ? id
      : id - 1;

  return ingame_resolutions.at(ingame_resolution_index);
}

bool IsStandardResolution(const std::tuple<int, int>& width_and_height) {
  return GetStandardResolutions().contains(width_and_height);
}

} // namespace sgd2fr
