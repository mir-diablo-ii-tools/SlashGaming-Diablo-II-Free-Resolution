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

#include "sgd2fr/common/resolution_test.h"

#include <wchar.h>

#include <CuTest.h>

#include "sgd2fr/common/resolution.h"

static const char k640x480Str[] = "640x480";
static const wchar_t k640x480WStr[] = L"640x480";
enum {
  k640x480StrLen = sizeof(k640x480Str) / sizeof(k640x480Str[0]) - 1,
  k640x480WStrLen = sizeof(k640x480WStr) / sizeof(k640x480WStr[0]) - 1
};

static void Constant_Default_Is640x480(CuTest* tc) {
  CuAssertIntEquals(tc, 640, Resolution_kDefault.width);
  CuAssertIntEquals(tc, 480, Resolution_kDefault.height);
}

static void Constant_640x480(CuTest* tc) {
  CuAssertIntEquals(tc, 640, Resolution_k640x480.width);
  CuAssertIntEquals(tc, 480, Resolution_k640x480.height);
}

static void Constant_800x600(CuTest* tc) {
  CuAssertIntEquals(tc, 800, Resolution_k800x600.width);
  CuAssertIntEquals(tc, 600, Resolution_k800x600.height);
}

static void FromString_640x480_ReturnsResolution(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, k640x480Str);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 640, resolution.width);
  CuAssertIntEquals(tc, 480, resolution.height);
}

static void FromString_Negatives_ReturnsResolution(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "-230x-900");

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, -230, resolution.width);
  CuAssertIntEquals(tc, -900, resolution.height);
}

static void FromString_CapitalDelimiter_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "640X480");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_NoWidth_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "x480");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_NoHeight_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "640x");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_WhitespacePrefix_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, " \t640x480");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_WhitespaceSuffix_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "640x480 \t");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_HyphenOnly_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "-");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_Hyphens_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "-x-");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_DelimiterOnly_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "x");

  CuAssertTrue(tc, result == NULL);
}

static void FromString_Empty_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromString(&resolution, "");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_640x480_ReturnsResolution(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, k640x480WStr);

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, 640, resolution.width);
  CuAssertIntEquals(tc, 480, resolution.height);
}

static void FromWString_Negatives_ReturnsResolution(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"-230x-900");

  CuAssertPtrNotNull(tc, result);
  CuAssertIntEquals(tc, -230, resolution.width);
  CuAssertIntEquals(tc, -900, resolution.height);
}

static void FromWString_CapitalDelimiter_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"640X480");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_NoWidth_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"x480");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_NoHeight_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"640x");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_WhitespacePrefix_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L" \t640x480");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_WhitespaceSuffix_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"640x480 \t");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_HyphenOnly_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"-");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_Hyphens_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"-x-");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_DelimiterOnly_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"x");

  CuAssertTrue(tc, result == NULL);
}

static void FromWString_Empty_ReturnsFailure(CuTest* tc) {
  struct Resolution resolution;
  struct Resolution* result;

  result = Resolution_FromWString(&resolution, L"");

  CuAssertTrue(tc, result == NULL);
}

static void Equals_SameResolution_ReturnsTrue(CuTest* tc) {
  CuAssertTrue(
      tc, Resolution_Equals(&Resolution_k640x480, &Resolution_k640x480));
}

static void Equals_EqualResolutions_ReturnsTrue(CuTest* tc) {
  struct Resolution lhs = { 640, 480 };
  struct Resolution rhs = { 640, 480 };

  CuAssertTrue(tc, Resolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentWidths_ReturnsTrue(CuTest* tc) {
  struct Resolution lhs = { 640, 480 };
  struct Resolution rhs = { 800, 480 };

  CuAssertTrue(tc, !Resolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentHeights_ReturnsTrue(CuTest* tc) {
  struct Resolution lhs = { 640, 480 };
  struct Resolution rhs = { 640, 600 };

  CuAssertTrue(tc, !Resolution_Equals(&lhs, &rhs));
}

static void Equals_DifferentWidthsAndHeights_ReturnsTrue(CuTest* tc) {
  CuAssertTrue(
      tc, !Resolution_Equals(&Resolution_k640x480, &Resolution_k800x600));
}

static void Compare_SameResolution_ReturnsZero(CuTest* tc) {
  CuAssertIntEquals(
      tc, 0, Resolution_Compare(&Resolution_k640x480, &Resolution_k640x480));
}

static void Compare_EqualResolutions_ReturnsZero(CuTest* tc) {
  struct Resolution lhs = { 640, 480 };
  struct Resolution rhs = { 640, 480 };

  CuAssertIntEquals(tc, 0, Resolution_Compare(&lhs, &rhs));
}

static void Compare_LtWidths_ReturnsNegative(CuTest* tc) {
  struct Resolution lhs = { 640 - 1, 480 };
  struct Resolution rhs = { 640, 480 };

  CuAssertTrue(tc, Resolution_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtWidths_ReturnsPositive(CuTest* tc) {
  struct Resolution lhs = { 640 + 1, 480 };
  struct Resolution rhs = { 640, 480 };

  CuAssertTrue(tc, Resolution_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtHeights_ReturnsNegative(CuTest* tc) {
  struct Resolution lhs = { 640, 480 - 1 };
  struct Resolution rhs = { 640, 480 };

  CuAssertTrue(tc, Resolution_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtHeights_ReturnsPositive(CuTest* tc) {
  struct Resolution lhs = { 640, 480 + 1 };
  struct Resolution rhs = { 640, 480 };

  CuAssertTrue(tc, Resolution_Compare(&lhs, &rhs) > 0);
}

static void Compare_DifferentWidthsAndHeights_ReturnsNonZero(CuTest* tc) {
  struct Resolution lhs = { 640 - 1, 480 + 1 };
  struct Resolution rhs = { 640, 480 };

  CuAssertTrue(tc, Resolution_Compare(&lhs, &rhs) != 0);
}

static void ToString_ReturnsString(CuTest* tc) {
  char buffer[Resolution_kMaxLength + 1];
  size_t length;

  Resolution_ToString(&Resolution_k640x480, buffer, &length);
  CuAssertStrEquals(tc, k640x480Str, buffer);
  CuAssertIntEquals(tc, 7, length);
}

static void ToWString_ReturnsString(CuTest* tc) {
  wchar_t buffer[Resolution_kMaxLength + 1];
  size_t length;

  Resolution_ToWString(&Resolution_k640x480, buffer, &length);
  CuAssertIntEquals(tc, 0, wcscmp(k640x480WStr, buffer));
  CuAssertIntEquals(tc, 7, length);
}

/**
 * External
 */

CuSuite* Resolution_GetTestSuite() {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, Constant_Default_Is640x480);
  SUITE_ADD_TEST(suite, Constant_640x480);
  SUITE_ADD_TEST(suite, Constant_800x600);

  SUITE_ADD_TEST(suite, FromString_640x480_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromString_Negatives_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromString_CapitalDelimiter_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_NoWidth_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_NoHeight_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_WhitespacePrefix_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_WhitespaceSuffix_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_HyphenOnly_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_Hyphens_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_DelimiterOnly_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromString_Empty_ReturnsFailure);

  SUITE_ADD_TEST(suite, FromWString_640x480_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromWString_Negatives_ReturnsResolution);
  SUITE_ADD_TEST(suite, FromWString_CapitalDelimiter_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_NoWidth_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_NoHeight_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_WhitespacePrefix_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_WhitespaceSuffix_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_HyphenOnly_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_Hyphens_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_DelimiterOnly_ReturnsFailure);
  SUITE_ADD_TEST(suite, FromWString_Empty_ReturnsFailure);

  SUITE_ADD_TEST(suite, Equals_SameResolution_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualResolutions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentWidths_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentHeights_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentWidthsAndHeights_ReturnsTrue);

  SUITE_ADD_TEST(suite, Compare_SameResolution_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_EqualResolutions_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_LtWidths_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtWidths_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtHeights_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtHeights_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_DifferentWidthsAndHeights_ReturnsNonZero);

  SUITE_ADD_TEST(suite, ToString_ReturnsString);
  SUITE_ADD_TEST(suite, ToWString_ReturnsString);

  return suite;
}
