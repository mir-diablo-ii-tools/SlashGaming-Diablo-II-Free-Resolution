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

#include "../include/sgd2modl_exports.h"

#include <mutex>

#include <sgd2mapi.hpp>
#include "config.hpp"
#include "patches/patches.hpp"

namespace {

bool is_loaded = false;

static std::mutex& GetLoadUnloadMutex() {
  static std::mutex load_unload_mutex;

  return load_unload_mutex;
}

static sgd2fr::patches::Patches& GetPatches() {
  static sgd2fr::patches::Patches patches;

  return patches;
}

} // namespace

bool SGD2ModL_OnLoad() {
  std::lock_guard lock_guard(GetLoadUnloadMutex());

  if (is_loaded) {
    return true;
  }

  GetPatches().Apply();

  is_loaded = true;
  return true;
}

bool SGD2ModL_OnUnload() {
  std::lock_guard lock_guard(GetLoadUnloadMutex());

  if (!is_loaded) {
    return true;
  }

  GetPatches().Remove();

  is_loaded = false;
  return true;
}

void SGD2ModL_LoadConfig(const wchar_t* config_path) {
  static std::mutex refresh_config_mutex;
  std::lock_guard lock_guard(refresh_config_mutex);

  sgd2fr::config::LoadConfig();
}
