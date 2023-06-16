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
#include "checksum_hash.h"
#include "ddraw_version.hpp"

namespace sgd2fr {
namespace {

using Ipv4HashResolutionTableEntry = ::std::pair<
    ::std::string_view,
    ::std::vector<::std::tuple<int, int>>
>;

struct Ipv4HashResolutionTableEntryCompareKey {
  constexpr bool operator()(
      const Ipv4HashResolutionTableEntry& entry1,
      const Ipv4HashResolutionTableEntry& entry2
  ) noexcept {
    return entry1.first < entry2.first;
  }

  constexpr bool operator()(
      const Ipv4HashResolutionTableEntry::first_type& key,
      const Ipv4HashResolutionTableEntry& entry
  ) noexcept {
    return key < entry.first;
  }

  constexpr bool operator()(
      const Ipv4HashResolutionTableEntry& entry,
      const Ipv4HashResolutionTableEntry::first_type& key
  ) noexcept {
    return entry.first < key;
  }
};

const std::vector<std::tuple<int, int>>& GetResolutionsFromIpV4(
    std::string_view ipv4_address
) {
  // Warning: This needs to be sorted lexicographically!
  static const Ipv4HashResolutionTableEntry kSortedIpv4ResolutionTable[] = {

      // NOWD
      Ipv4HashResolutionTableEntry(
          "14F5ECFBCD56780D47BCC134FD021BFC15B5D168",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600),
              std::make_tuple(1344, 700)
          }
      ),

      // MXL Ultimative Challenge
      Ipv4HashResolutionTableEntry(
          "1A76FC3AA22DB2C650596C6B71DBCF78895FE551",
          {
              kResolution800x600,
              std::make_tuple(1024, 768)
          }),

      // timer's server (old)
      Ipv4HashResolutionTableEntry(
          "1EF04EB4585C6521BDD6F644D0AB3D2020EC4600",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600),
          }
      ),

      // ptr.diablo09.com (old)
      Ipv4HashResolutionTableEntry(
          "22A3E5D23BD68EED6A8163EB1F17F0A74EA3D119",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }),

      // Ale-'s server 2
      Ipv4HashResolutionTableEntry(
          "38B7CA6876F3FA76229720B6B0B94925F64FC790",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600),
          }),

      // Rebirth D2
      Ipv4HashResolutionTableEntry(
          "3F37A6BE5E02055D3E57D45353338FFD0EFA58BC",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1024, 768),
              std::make_tuple(1068, 600),
              std::make_tuple(1280, 768)
          }
      ),

      // timer's server
      Ipv4HashResolutionTableEntry(
          "44EBC5EE6B0C2D5474233AD3370161FA5CFE560D",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600),
          }
      ),

      // Diablo II Evolution
      Ipv4HashResolutionTableEntry(
          "4A0C205D82F5A1089606505350B5096829E9182C",
          {
              kResolution800x600,
              std::make_tuple(1068, 600),
              std::make_tuple(1280, 720),
          }),

      // Vahsify's "The Fury Within 1.02"
      Ipv4HashResolutionTableEntry(
          "4B3B6D3727A0004E04DFF49E41D497C001C7DFCF",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600),
          }),

      // ptr.diablo09.com
      Ipv4HashResolutionTableEntry(
          "4FEE7F8C74CB7EC0096D8653ED9D964EBEBBBDA2",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }),

      // Firesnake's ESR
      Ipv4HashResolutionTableEntry(
          "70C115B399B78827EEA39A045129771230C28F36",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1024, 768),
              std::make_tuple(1068, 600),
              std::make_tuple(1280, 720),
          }),

      // Casual Nostalgia
      Ipv4HashResolutionTableEntry(
          "7233C41BD36281AD8D0251D74F5E84984F35AC3E",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1024, 768),
              std::make_tuple(1068, 600)
          }),

      // D2infinitum
      Ipv4HashResolutionTableEntry(
          "746F9216D84745B78A9777E3A8FC27B20A1C8C51",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600),
          }),

      // Firesnake's ESR (beta)
      Ipv4HashResolutionTableEntry(
          "830C87608053315439D453BC28B75EE7B4DA73C9",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1024, 768),
              std::make_tuple(1068, 600),
              std::make_tuple(1280, 720),
          }),

      // ip.d2lod.net
      Ipv4HashResolutionTableEntry(
          "8FD8A2923B012C29A1427B3972B16752AFB8FF0F",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1024, 768),
              std::make_tuple(1068, 600)
          }
      ),

      // realm.diablo09.com
      Ipv4HashResolutionTableEntry(
          "9A2517D7A8CC25A05F76C263DB923725157CC275",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }
      ),

      // D2 Blacksoul
      Ipv4HashResolutionTableEntry(
          "A3383DA756A8D9AD74A2B7A712C3BE4A15745574",
          {
              std::make_tuple(1068, 600),
              std::make_tuple(1280, 720)
          }),

      // Project Diablo 2
      Ipv4HashResolutionTableEntry(
          "AB3C21D075AFC5B3A07EEF579576454D89C998E4",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }
      ),

      // ZombiesRUs
      Ipv4HashResolutionTableEntry(
          "B0DE98F5C01859485AD9DE0902AC929AAE8FFEA4",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }
      ),

      // Diablo2Online
      Ipv4HashResolutionTableEntry(
          "B754F27105498EACFAFE10B5B4C48C2C572B64F1",
          {
              kResolution640x480,
              kResolution800x600,
              // Do not add 856x480, by WOLF's request
              std::make_tuple(1068, 600)
          }),

      // play.slashdiablo.net
      Ipv4HashResolutionTableEntry(
          "C311F388012034C4ACB91AC573965302CF5711E0",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }
      ),

      // evnt.slashdiablo.net
      Ipv4HashResolutionTableEntry(
          "E1625F180F649ED2E4C98B4210012B6C52D9361F",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }
      ),

      // evnt.slashdiablo.net (old)
      Ipv4HashResolutionTableEntry(
          "F067533C94707F1DE2DBB0AFA1334F8EBE276450",
          {
              kResolution640x480,
              kResolution800x600,
              std::make_tuple(856, 480),
              std::make_tuple(1068, 600)
          }
      ),

      // 1.09 DiabloFans
      Ipv4HashResolutionTableEntry(
          "FCCB6017F496BD14AB7281E963E969D94C176568",
          {
              kResolution800x600,
              std::make_tuple(1024, 768),
              std::make_tuple(1244, 700),
          }
      ),
  };

  enum {
    kSortedIpv4ResolutionTableCount =
        sizeof(kSortedIpv4ResolutionTable)
            / sizeof(kSortedIpv4ResolutionTable[0])
  };

  static const std::vector default_resolutions = {
      kResolution640x480,
      kResolution800x600
  };

  char sha1_str[Sha1_kLength + 1];
  Sha1_GenerateHash(sha1_str, ipv4_address.data(), ipv4_address.length());

  const Ipv4HashResolutionTableEntry* table_begin =
      &kSortedIpv4ResolutionTable[0];
  const Ipv4HashResolutionTableEntry* table_end =
      &kSortedIpv4ResolutionTable[kSortedIpv4ResolutionTableCount];
  ::std::pair search_range = ::std::equal_range(
      table_begin,
      table_end,
      sha1_str,
      Ipv4HashResolutionTableEntryCompareKey()
  );

  if (search_range.first == table_end
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
                && ddraw_version::GetRunning() != DDrawVersion::kCnC
                && ddraw_version::GetRunning() != DDrawVersion::kD2gl)) {
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
