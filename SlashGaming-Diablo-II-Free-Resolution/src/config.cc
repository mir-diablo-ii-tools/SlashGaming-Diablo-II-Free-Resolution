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

#include "config.hpp"

#include <array>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>

#include <mdc/error/exit_on_error.hpp>
#include <mdc/wchar_t/filew.h>
#include <mjsoni/rapid_json_config_reader.hpp>
#include "compile_time_switch.hpp"
#include "helper/game_resolution.hpp"

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
constexpr int kMinorVersionAValue = 1;
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

// Custom MPQ
constexpr ::std::string_view kCustomMpqPathKey =
    "Custom MPQ File";
constexpr ::std::string_view kDefaultCustomMpqPath =
    "SGD2FreeRes.mpq";

// Draw variables.
constexpr std::string_view kScreenBackgroundImagePathKey =
    "Screen Background Image Path";
constexpr std::string_view kDefaultScreenBackgroundImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRStoneBack";

// Left screen border images
constexpr std::string_view kCustomLeftScreenBorderLeftImagePathKey =
    "Left Screen Border Left Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderLeftImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderInterfaceLeft";

constexpr std::string_view kCustomLeftScreenBorderTopImagePathKey =
    "Left Screen Border Top Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderTopImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderTopLeft";

constexpr std::string_view kCustomLeftScreenBorderTopRightImagePathKey =
    "Left Screen Border Top Right Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderTopRightImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerTopLeft";

constexpr std::string_view kCustomLeftScreenBorderBottomImagePathKey =
    "Left Screen Border Bottom Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderBottomImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderBottomLeft";

constexpr std::string_view kCustomLeftScreenBorderBottomRightImagePathKey =
    "Left Screen Border Bottom Right Image Path";
constexpr std::string_view kDefaultCustomLeftScreenBorderBottomRightImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerBottomLeft";

// Right screen border images
constexpr std::string_view kCustomRightScreenBorderRightImagePathKey =
    "Right Screen Border Right Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderRightImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderInterfaceRight";

constexpr std::string_view kCustomRightScreenBorderTopImagePathKey =
    "Right Screen Border Top Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderTopImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderTopRight";

constexpr std::string_view kCustomRightScreenBorderTopLeftImagePathKey =
    "Right Screen Border Top Left Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderTopLeftImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerTopRight";

constexpr std::string_view kCustomRightScreenBorderBottomImagePathKey =
    "Right Screen Border Bottom Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderBottomImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderBottomRight";

constexpr std::string_view kCustomRightScreenBorderBottomLeftImagePathKey =
    "Right Screen Border Bottom Left Image Path";
constexpr std::string_view kDefaultCustomRightScreenBorderBottomLeftImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\NeoD2MRFancyBorderCornerBottomRight";

constexpr std::string_view kScreenBorderHorizontalRibbonImagePathKey =
    "Screen Border Horizontal Ribbon";
constexpr std::string_view kDefaultScreenBorderHorizontalRibbonImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyHorizontalBar";

constexpr std::string_view kScreenBorderVerticalRibbonImagePathKey =
    "Screen Border Vertical Ribbon";
constexpr std::string_view kDefaultScreenBorderVerticalRibbonImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyVerticalBar";

// Interface Bar Background
constexpr std::string_view kInterfaceBarBackgroundCenterImagePathKey =
    "Interface Bar Background Center Image Path";
constexpr std::string_view kDefaultInterfaceBarBackgroundCenterImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertHorizontalBar";

constexpr std::string_view kInterfaceBarBackgroundLeftImagePathKey =
    "Interface Bar Background Left Image Path";
constexpr std::string_view kDefaultInterfaceBarBackgroundLeftImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertLeft";

constexpr std::string_view kInterfaceBarBackgroundRightImagePathKey =
    "Interface Bar Background Right Image Path";
constexpr std::string_view kDefaultInterfaceBarBackgroundRightImagePath =
    "data\\SGD2FreeResolution\\ui\\panel\\D2MRFancyPanelInvertRight";

constexpr std::string_view kIsScreenBorderFrameEnabledKey =
    "Enable Screen Border Frame?";
constexpr bool kDefaultIsScreenBorderFrameEnabled = true;

constexpr std::string_view kIsUseOriginalScreenBorderFrameKey =
    "Use Original Screen Border Frame?";
constexpr bool kDefaultIsUseOriginalScreenBorderFrame = false;

// Is 800 Interface Bar Enabled
constexpr std::string_view kIs800InterfaceBarEnabledKey =
    "Use 800 Interface Bar?";
constexpr bool kDefaultIs800InterfaceBarEnabled = true;

std::map<std::string, std::once_flag> once_flags_by_json_keys;

const std::filesystem::path& GetConfigPath() {
  static std::filesystem::path kConfigPath = "SGD2FreeResolution.json";
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

  if constexpr (kIsLoadCustomMpq) {
    if (!config_reader.HasString(kMainEntryKey, kCustomMpqPathKey)) {
      config_reader.SetDeepString(
          kDefaultCustomMpqPath.data(),
          kMainEntryKey,
          kCustomMpqPathKey
      );
    }
  }

  if constexpr (kIsAssetsPathCustomizable) {
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

    if (!config_reader.HasString(kMainEntryKey, kScreenBorderHorizontalRibbonImagePathKey)) {
      config_reader.SetDeepString(
          kDefaultScreenBorderHorizontalRibbonImagePath.data(),
          kMainEntryKey,
          kScreenBorderHorizontalRibbonImagePathKey
      );
    }

    if (!config_reader.HasString(kMainEntryKey, kScreenBorderVerticalRibbonImagePathKey)) {
      config_reader.SetDeepString(
          kDefaultScreenBorderVerticalRibbonImagePath.data(),
          kMainEntryKey,
          kScreenBorderVerticalRibbonImagePathKey
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

  if (!config_reader.HasBool(kMainEntryKey, kIs800InterfaceBarEnabledKey)) {
    config_reader.SetDeepBool(
        kDefaultIs800InterfaceBarEnabled,
        kMainEntryKey,
        kIs800InterfaceBarEnabledKey
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
    ::mdc::error::ExitOnGeneralError(
        L"Error",
        L"Failed to read config in %ls. The file may be missing read "
            L"permissions, or the config is not strictly JSON "
            L"compliant (such as containing a trailing comma after "
            L"the last resolution entry).",
        __FILEW__,
        __LINE__,
        config_file_path.c_str()
    );

    ::std::exit(0);
  }

  bool is_missing_entry_added = AddMissingConfigEntries(config_reader);
  if (!is_missing_entry_added) {
    ::mdc::error::ExitOnGeneralError(
        L"Error",
        L"Failed add missing entries to the config in %ls.",
        __FILEW__,
        __LINE__,
        config_file_path.c_str()
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

Resolution GetResolutionFromString(std::string_view resolution_str) {
  std::string::size_type split_index = resolution_str.find('x');

  int resolution_width = std::atoi(
      resolution_str.substr(0, split_index).data()
  );

  int resolution_height = std::atoi(
      resolution_str.substr(split_index + 1).data()
  );

  return { resolution_width, resolution_height };
}

} // namespace

const std::vector<Resolution>& GetIngameResolutions() {
  static std::vector<Resolution> ingame_resolutions;
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

        std::set<Resolution> sorted_distinct_ingame_resolutions;

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

Resolution GetMainMenuResolution() {
  static Resolution main_menu_resolution;

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

        if (ingame_resolution_mode > GetMaxConfigResolutionId()) {
          ingame_resolution_mode = GetMinConfigResolutionId();
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

::std::string_view GetCustomMpqPath() {
  static std::string custom_mpq_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kCustomMpqPathKey),
      [=] () {
        custom_mpq_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kCustomMpqPathKey
            );
      }
  );

  return custom_mpq_path;
}

std::string_view GetScreenBackgroundImagePath() {
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultScreenBackgroundImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomLeftScreenBorderLeftImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomLeftScreenBorderTopImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomLeftScreenBorderTopRightImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomLeftScreenBorderBottomImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomLeftScreenBorderBottomRightImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomRightScreenBorderRightImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomRightScreenBorderTopImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomRightScreenBorderTopLeftImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomRightScreenBorderBottomImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultCustomRightScreenBorderBottomLeftImagePath;
  }

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

std::string_view GetScreenBorderHorizontalRibbonImagePath() {
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultScreenBorderHorizontalRibbonImagePath;
  }

  static std::string screen_border_ribbon_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kScreenBorderHorizontalRibbonImagePathKey),
      [=] () {
        screen_border_ribbon_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kScreenBorderHorizontalRibbonImagePathKey
            );
      }
  );

  return screen_border_ribbon_image_path;
}

std::string_view GetScreenBorderVerticalRibbonImagePath() {
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultScreenBorderVerticalRibbonImagePath;
  }

  static std::string screen_border_ribbon_image_path;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kScreenBorderVerticalRibbonImagePathKey),
      [=] () {
        screen_border_ribbon_image_path = GetConfigReader()
            .GetString(
                kMainEntryKey,
                kScreenBorderVerticalRibbonImagePathKey
            );
      }
  );

  return screen_border_ribbon_image_path;
}

std::string_view GetInterfaceBarBackgroundCenterImagePath() {
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultInterfaceBarBackgroundCenterImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultInterfaceBarBackgroundLeftImagePath;
  }

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
  if constexpr (!kIsAssetsPathCustomizable) {
    return kDefaultInterfaceBarBackgroundRightImagePath;
  }

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

bool Is800InterfaceBarEnabled() {
  static bool is_800_inteface_bar_enabled;

  std::call_once(
      GetOnceFlag(kMainEntryKey, kIs800InterfaceBarEnabledKey),
      [=] () {
        is_800_inteface_bar_enabled = GetConfigReader()
            .GetBool(
                kMainEntryKey,
                kIs800InterfaceBarEnabledKey
            );
      }
  );

  return is_800_inteface_bar_enabled;
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
