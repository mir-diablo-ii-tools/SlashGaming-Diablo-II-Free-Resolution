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

#ifndef SGD2FR_COMMON_RESOLUTION_H_
#define SGD2FR_COMMON_RESOLUTION_H_

#include <stddef.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

struct Resolution {
  int width;
  int height;
};

enum {
  /* Max length is based on "-2147483648x-2147483647". */
  Resolution_kMaxLength = 23
};

extern struct Resolution Resolution_kDefault;
extern struct Resolution Resolution_k640x480;
extern struct Resolution Resolution_k800x600;

/**
 * Initializes a new resolution object with the given string parameter. Returns
 * the given resolution object on success. Otherwise, returns NULL.
 *
 * The string format for a resolution must match "WIDTHxHEIGHT". The width and
 * height value must fit in a 32-bit integer value. Otherwise, the function
 * returns NULL.
 */
struct Resolution* Resolution_FromString(
    struct Resolution* resolution, const char* str);

/**
 * Initializes a new resolution object with the given string parameter. Returns
 * the given resolution object on success. Otherwise, returns NULL.
 *
 * The string format for a resolution must match "WIDTHxHEIGHT". The width and
 * height value must fit in a 32-bit integer value. Otherwise, the function
 * returns NULL.
 */
struct Resolution* Resolution_FromWString(
    struct Resolution* resolution, const wchar_t* str);

/**
 * Returns a compare value based on a comparison of the width and height fields
 * of the two resolutions.
 */
int Resolution_Compare(
    const struct Resolution* lhs, const struct Resolution* rhs);

/**
 * Returns a non-zero value if the two resolutions are equal. Otherwise returns
 * zero.
 */
int Resolution_Equals(
    const struct Resolution* lhs, const struct Resolution* rhs);

/**
 * Converts the resolution values into string format, i.e. "WIDTHxHEIGHT".
 *
 * The buffer must be capable of storing 22 characters for guaranteed safe
 * usage. If length is NULL, then the length of the resulting string will not
 * be written.
 */
char* Resolution_ToString(
    const struct Resolution* resolution, char* buffer, size_t* length);

/**
 * Converts the resolution values into string format, i.e. "WIDTHxHEIGHT".
 *
 * The buffer must be capable of storing 22 characters for guaranteed safe
 * usage. If length is NULL, then the length of the resulting string will not
 * be written.
 */
wchar_t* Resolution_ToWString(
    const struct Resolution* resolution, wchar_t* buffer, size_t* length);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* SGD2FR_COMMON_RESOLUTION_H_ */
