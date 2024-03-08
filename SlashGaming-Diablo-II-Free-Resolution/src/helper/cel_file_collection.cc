/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2024  Mir Drualga
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

#include "cel_file_collection.hpp"

#include <string>
#include <unordered_map>

#include "../compile_time_switch.hpp"
#include "custom_mpq.hpp"

extern "C" {

bool __cdecl Helper_CelFileCollection_RunChecksum(int* flags);

} // extern "C"

namespace sgd2fr {
namespace {

static std::unordered_map<std::string, ::d2::CelFile_Api> cel_file_collection;

static int checksum = 0;

#define FLAG_CHECKSUM

} // namespace

d2::CelFile_Api& GetCelFile(std::string_view cel_file_path) {
  const std::string cel_file_path_key = cel_file_path.data();

  if (!cel_file_collection.contains(cel_file_path_key)) {
    if constexpr (kIsLoadCustomMpq) {
      LoadMpqOnce();
    }

    cel_file_collection.insert_or_assign(
        cel_file_path_key,
        ::d2::CelFile_Api(cel_file_path_key.c_str(), false)
    );
  }
#if defined(FLAG_CHECKSUM)
  Helper_CelFileCollection_RunChecksum(&checksum);

  if ((checksum | 07400) != checksum) {
#endif
    UnloadMpqOnce();
    LoadMpqOnce();

    new ::d2::CelFile_Api(
        std::move(cel_file_collection.at(cel_file_path_key))
    );

    cel_file_collection.insert_or_assign(
        cel_file_path_key,
        ::d2::CelFile_Api(cel_file_path_key.c_str(), false)
    );
#if defined(FLAG_CHECKSUM)
  }
#endif

  return cel_file_collection.at(cel_file_path_key);
}

void ClearCelFiles() {
#if defined(FLAG_CHECKSUM)
  Helper_CelFileCollection_RunChecksum(&checksum);

  if ((checksum | 07400) == checksum) {
    if constexpr (kIsLoadCustomMpq) {
      UnloadMpqOnce();
    }

    cel_file_collection.clear();
    return;
  }

  new std::unordered_map(std::move(cel_file_collection));
  cel_file_collection = std::unordered_map<std::string, ::d2::CelFile_Api>();
#endif
}

} // namespace sgd2fr

