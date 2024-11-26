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

#include "sgd2fr/common/semantic_version_test.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <CuTest.h>

#include "sgd2fr/common/semantic_version.h"

static void Equals_SameVersions_ReturnsTrue(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };

  CuAssertTrue(tc, SemanticVersion_Equals(&lhs, &lhs));
}

static void Equals_EqualVersions_ReturnsTrue(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 0, 0, 0 };

  CuAssertTrue(tc, SemanticVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentMajor_ReturnsFalse(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 2, 0, 0, 0 };

  CuAssertTrue(tc, !SemanticVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentMinor_ReturnsFalse(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 1, 0, 0 };

  CuAssertTrue(tc, !SemanticVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentPatch_ReturnsFalse(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 0, 1, 0 };

  CuAssertTrue(tc, !SemanticVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentBuild_ReturnsFalse(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 0, 0, 1 };

  CuAssertTrue(tc, !SemanticVersion_Equals(&lhs, &rhs));
}

static void Equals_DifferentAll_ReturnsFalse(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 2, 3, 4 };

  CuAssertTrue(tc, !SemanticVersion_Equals(&lhs, &rhs));
}

static void Compare_SameVersions_ReturnsZero(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };

  CuAssertIntEquals(tc, 0, SemanticVersion_Compare(&lhs, &lhs));
}

static void Compare_EqualVersions_ReturnsZero(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 0, 0, 0 };

  CuAssertIntEquals(tc, 0, SemanticVersion_Compare(&lhs, &rhs));
}

static void Compare_LtMajor_ReturnsNegative(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 2, 0, 0, 0 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtMajor_ReturnsPositive(CuTest* tc) {
  struct SemanticVersion lhs = { 2, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 0, 0, 0 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtMinor_ReturnsNegative(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 1, 0, 0 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtMinor_ReturnsPositive(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 2, 0, 0 };
  struct SemanticVersion rhs = { 1, 1, 0, 0 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtPatch_ReturnsNegative(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 0, 1, 0 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtPatch_ReturnsPositive(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 2, 0 };
  struct SemanticVersion rhs = { 1, 0, 1, 0 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtBuild_ReturnsNegative(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 0, 0, 1 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtBuild_ReturnsPositive(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 2 };
  struct SemanticVersion rhs = { 1, 0, 0, 1 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) > 0);
}

static void Compare_DifferentAll_ReturnsNonZero(CuTest* tc) {
  struct SemanticVersion lhs = { 1, 0, 0, 0 };
  struct SemanticVersion rhs = { 1, 2, 3, 4 };

  CuAssertTrue(tc, SemanticVersion_Compare(&lhs, &rhs) != 0);
}

static void FromString_ValidString_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 2468, 321, 42 };
  const char kStr[] = "1234.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_ValidSubString_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 2468, 321, 4 };
  const char kStr[] = "1234.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr) - 1);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_SubstringOfTerminateStringPeriod_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 2468, 321, 42 };
  const char kStr[] = "1234.2468.321.42.";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr) - 1);

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_MajorZero_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 0, 2468, 321, 42 };
  const char kStr[] = "0.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_MinorZero_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 0, 321, 42 };
  const char kStr[] = "1234.0.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_PatchZero_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 2468, 0, 42 };
  const char kStr[] = "1234.2468.0.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_BuildZero_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 2468, 321, 0 };
  const char kStr[] = "1234.2468.321.0";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_MajorIntMax_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { INT_MAX, 2468, 321, 42 };
  char kStr[64];
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", INT_MAX, 2468, 321, 42);

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_MinorIntMax_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, INT_MAX, 321, 42 };
  char kStr[64];
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", 1234, INT_MAX, 321, 42);

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_PatchIntMax_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 2468, INT_MAX, 42 };
  char kStr[64];
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", 1234, 2468, INT_MAX, 42);

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_BuildIntMax_ReturnsVersion(CuTest* tc) {
  const struct SemanticVersion kExpected = { 1234, 2468, 321, INT_MAX };
  char kStr[64];
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  sprintf(kStr, "%d.%d.%d.%d", 1234, 2468, 321, INT_MAX);

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrNotNull(tc, result);
  CuAssertTrue(tc, SemanticVersion_Equals(&actual, &kExpected));
}

static void FromString_TerminateStringPeriod_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.42.";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MajorNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "-1234.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MinorNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.-2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_PatchNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.-321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_BuildNegative_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.-42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MissingMajor_ReturnsNull(CuTest* tc) {
  const char kStr[] = ".2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MissingMinor_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234..321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MissingPatch_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468..42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MissingBuild_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_PrefixMajorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "      1234.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_SuffixMajorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234     .2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_PrefixMinorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.      2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_SuffixMinorNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468     .321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_PrefixPatchNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.      321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_SuffixPatchNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321     .42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_PrefixBuildNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.      42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_SuffixBuildNonDigit_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.42     ";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_SubstringOfValid_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr) - 2);

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_CommaDelimiters_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234,2468,321,42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MajorLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "01234.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MinorLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.02468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_PatchLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.0321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_BuildLeadingZeros_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.042";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MajorAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.2468.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_MinorAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.321.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_PatchAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.42";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void FromString_BuildAboveIntMax_ReturnsNull(CuTest* tc) {
  const char kStr[] = "1234.2468.321.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";
  struct SemanticVersion actual;
  struct SemanticVersion* result;

  result = SemanticVersion_FromString(&actual, kStr, strlen(kStr));

  CuAssertPtrEquals(tc, NULL, result);
}

static void ToString_Valid_ReturnsString(CuTest* tc) {
  struct SemanticVersion kVersion = { 1, 2, 3, 4 };
  char buffer[SemanticVersion_kMaxLength];
  size_t length;

  SemanticVersion_ToString(&kVersion, buffer, &length);
  CuAssertStrEquals(tc, "1.2.3.4", buffer);
  CuAssertIntEquals(tc, 7, length);
}

static void ToString_AllIntMax_ReturnsString(CuTest* tc) {
  struct SemanticVersion kVersion = { INT_MAX, INT_MAX, INT_MAX, INT_MAX };
  char buffer[SemanticVersion_kMaxLength];
  size_t length;

  SemanticVersion_ToString(&kVersion, buffer, &length);
  CuAssertStrEquals(tc, "2147483647.2147483647.2147483647.2147483647", buffer);
  CuAssertIntEquals(tc, SemanticVersion_kMaxLength, length);
}

/**
 * External
 */

CuSuite* SemanticVersion_GetTestSuite(void) {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, Equals_SameVersions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualVersions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentMajor_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentMinor_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentPatch_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentBuild_ReturnsFalse);
  SUITE_ADD_TEST(suite, Equals_DifferentAll_ReturnsFalse);

  SUITE_ADD_TEST(suite, Compare_SameVersions_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_EqualVersions_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_LtMajor_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtMajor_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtMinor_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtMinor_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtPatch_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtPatch_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtBuild_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtBuild_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_DifferentAll_ReturnsNonZero);

  SUITE_ADD_TEST(suite, FromString_ValidString_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_ValidSubString_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_SubstringOfTerminateStringPeriod_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_MajorZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_MinorZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_PatchZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_BuildZero_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_MajorIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_MinorIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_PatchIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_BuildIntMax_ReturnsVersion);
  SUITE_ADD_TEST(suite, FromString_TerminateStringPeriod_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MajorNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MinorNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_PatchNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_BuildNegative_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MissingMajor_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MissingMinor_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MissingPatch_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MissingBuild_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_PrefixMajorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_SuffixMajorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_PrefixMinorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_SuffixMinorNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_PrefixPatchNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_SuffixPatchNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_PrefixBuildNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_SuffixBuildNonDigit_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_SubstringOfValid_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_CommaDelimiters_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MajorLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MinorLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_PatchLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_BuildLeadingZeros_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MajorAboveIntMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_MinorAboveIntMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_PatchAboveIntMax_ReturnsNull);
  SUITE_ADD_TEST(suite, FromString_BuildAboveIntMax_ReturnsNull);

  SUITE_ADD_TEST(suite, ToString_Valid_ReturnsString);
  SUITE_ADD_TEST(suite, ToString_AllIntMax_ReturnsString);

  return suite;
}
