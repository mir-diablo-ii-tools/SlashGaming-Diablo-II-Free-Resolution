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

#include "config.hpp"

#include <array>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>

#include <fmt/format.h>
#include <mjsoni/rapid_json_config_reader.hpp>

namespace sgd2fr::config {
namespace {

// Global config entries.
constexpr std::string_view kGlobalEntryKey = "!!!Globals!!!";

constexpr std::string_view kConfigTabWidthKey = "Config Tab Width";
constexpr int kDefaultConfigTabWidth = 4;

// Main config entries.
constexpr std::string_view kMainEntryKey = "SlashGaming Diablo II Free Resolution";
constexpr std::string_view kMetaDataKey = "!!!Metadata (Do not modify)!!!";

// Note that this signifies the last version where the config formatting and
// entries were updated. These values do not need to change with respect to API
// file version!
constexpr std::string_view kMajorVersionAKey = "Major Version A";
constexpr int kMajorVersionAValue = 3;
constexpr std::string_view kMajorVersionBKey = "Major Version B";
constexpr int kMajorVersionBValue = 0;
constexpr std::string_view kMinorVersionAKey = "Minor Version A";
constexpr int kMinorVersionAValue = 0;
constexpr std::string_view kMinorVersionBKey = "Minor Version B";
constexpr int kMinorVersionBValue = 0;

// Resolution variables.
constexpr std::string_view kIngameResolutionsKey = "Ingame Resolutions";
constexpr std::array<std::string_view, 2> kDefaultIngameResolutions = {
  "640x480",
  "800x600"
};

constexpr std::string_view kMainMenuResolutionKey = "Main Menu Resolution";
constexpr std::string_view kDefaultMainMenuResolution = "800x600";

constexpr std::string_view kIngameResolutionModeKey = "Ingame Resolution Mode";
constexpr unsigned int kDefaultIngameResolutionMode = 0;

// Draw variables.
constexpr std::string_view kScreenBackgroundImagePathKey =
    "Screen Background Image Path";
constexpr std::string_view kDefaultScreenBackgroundImagePath = "";

constexpr std::string_view kScreenBackgroundRibbonImagePathKey =
    "Screen Background Ribbon Image Path";
constexpr std::string_view kDefaultScreenBackgroundRibbonImagePath = "";

// Left screen border images
constexpr std::string_view kCustomLeftScreenBorderLeftImagePathKey =
    "Left Screen Border Left Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderLeftImagePath = "";

constexpr std::string_view kCustomLeftScreenBorderTopImagePathKey =
    "Left Screen Border Top Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderTopImagePath = "";

constexpr std::string_view kCustomLeftScreenBorderTopRightImagePathKey =
    "Left Screen Border Top Right Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderTopRightImagePath = "";

constexpr std::string_view kCustomLeftScreenBorderBottomImagePathKey =
    "Left Screen Border Bottom Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderBottomImagePath = "";

constexpr std::string_view kCustomLeftScreenBorderBottomRightImagePathKey =
    "Left Screen Border Bottom Right Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderBottomRightImagePath = "";

// Right screen border images
constexpr std::string_view kCustomRightScreenBorderRightImagePathKey =
    "Right Screen Border Right Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderRightImagePath = "";

constexpr std::string_view kCustomRightScreenBorderTopImagePathKey =
    "Right Screen Border Top Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderTopImagePath = "";

constexpr std::string_view kCustomRightScreenBorderTopLeftImagePathKey =
    "Right Screen Border Top Left Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderTopLeftImagePath = "";

constexpr std::string_view kCustomRightScreenBorderBottomImagePathKey =
    "Right Screen Border Bottom Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderBottomImagePath = "";

constexpr std::string_view kCustomRightScreenBorderBottomLeftImagePathKey =
    "Right Screen Border Bottom Left Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderBottomLeftImagePath = "";


// Interface Bar Background
constexpr std::string_view kInterfaceBarBackgroundCenterImagePathKey =
    "Interface Bar Background Center Image Path";
constexpr std::string_view kDefaultInterfaceBarBackgroundCenterImagePath = "";

constexpr std::string_view kInterfaceBarBackgroundLeftImagePathKey =
    "Interface Bar Background Left Image Path";
constexpr std::string_view kDefaultInterfaceBarBackgroundLeftImagePath = "";

constexpr std::string_view kInterfaceBarBackgroundRightImagePathKey =
    "Interface Bar Background Right Image Path";
constexpr std::string_view kDefaultInterfaceBarBackgroundRightImagePath = "";

constexpr std::string_view kIsScreenBorderFrameEnabledKey =
    "Enable Screen Border Frame?";
constexpr bool kDefaultIsScreenBorderFrameEnabled = true;

constexpr std::string_view kIsUseOriginalScreenBorderFrameKey =
    "Use Original Screen Border Frame?";
constexpr bool kDefaultIsUseOriginalScreenBorderFrame = false;

std::map<std::string, std::once_flag> once_flags_by_json_keys;

const std::filesystem::path& GetConfigPath() {
  static std::filesystem::path kConfigPath = "SGD2FreeRes.json";
  return kConfigPath;
}

template <typename ...Args>
std::once_flag& GetOnceFlag(const Args&... json_keys) {
  // Calculate concat key size.
  std::size_t concat_key_size = 0;
  for (const auto& json_key : { json_keys...}) {
    concat_key_size += json_key.length() + 1;
  }

  // Concat all keys together.
  std::string concat_key(concat_key_size, '\0');

  std::size_t i = 0;
  for (const auto& json_key : { json_keys...}) {
    concat_key += json_key;
    concat_key += static_cast<char>(i + 1);

    i = (i + 1) % 0x32;
  }

  return once_flags_by_json_keys[std::move(concat_key)];
}

template <typename ...Args>
void ResetOnceFlag(const Args&... json_keys) {
  // Calculate concat key size.
  std::size_t concat_key_size = 0;
  for (const auto& json_key : { json_keys...}) {
    concat_key_size += json_key.length() + 1;
  }

  // Concat all keys together.
  std::string concat_key(concat_key_size, '\0');

  std::size_t i = 0;
  for (const auto& json_key : { json_keys...}) {
    concat_key += json_key;
    concat_key += static_cast<char>(i + 1);

    i = (i + 1) % 0x32;
  }

  once_flags_by_json_keys.erase(std::move(concat_key));
}

bool AddMissingConfigEntries(
    mjsoni::RapidJsonConfigReader& config_reader
) {
  // Check that the actual config version is less than or equal to the expected
  // config version. If the actual is larger, then do not add any new entries.
  // If there are any breaking config changes, then the program will most
  // likely crash.
  int major_version_a = config_reader.GetIntOrDefault(
      std::numeric_limits<int>::min(),
      kMainEntryKey,
      kMetaDataKey,
      kMajorVersionAKey
  );

  if (major_version_a < kMajorVersionAValue) {
    major_version_a = kMajorVersionAValue;

    config_reader.SetDeepInt(
        kMajorVersionAValue,
        kMainEntryKey,
        kMetaDataKey,
        kMajorVersionAKey
    );

    config_reader.SetDeepInt(
        std::numeric_limits<int>::min(),
        kMainEntryKey,
        kMetaDataKey,
        kMajorVersionBKey
    );

    config_reader.SetDeepInt(
        std::numeric_limits<int>::min(),
        kMainEntryKey,
        kMetaDataKey,
        kMinorVersionAKey
    );

    config_reader.SetDeepInt(
        std::numeric_limits<int>::min(),
        kMainEntryKey,
        kMetaDataKey,
        kMinorVersionBKey
    );
  } else if (major_version_a > kMajorVersionAValue) {
    return true;
  }

  int major_version_b = config_reader.GetIntOrDefault(
      std::numeric_limits<int>::min(),
      kMetaDataKey,
      kMajorVersionBKey
  );

  if (major_version_b < kMajorVersionBValue) {
    major_version_b = kMajorVersionBValue;

    config_reader.SetDeepInt(
        kMajorVersionBValue,
        kMainEntryKey,
        kMetaDataKey,
        kMajorVersionBKey
    );

    config_reader.SetDeepInt(
        std::numeric_limits<int>::min(),
        kMainEntryKey,
        kMetaDataKey,
        kMinorVersionAKey
    );

    config_reader.SetDeepInt(
        std::numeric_limits<int>::min(),
        kMainEntryKey,
        kMetaDataKey,
        kMinorVersionBKey
    );
  } else if (major_version_b > kMajorVersionBValue) {
    return true;
  }

  int minor_version_a = config_reader.GetIntOrDefault(
      std::numeric_limits<int>::min(),
      kMainEntryKey,
      kMetaDataKey,
      kMinorVersionAKey
  );

  if (minor_version_a < kMinorVersionAValue) {
    minor_version_a = kMinorVersionAValue;

    config_reader.SetDeepInt(
        kMinorVersionAValue,
        kMainEntryKey,
        kMetaDataKey,
        kMinorVersionAKey
    );

    config_reader.SetDeepInt(
        std::numeric_limits<int>::min(),
        kMainEntryKey,
        kMetaDataKey,
        kMinorVersionBKey
    );
  } else if (minor_version_a > kMinorVersionAValue) {
    return true;
  }

  int minor_version_b = config_reader.GetIntOrDefault(
      std::numeric_limits<int>::min(),
      kMainEntryKey,
      kMetaDataKey,
      kMinorVersionBKey
  );

  if (minor_version_b < kMinorVersionBValue) {
    minor_version_b = kMinorVersionBValue;

    config_reader.SetDeepInt(
        kMinorVersionBValue,
        kMainEntryKey,
        kMetaDataKey,
        kMinorVersionBKey
    );
  } else if (minor_version_b > kMinorVersionBValue) {
    return true;
  }

  // The user's config version is less or equal, so add defaults if missing.
  if (!config_reader.HasInt(kGlobalEntryKey, kConfigTabWidthKey)) {
    config_reader.SetDeepInt(
        kDefaultConfigTabWidth,
        kGlobalEntryKey,
        kConfigTabWidthKey
    );
  }

  if (!config_reader.HasVector(kMainEntryKey, kIngameResolutionsKey)) {
    config_reader.SetDeepArray(
        kDefaultIngameResolutions.cbegin(),
        kDefaultIngameResolutions.cend(),
        kMainEntryKey,
        kIngameResolutionsKey
    );
  }

  if (!config_reader.HasUnsignedInt(kMainEntryKey, kIngameResolutionModeKey)) {
    config_reader.SetDeepUnsignedInt(
        kDefaultIngameResolutionMode,
        kMainEntryKey,
        kIngameResolutionModeKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kMainMenuResolutionKey)) {
    config_reader.SetDeepString(
        kDefaultMainMenuResolution.data(),
        kMainEntryKey,
        kMainMenuResolutionKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kScreenBackgroundImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultScreenBackgroundImagePath.data(),
        kMainEntryKey,
        kScreenBackgroundImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomLeftScreenBorderLeftImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomLeftScreenBorderLeftImagePath.data(),
        kMainEntryKey,
        kCustomLeftScreenBorderLeftImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomLeftScreenBorderTopImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomLeftScreenBorderTopImagePath.data(),
        kMainEntryKey,
        kCustomLeftScreenBorderTopImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomLeftScreenBorderTopRightImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomLeftScreenBorderTopRightImagePath.data(),
        kMainEntryKey,
        kCustomLeftScreenBorderTopRightImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomLeftScreenBorderBottomImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomLeftScreenBorderBottomImagePath.data(),
        kMainEntryKey,
        kCustomLeftScreenBorderBottomImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomLeftScreenBorderBottomRightImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomLeftScreenBorderBottomRightImagePath.data(),
        kMainEntryKey,
        kCustomLeftScreenBorderBottomRightImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomRightScreenBorderRightImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomRightScreenBorderRightImagePath.data(),
        kMainEntryKey,
        kCustomRightScreenBorderRightImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomRightScreenBorderTopImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomRightScreenBorderTopImagePath.data(),
        kMainEntryKey,
        kCustomRightScreenBorderTopImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomRightScreenBorderTopLeftImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomRightScreenBorderTopLeftImagePath.data(),
        kMainEntryKey,
        kCustomRightScreenBorderTopLeftImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomRightScreenBorderBottomImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomRightScreenBorderBottomImagePath.data(),
        kMainEntryKey,
        kCustomRightScreenBorderBottomImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kCustomRightScreenBorderBottomLeftImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultCustomRightScreenBorderBottomLeftImagePath.data(),
        kMainEntryKey,
        kCustomRightScreenBorderBottomLeftImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kInterfaceBarBackgroundCenterImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultInterfaceBarBackgroundCenterImagePath.data(),
        kMainEntryKey,
        kInterfaceBarBackgroundCenterImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kInterfaceBarBackgroundLeftImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultInterfaceBarBackgroundLeftImagePath.data(),
        kMainEntryKey,
        kInterfaceBarBackgroundLeftImagePathKey
    );
  }

  if (!config_reader.HasString(kMainEntryKey, kInterfaceBarBackgroundRightImagePathKey)) {
    config_reader.SetDeepString(
        kDefaultInterfaceBarBackgroundRightImagePath.data(),
        kMainEntryKey,
        kInterfaceBarBackgroundRightImagePathKey
    );
  }

  if (!config_reader.HasBool(kMainEntryKey, kIsScreenBorderFrameEnabledKey)) {
    config_reader.SetDeepBool(
        kDefaultIsScreenBorderFrameEnabled,
        kMainEntryKey,
        kIsScreenBorderFrameEnabledKey
    );
  }

  if (!config_reader.HasBool(kMainEntryKey, kIsUseOriginalScreenBorderFrameKey)) {
    config_reader.SetDeepBool(
        kDefaultIsUseOriginalScreenBorderFrame,
        kMainEntryKey,
        kIsUseOriginalScreenBorderFrameKey
    );
  }

  // Write to the config file any new default values.
  int indent_width = config_reader.GetInt(
      kGlobalEntryKey,
      kConfigTabWidthKey
  );

  return config_reader.Write(indent_width);
}

mjsoni::RapidJsonConfigReader ReadConfig(
    const std::filesystem::path& config_file_path
) {
  // Read the config file for processing, if all other conditions are good.
  mjsoni::RapidJsonConfigReader config_reader(config_file_path);

  bool is_read = config_reader.Read();
  if (!is_read) {
    std::wstring failed_to_read_message = fmt::format(
        L"Failed to read config in: {}",
        config_file_path.wstring().data()
    );

    MessageBoxW(
        nullptr,
        failed_to_read_message.data(),
        L"Failed to Read Config",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }

  bool is_missing_entry_added = AddMissingConfigEntries(config_reader);
  if (!is_missing_entry_added) {
    std::wstring failed_to_read_message = fmt::format(
        L"Failed add missing entries to the config in: {}",
        config_file_path.wstring().data()
    );

    MessageBoxW(
        nullptr,
        failed_to_read_message.data(),
        L"Failed to Add Missing Entries to Config",
        MB_OK | MB_ICONERROR
    );

    std::exit(0);
  }

  return config_reader;
}

mjsoni::RapidJsonConfigReader& GetConfigReader() {
  static mjsoni::RapidJsonConfigReader config_reader =
      ReadConfig(GetConfigPath());
  return config_reader;
}

std::tuple<int, int> GetResolutionFromString(
    std::string_view resolution_str
) {
  std::string::size_type split_index = resolution_str.find('x');

  int resolution_width = std::atoi(
      resolution_str.substr(0, split_index).data()
  );

  int resolution_height = std::atoi(
      resolution_str.substr(split_index + 1).data()
  );

  return std::make_tuple(resolution_width, resolution_height);
}

} // namespace

const std::vector<std::tuple<int, int>>& GetIngameResolutions() {
  static std::vector<std::tuple<int, int>> ingame_resolutions;
  static const std::vector<std::string> default_ingame_resolutions_str(
      kDefaultIngameResolutions.cbegin(),
      kDefaultIngameResolutions.cend()
  );

  std::call_once(
      GetOnceFlag(kMainEntryKey, kIngameResolutionsKey),
      [=] () {
        std::vector<std::string> ingame_resolutions_str = GetConfigReader()
            .GetVectorOrDefault<std::string>(
                default_ingame_resolutions_str,
                kMainEntryKey,
                kIngameResolutionsKey
            );

        std::set<std::tuple<int, int>> sorted_distinct_ingame_resolutions;

        for (const std::string& resolution_str : ingame_resolutions_str) {
          sorted_distinct_ingame_resolutions.insert(
              GetResolutionFromString(resolution_str)
          );
        }

        ingame_resolutions = std::vector(
            std::make_move_iterator(sorted_distinct_ingame_resolutions.begin()),
            std::make_move_iterator(sorted_distinct_ingame_resolutions.end())
        );
      }
  );

  return ingame_resolutions;
}

std::tuple<int, int> GetMainMenuResolution() {
  static std::tuple<int, int> main_menu_resolution;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kMainMenuResolutionKey),
      [=] () {
        std::string main_menu_resolution_str = GetConfigReader()
            .GetStringOrDefault(
                kDefaultMainMenuResolution.data(),
                kMainEntryKey,
                kMainMenuResolutionKey
            );

        main_menu_resolution = GetResolutionFromString(
            main_menu_resolution_str
        );
      }
  );

  return main_menu_resolution;
}

unsigned int GetIngameResolutionMode() {
  static unsigned int ingame_resolution_mode;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kIngameResolutionModeKey),
      [=] () {
        ingame_resolution_mode = GetConfigReader()
            .GetUnsignedInt(
                kMainEntryKey,
                kIngameResolutionModeKey
            );

        if (ingame_resolution_mode > GetIngameResolutions().size()) {
          ingame_resolution_mode = kDefaultIngameResolutionMode;
        }
      }
  );

  return ingame_resolution_mode;
}

void SetIngameResolutionMode(unsigned int resolution_mode) {
  ResetOnceFlag(kMainEntryKey, kIngameResolutionModeKey);

  GetConfigReader().SetDeepUnsignedInt(
          resolution_mode,
          kMainEntryKey,
          kIngameResolutionModeKey
      );

  WriteConfig();
}

std::string_view GetScreenBackgroundImagePath() {
  static std::string screen_background_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kScreenBackgroundImagePathKey),
      [=] () {
        screen_background_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kScreenBackgroundImagePathKey
            );
      }
  );

  return screen_background_image_path;
}

std::string_view GetCustomLeftScreenBorderLeftImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomLeftScreenBorderLeftImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomLeftScreenBorderLeftImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomLeftScreenBorderTopImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomLeftScreenBorderTopImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomLeftScreenBorderTopImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomLeftScreenBorderTopRightImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomLeftScreenBorderTopRightImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomLeftScreenBorderTopRightImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomLeftScreenBorderBottomImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomLeftScreenBorderBottomImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomLeftScreenBorderBottomImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomLeftScreenBorderBottomRightImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomLeftScreenBorderBottomRightImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomLeftScreenBorderBottomRightImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomRightScreenBorderRightImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomRightScreenBorderRightImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomRightScreenBorderRightImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomRightScreenBorderTopImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomRightScreenBorderTopImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomRightScreenBorderTopImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomRightScreenBorderTopLeftImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomRightScreenBorderTopLeftImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomRightScreenBorderTopLeftImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomRightScreenBorderBottomImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomRightScreenBorderBottomImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomRightScreenBorderBottomImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetCustomRightScreenBorderBottomLeftImagePath() {
  static std::string screen_border_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomRightScreenBorderBottomLeftImagePathKey),
      [=] () {
        screen_border_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomRightScreenBorderBottomLeftImagePathKey
            );
      }
  );

  return screen_border_image_path;
}

std::string_view GetInterfaceBarBackgroundCenterImagePath() {
  static std::string interface_bar_background_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kInterfaceBarBackgroundCenterImagePathKey),
      [=] () {
        interface_bar_background_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kInterfaceBarBackgroundCenterImagePathKey
            );
      }
  );

  return interface_bar_background_image_path;
}

std::string_view GetInterfaceBarBackgroundLeftImagePath() {
  static std::string interface_bar_background_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kInterfaceBarBackgroundLeftImagePathKey),
      [=] () {
        interface_bar_background_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kInterfaceBarBackgroundLeftImagePathKey
            );
      }
  );

  return interface_bar_background_image_path;
}

std::string_view GetInterfaceBarBackgroundRightImagePath() {
  static std::string interface_bar_background_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kInterfaceBarBackgroundRightImagePathKey),
      [=] () {
        interface_bar_background_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kInterfaceBarBackgroundRightImagePathKey
            );
      }
  );

  return interface_bar_background_image_path;
}

bool IsScreenBorderFrameEnabled() {
  static bool is_screen_border_frame_enabled;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kIsScreenBorderFrameEnabledKey),
      [=] () {
        is_screen_border_frame_enabled = GetConfigReader()
            .GetBool(
                kMainEntryKey,
                kIsScreenBorderFrameEnabledKey
            );
      }
  );

  return is_screen_border_frame_enabled;
}

bool IsUseOriginalScreenBorderFrame() {
  static bool is_use_screen_border_frame;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kIsUseOriginalScreenBorderFrameKey),
      [=] () {
        is_use_screen_border_frame = GetConfigReader()
            .GetBool(
                kMainEntryKey,
                kIsUseOriginalScreenBorderFrameKey
            );
      }
  );

  return is_use_screen_border_frame;
}

bool LoadConfig() {
  GetConfigReader() = ReadConfig(GetConfigPath());
  once_flags_by_json_keys.clear();

  return true;
}

bool WriteConfig() {
  int indent_width = GetConfigReader().GetIntOrDefault(
      kDefaultConfigTabWidth,
      kGlobalEntryKey,
      kConfigTabWidthKey
  );

  return GetConfigReader().Write(indent_width);
}

} // namespace sgd2fr::config
