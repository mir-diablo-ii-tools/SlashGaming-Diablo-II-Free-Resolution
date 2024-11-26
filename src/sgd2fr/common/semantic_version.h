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

#ifndef SGD2FR_COMMON_SEMANTIC_VERSION_H_
#define SGD2FR_COMMON_SEMANTIC_VERSION_H_

#include <stddef.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

struct SemanticVersion {
  int major_version;
  int minor_version;
  int patch_version;
  int build_version;
};

enum {
  /* Min length is based on "0.0.0.0". */
  SemanticVersion_kMinLength = 7,
  /* Max length is based on "2147483647.2147483647.2147483647.2147483647". */
  SemanticVersion_kMaxLength = 43
};

/**
 * Returns a compare value based on a comparison of the fields of the two
 * versions.
 */
int SemanticVersion_Compare(
    const struct SemanticVersion* lhs, const struct SemanticVersion* rhs);

/**
 * Returns a non-zero value if the two versions are equal. Otherwise returns
 * zero.
 */
int SemanticVersion_Equals(
    const struct SemanticVersion* lhs, const struct SemanticVersion* rhs);

/**
 * Initializes a new version object with the given string parameter. Returns
 * the given resolution object on success. Otherwise, returns NULL.
 *
 * The string format for a version must match "MAJOR.MINOR.PATCH.BUILD". The
 * values for each portion must fit in a positive 31-bit unsigned integer
 * value. Otherwise, the function returns NULL.
 */
struct SemanticVersion* SemanticVersion_FromString(
    struct SemanticVersion* version, const char* str, size_t length);

/**
 * Converts the version values into string format, i.e.
 * "MAJOR.MINOR.PATCH.BUILD".
 *
 * The buffer must be capable of storing 44 characters for guaranteed safe
 * usage. If length is NULL, then the length of the resulting string will not
 * be written.
 */
char* SemanticVersion_ToString(
    const struct SemanticVersion* version, char* buffer, size_t* length);

/**
 * Converts the version values into string format, i.e.
 * "MAJOR.MINOR.PATCH.BUILD".
 *
 * The buffer must be capable of storing 44 characters for guaranteed safe
 * usage. If length is NULL, then the length of the resulting string will not
 * be written.
 */
wchar_t* SemanticVersion_ToWString(
    const struct SemanticVersion* version, wchar_t* buffer, size_t* length);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* SGD2FR_COMMON_SEMANTIC_VERSION_H_ */
