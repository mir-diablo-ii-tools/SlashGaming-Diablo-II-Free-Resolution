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

#include "sgd2fr/common/resolution.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

static int IsNumberStart(char c) {
  return isdigit(c) || c == '-' || c == '+';
}

static int IsNumberStartW(wchar_t c) {
  return iswdigit(c) || c == L'-' || c  == L'+';
}

/**
 * External
 */

struct Resolution Resolution_kDefault = { 640, 480 };
struct Resolution Resolution_k640x480 = { 640, 480 };
struct Resolution Resolution_k800x600 = { 800, 600 };

struct Resolution* Resolution_FromString(
    struct Resolution* resolution, const char* str) {
  size_t i;
  char* delimiter;
  char* null_terminator;

  struct Resolution temp_resolution;

  assert(resolution != NULL);
  assert(str != NULL);

  /* Parse width. */
  if (!IsNumberStart(str[0])) {
    return NULL;
  }
  temp_resolution.width = (int)strtol(str, &delimiter, 10);
  if (errno == ERANGE) {
    return NULL;
  }

  /* Check for 'x' delimiter. */
  if (*delimiter != 'x') {
    return NULL;
  }

  /* Parse height. */
  if (!IsNumberStart(delimiter[1])) {
    return NULL;
  }
  temp_resolution.height = (int)strtol(&delimiter[1], &null_terminator, 10);
  if (errno == ERANGE) {
    return NULL;
  }

  /* Check for null terminator. */
  if (*null_terminator != '\0') {
    return NULL;
  }

  *resolution = temp_resolution;
  return resolution;
}

struct Resolution* Resolution_FromWString(
    struct Resolution* resolution, const wchar_t* str) {
  size_t i;
  wchar_t* delimiter;
  wchar_t* null_terminator;

  struct Resolution temp_resolution;

  assert(resolution != NULL);
  assert(str != NULL);

  /* Parse width. */
  if (!IsNumberStartW(str[0])) {
    return NULL;
  }
  temp_resolution.width = (int)wcstol(str, &delimiter, 10);
  if (errno == ERANGE) {
    return NULL;
  }

  /* Check for 'x' delimiter. */
  if (*delimiter != L'x') {
    return NULL;
  }

  /* Parse height. */
  if (!IsNumberStartW(delimiter[1])) {
    return NULL;
  }
  temp_resolution.height = (int)wcstol(&delimiter[1], &null_terminator, 10);
  if (errno == ERANGE) {
    return NULL;
  }

  /* Check for null terminator. */
  if (*null_terminator != '\0') {
    return NULL;
  }

  *resolution = temp_resolution;
  return resolution;
}

int Resolution_Compare(
    const struct Resolution* lhs, const struct Resolution* rhs) {
  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 0;
  }

  /* Compare width. */
  if (lhs->width < rhs->width) {
    return -1;
  } else if (lhs->width > rhs->width) {
    return 1;
  }

  /* Compare height. */
  if (lhs->height < rhs->height) {
    return -1;
  } else if (lhs->height > rhs->height) {
    return 1;
  }

  return 0;
}

int Resolution_Equals(
    const struct Resolution* lhs, const struct Resolution* rhs) {
  assert(lhs != NULL);
  assert(rhs != NULL);

  if (lhs == rhs) {
    return 1;
  }

  return lhs->width == rhs->width && lhs->height == rhs->height;
}

char* Resolution_ToString(
    const struct Resolution* resolution, char* buffer, size_t* length) {
  int chars_written;

  assert(resolution != NULL);
  assert(buffer != NULL);

  chars_written = _snprintf(
      buffer,
      Resolution_kMaxLength + 1,
      "%dx%d",
      resolution->width,
      resolution->height);
  buffer[Resolution_kMaxLength] = '\0';

  if (length != NULL) {
    *length = chars_written;
  }

  return buffer;
}

wchar_t* Resolution_ToWString(
    const struct Resolution* resolution, wchar_t* buffer, size_t* length) {
  int chars_written;

  assert(resolution != NULL);
  assert(buffer != NULL);

  chars_written = _snwprintf(
      buffer,
      Resolution_kMaxLength + 1,
      L"%dx%d",
      resolution->width,
      resolution->height);
  buffer[Resolution_kMaxLength] = '\0';

  if (length != NULL) {
    *length = chars_written;
  }

  return buffer;
}
