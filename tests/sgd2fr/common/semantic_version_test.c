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

  return suite;
}
