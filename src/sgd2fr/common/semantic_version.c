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

#include "sgd2fr/common/semantic_version.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/**
 * Attempts to find a non-digit character in between the range [begin, end) and
 * returns a pointer to the non-digit character. If a non-digit could not be
 * found in the specified range, then the function returns the end. If a
 * non-digit could not be found within the number of characters specified as
 * the limit, then the function returns NULL.
 */
static char* FindNonDigit(const char* begin, const char* end, size_t limit) {
  const char* current;

  for (current = begin; current != end && current - begin < limit; ++current) {
    if (!isdigit(*current)) {
      return (char*)current;
    }
  }

  if (current == end) {
    return (char*)current;
  }

  return NULL;
}

/**
 * Converts a string and returns the converted value. If the function fails to
 * convert the string, such as zero length or overflow, it returns NULL.
 */
static int* ConvertStringToInt(int* dest, const char* begin, const char* end) {
  int dest_temp;
  const char* current;

  assert(dest != NULL);
  assert(begin != NULL);
  assert(end != NULL);

  if (begin == end) {
    return NULL;
  }

  /* Check for leading zero. */
  if (begin + 1 != end && begin[0] == '0') {
    return NULL;
  }

  dest_temp = 0;
  for (current = begin; current != end; ++current) {
    /* Check for overflow. */
    if (dest_temp > INT_MAX / 10) {
      return NULL;
    }

    dest_temp *= 10;
    dest_temp += *current - '0';
  }

  *dest = dest_temp;
  return dest;
}

/* Original implementation, will remove due to complexity. */
struct SemanticVersion* SemanticVersion_FromString_Original(
    struct SemanticVersion* version, const char* str, size_t length) {
  enum {
    kVersionFieldCount = 4,
    /* Length of "2000000000" (which is 2^31 - 1). */
    kIntMaxLength = 10
  };
  size_t i;
  char* begins[kVersionFieldCount];
  char* ends[kVersionFieldCount];
  int converted_values[kVersionFieldCount];

  assert(version != NULL);
  assert(str != NULL);
  if (length <= 0) {
    return NULL;
  }

  if (!isdigit(str[0])) {
    return NULL;
  }

  /* Locate the '.' delimiters and end pointer. */
  begins[0] = (char*)str;
  for (i = 0; i < kVersionFieldCount; ++i) {
    ends[i] = FindNonDigit(begins[i], &str[length], kIntMaxLength + 1);
    if (ends[i] == NULL) {
      return NULL;
    }

    if (ends[i] == &str[length]) {
      break;
    }

    if (i != kVersionFieldCount - 1) {
      begins[i + 1] = ends[i] + 1;
    }
  }

  /* Check that all delimiters are '.' chars. */
  for (i = 0; i < kVersionFieldCount - 1; ++i) {
    if (ends[i] == &str[length] || ends[i][0] != '.') {
      return NULL;
    }
  }

  /* Check that the last end is the end pointer. */
  if (ends[kVersionFieldCount - 1] != &str[length]) {
    return NULL;
  }

  /* Check the lengths between delimiters. */
  for (i = 0; i < kVersionFieldCount; ++i) {
    size_t section_length;

    section_length = ends[i] - begins[i];
    if (section_length <= 0 || section_length > kIntMaxLength) {
      return NULL;
    }
  }

  /* Convert delimited strings to int. */
  for (i = 0; i < kVersionFieldCount; ++i) {
    int* convert_result;

    convert_result =
        ConvertStringToInt(&converted_values[i], begins[i], ends[i]);
    if (convert_result == NULL) {
      return NULL;
    }
  }

  version->major_version = converted_values[0];
  version->minor_version = converted_values[1];
  version->patch_version = converted_values[2];
  version->build_version = converted_values[3];

  return version;
}

/**
 * External
 */

struct SemanticVersion* SemanticVersion_FromString(
    struct SemanticVersion* version, const char* str, size_t length) {
  struct SemanticVersion temp_version;

  size_t i;
  int successful_assigns;
  int chars_read;
  int build_length;

  if (length < SemanticVersion_kMinLength
      || length > SemanticVersion_kMaxLength) {
    return NULL;
  }

  /*
   * Check for only valid characters, that being digits and '.' delimiter. Also
   * prevents negative values by blocking the '-' char.
   */
  for (i = 0; i < length; ++i) {
    if (!isdigit(str[i]) && str[i] != '.') {
      return NULL;
    }
  }

  /* Check for any leading zeros. */
  if (str[0] == '0' && isdigit(str[1])) {
    return NULL;
  }
  for (i = 2; i < length; ++i) {
    if (str[i - 2] == '.' && str[i - 1] == '0' && isdigit(str[i])) {
      return NULL;
    }
  }

  successful_assigns =
      sscanf(
          str,
          "%d.%d.%d.%d%n",
          &temp_version.major_version,
          &temp_version.minor_version,
          &temp_version.patch_version,
          &temp_version.build_version,
          &chars_read);
  if (successful_assigns != 4) {
    return NULL;
  }

  /* Detect suffix '.' chars. */
  if (chars_read < length) {
    return NULL;
  }

  /* Remove digits for trailing chars in build version, to match length. */
  build_length = chars_read - length;
  if (build_length > 0) {
    for (i = 0; i < build_length; ++i) {
      temp_version.build_version /= 10;
      if (temp_version.build_version == 0) {
        return NULL;
      }
    }
  }

  *version = temp_version;
  return version;
}

int SemanticVersion_Compare(
    const struct SemanticVersion* lhs, const struct SemanticVersion* rhs) {
  if (lhs == rhs) {
    return 0;
  }

  if (lhs->major_version < rhs->major_version) {
    return -1;
  } else if (lhs->major_version > rhs->major_version) {
    return 1;
  }

  if (lhs->minor_version < rhs->minor_version) {
    return -1;
  } else if (lhs->minor_version > rhs->minor_version) {
    return 1;
  }

  if (lhs->patch_version < rhs->patch_version) {
    return -1;
  } else if (lhs->patch_version > rhs->patch_version) {
    return 1;
  }

  if (lhs->build_version < rhs->build_version) {
    return -1;
  } else if (lhs->build_version > rhs->build_version) {
    return 1;
  } else {
    return 0;
  }
}

int SemanticVersion_Equals(
    const struct SemanticVersion* lhs, const struct SemanticVersion* rhs) {
  if (lhs == rhs) {
    return 1;
  }

  return lhs->major_version == rhs->major_version
      && lhs->minor_version == rhs->minor_version
      && lhs->patch_version == rhs->patch_version
      && lhs->build_version == rhs->build_version;
}

char* SemanticVersion_ToString(
    const struct SemanticVersion* version, char* buffer, size_t* length) {
  int chars_written;

  assert(version != NULL);
  assert(buffer != NULL);

  assert(version->major_version >= 0);
  assert(version->minor_version >= 0);
  assert(version->patch_version >= 0);
  assert(version->build_version >= 0);

  chars_written = _snprintf(
      buffer,
      SemanticVersion_kMaxLength + 1,
      "%d.%d.%d.%d",
      version->major_version,
      version->minor_version,
      version->patch_version,
      version->build_version);
  buffer[SemanticVersion_kMaxLength] = '\0';

  if (length != NULL) {
    *length = chars_written;
  }

  return buffer;
}
