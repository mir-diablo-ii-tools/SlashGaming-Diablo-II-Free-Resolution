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

#include "game_resolution.hpp"

#include <array>
#include <algorithm>
#include <mutex>
#include <set>
#include <utility>

#include <mdc/error/exit_on_error.hpp>
#include <mdc/wchar_t/filew.h>
#include <sgd2mapi.hpp>
#include "../config.hpp"
#include "../compile_time_switch.hpp"
#include "ddraw_version.hpp"

namespace sgd2fr {
namespace {

using Ipv4ResolutionTableEntry = ::std::pair<
    ::std::string_view,
    ::std::vector<::std::tuple<int, int>>
>;

struct Ipv4ResolutionTableEntryCompareKey {
  constexpr bool operator()(
      const Ipv4ResolutionTableEntry& entry1,
      const Ipv4ResolutionTableEntry& entry2
  ) noexcept {
    return entry1.first < entry2.first;
  }

  constexpr bool operator()(
      const Ipv4ResolutionTableEntry::first_type& key,
      const Ipv4ResolutionTableEntry& entry
  ) noexcept {
    return key < entry.first;
  }

  constexpr bool operator()(
      const Ipv4ResolutionTableEntry& entry,
      const Ipv4ResolutionTableEntry::first_type& key
  ) noexcept {
    return entry.first < key;
  }
};

const std::vector<std::tuple<int, int>>& GetResolutionsFromIpV4(
    std::string_view ipv4_address
) {
  // Warning: This needs to be sorted lexicographically!
  static const ::std::array<
      Ipv4ResolutionTableEntry,
      5
  > kSortedIpv4ResolutionTable = {{

      // evnt.slashdiablo.net
      Ipv4ResolutionTableEntry(
          "207.252.75.177",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(1068, 600)
          }
      ),

      // play.slashdiablo.net
      Ipv4ResolutionTableEntry(
          "209.222.25.91",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(1068, 600)
          }
      ),

      // Project Diablo 2
      Ipv4ResolutionTableEntry(
          "35.225.107.249",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(1068, 600)
          }
      ),

      // ip.d2lod.net
      Ipv4ResolutionTableEntry(
          "51.222.51.12",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(1024, 768),
              std::make_tuple(1068, 600)
          }
      ),

      // realm.diablo09.com
      Ipv4ResolutionTableEntry(
          "95.179.228.126",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(1068, 600)
          }
      ),
  }};

  static const std::vector default_resolutions = {
      kResolution640x480,
      kResolution800x600
  };

  ::std::pair search_range = ::std::equal_range(
      kSortedIpv4ResolutionTable.cbegin(),
      kSortedIpv4ResolutionTable.cend(),
      ipv4_address,
      Ipv4ResolutionTableEntryCompareKey()
  );

  if (search_range.first == kSortedIpv4ResolutionTable.cend()
      || search_range.first == search_range.second) {
    return default_resolutions;
  }

  return search_range.first->second;
}

const std::vector<std::tuple<int, int>>& SelectLocalOrOnlineResolutions() {
  if (d2::d2client::GetGameType() == ::d2::ClientGameType::kBattleNetJoin) {
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
  static ::d2::ClientGameType selected_game_type =
      ::d2::d2client::GetGameType();
  static std::vector<std::tuple<int, int>> non_crashing_ingame_resolutions;
  static ::std::string gateway_ipv4_address;

  std::lock_guard lock(check_mutex);

  if (selected_game_type != ::d2::d2client::GetGameType()
      || gateway_ipv4_address != ::d2::bnclient::GetGatewayIpV4Address()) {
    init_once_flag = std::make_unique<std::once_flag>();
  }

  std::call_once(
      *init_once_flag,
      [&] () {
        ::d2::VideoMode current_video_mode = ::d2::d2gfx::GetVideoMode();
        const std::vector<std::tuple<int, int>>& selected_ingame_resolutions =
            SelectLocalOrOnlineResolutions();

        non_crashing_ingame_resolutions.clear();

        if (current_video_mode == ::d2::VideoMode::kDirect3D
            || (current_video_mode == ::d2::VideoMode::kDirectDraw
                && ddraw_version::GetRunning() != DDrawVersion::kCnC)) {
          std::copy_if(
              selected_ingame_resolutions.cbegin(),
              selected_ingame_resolutions.cend(),
              std::back_inserter(non_crashing_ingame_resolutions),
              &IsStandardResolution
          );
        } else {
          non_crashing_ingame_resolutions = selected_ingame_resolutions;
        }

        selected_game_type = ::d2::d2client::GetGameType();
        gateway_ipv4_address = ::d2::bnclient::GetGatewayIpV4Address();
      }
  );

  return non_crashing_ingame_resolutions;
}

} // namespace

std::size_t GetMinConfigResolutionId() {
  return GetNonCrashingIngameResolutions().at(0) == kResolution640x480
      ? 0
      : 1;
}

std::size_t GetMaxConfigResolutionId() {
  return GetNumIngameResolutions() + GetMinConfigResolutionId();
}

std::size_t GetMinIngameResolutionId() {
  return GetNonCrashingIngameResolutions().at(0) == kResolution640x480
      ? 0
      : 2;
}

std::size_t GetMaxIngameResolutionId() {
  return GetNumIngameResolutions() + GetMinIngameResolutionId();
}

std::size_t GetNumIngameResolutions() {
  return GetNonCrashingIngameResolutions().size();
}

std::tuple<int, int> GetIngameResolutionFromId(std::size_t id) {
  if (id == 0) {
    return kResolution640x480;
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

::std::tuple<int, int> GetVideoModeDisplayResolution() {
  ::d2::VideoMode running_video_mode = ::d2::d2gfx::GetVideoMode();

  switch (running_video_mode) {
    case ::d2::VideoMode::kGdi: {
      return ::std::make_tuple(
          ::d2::d2gdi::GetBitBlockWidth(),
          ::d2::d2gdi::GetBitBlockHeight()
      );
    }

    case ::d2::VideoMode::kDirectDraw: {
      return ::std::make_tuple(
          ::d2::d2ddraw::GetDisplayWidth(),
          ::d2::d2ddraw::GetDisplayHeight()
      );
    }

    case ::d2::VideoMode::kGlide: {
      return ::std::make_tuple(
          ::d2::d2glide::GetDisplayWidth(),
          ::d2::d2glide::GetDisplayHeight()
      );
    }

    case ::d2::VideoMode::kDirect3D: {
      return ::std::make_tuple(
          ::d2::d2direct3d::GetDisplayWidth(),
          ::d2::d2direct3d::GetDisplayHeight()
      );
    }

    default: {
      ::mdc::error::ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          static_cast<int>(running_video_mode)
      );

      return ::std::make_tuple(0, 0);
    }
  }
}

unsigned int GetSourceInventoryArrangeMode() {
  static constexpr unsigned int kDefaultSourceInventoryArrangeMode =
      (kIsSourceInventoryArrange800)
          ? 1
          : 0;

  unsigned int resolution_mode = ::d2::d2gfx::GetResolutionMode();

  ::std::tuple<int, int> current_resolution = GetIngameResolutionFromId(
      resolution_mode
  );

  if (current_resolution == kResolution640x480) {
    return 0;
  } else if (current_resolution == kResolution800x600) {
    return 1;
  } else {
    return kDefaultSourceInventoryArrangeMode;
  }
}

const ::std::tuple<int, int>& GetSourceInventoryArrangeResolution() {
  unsigned int resolution_mode = ::d2::d2gfx::GetResolutionMode();

  ::std::tuple<int, int> current_resolution = GetIngameResolutionFromId(
      resolution_mode
  );

  if (current_resolution == kResolution640x480) {
    return kResolution640x480;
  } else if (current_resolution == kResolution800x600) {
    return kResolution800x600;
  }

  if constexpr (kIsSourceInventoryArrange800) {
    return kResolution800x600;
  } else {
    return kResolution640x480;
  }
}

} // namespace sgd2fr
