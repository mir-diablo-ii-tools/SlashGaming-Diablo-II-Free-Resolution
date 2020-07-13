/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2020  Mir Drualga
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

constexpr std::tuple resolution_640x480 = std::make_tuple(640, 480);
constexpr std::tuple resolution_800x600 = std::make_tuple(800, 600);

const std::vector<std::tuple<int, int>>& GetResolutionsFromIpV4(std::string_view ipv4_address) {
  static const std::unordered_map<
      std::string_view,
      std::vector<std::tuple<int, int>>
  > acceptable_resolutions_from_ipv4 = {
      // play.slashdiablo.net
      {
          "209.222.25.91", {
              resolution_640x480,
              resolution_800x600,
              std::make_tuple(1068, 600)
          }
      },
      // evnt.slashdiablo.net
      {
          "207.252.75.177", {
              resolution_640x480,
              resolution_800x600,
              std::make_tuple(1068, 600)
          }
      },
      // realm.diablo09.com
      {
          "95.179.228.126", {
              resolution_640x480,
              resolution_800x600,
              std::make_tuple(1024, 768)
          }
      },
  };

  static const std::vector default_resolutions = {
      resolution_640x480,
      resolution_800x600
  };

  return acceptable_resolutions_from_ipv4.contains(ipv4_address)
      ? acceptable_resolutions_from_ipv4.at(ipv4_address)
      : default_resolutions;
}

const std::vector<std::tuple<int, int>>& SelectLocalOrOnlineResolutions() {
  if (d2::d2client::GetGameType() == d2::ClientGameType::kBattleNetJoin) {
    return GetResolutionsFromIpV4(d2::bnclient::GetGatewayIpV4Address());
  } else {
    return config::GetIngameResolutions();
  }
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

const std::vector<std::tuple<int, int>>& GetNonCrashingIngameResolutions() {
  static std::mutex check_mutex;
  static std::unique_ptr init_once_flag = std::make_unique<std::once_flag>();
  static d2::ClientGameType selected_game_type =
      d2::d2client::GetGameType();
  static std::vector<std::tuple<int, int>> non_crashing_ingame_resolutions;

  std::lock_guard lock(check_mutex);

  if (selected_game_type != d2::d2client::GetGameType()) {
    init_once_flag = std::make_unique<std::once_flag>();
  }

  std::call_once(
      *init_once_flag,
      [=] () {
        d2::VideoMode current_video_mode = d2::d2gfx::GetVideoMode();
        const std::vector<std::tuple<int, int>>& selected_ingame_resolutions =
            SelectLocalOrOnlineResolutions();

        selected_game_type = d2::d2client::GetGameType();
        non_crashing_ingame_resolutions.clear();

        if (current_video_mode == d2::VideoMode::kDirect3D
            || current_video_mode == d2::VideoMode::kDirectDraw) {
          std::copy_if(
              selected_ingame_resolutions.cbegin(),
              selected_ingame_resolutions.cend(),
              std::back_inserter(non_crashing_ingame_resolutions),
              &IsStandardResolution
          );
        } else {
          non_crashing_ingame_resolutions = selected_ingame_resolutions;
        }
      }
  );

  return non_crashing_ingame_resolutions;
}

} // namespace

std::size_t GetMinConfigResolutionId() {
  return GetNonCrashingIngameResolutions().at(0) == resolution_640x480
      ? 0
      : 1;
}

std::size_t GetMinIngameResolutionId() {
  return GetNonCrashingIngameResolutions().at(0) == resolution_640x480
      ? 0
      : 2;
}

std::size_t GetNumIngameResolutions() {
  return GetNonCrashingIngameResolutions().size();
}

std::tuple<int, int> GetIngameResolutionFromId(std::size_t id) {
  if (id == 0) {
    return resolution_640x480;
  } else if (id == 1) {
    return config::GetMainMenuResolution();
  }

  const auto& ingame_resolutions = GetNonCrashingIngameResolutions();

  std::size_t ingame_resolution_index = (GetMinIngameResolutionId() == 0)
      ? id - 1
      : id - 2;

  return ingame_resolutions.at(ingame_resolution_index);
}

bool IsStandardResolution(const std::tuple<int, int>& width_and_height) {
  return GetStandardResolutions().contains(width_and_height);
}

} // namespace sgd2fr
