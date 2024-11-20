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

#include "sgd2fr/common/position_test.h"

#include <CuTest.h>

#include "sgd2fr/common/position.h"

static void Equals_SamePosition_ReturnsTrue(CuTest* tc) {
  struct Position pos = { 42, 1337 };

  CuAssertTrue(tc, Position_Equals(&pos, &pos));
}

static void Equals_EqualPositions_ReturnsTrue(CuTest* tc) {
  struct Position lhs = { 640, 480 };
  struct Position rhs = { 640, 480 };

  CuAssertTrue(tc, Position_Equals(&lhs, &rhs));
}

static void Equals_DifferentXs_ReturnsTrue(CuTest* tc) {
  struct Position lhs = { 640, 480 };
  struct Position rhs = { 800, 480 };

  CuAssertTrue(tc, !Position_Equals(&lhs, &rhs));
}

static void Equals_DifferentYs_ReturnsTrue(CuTest* tc) {
  struct Position lhs = { 640, 480 };
  struct Position rhs = { 640, 600 };

  CuAssertTrue(tc, !Position_Equals(&lhs, &rhs));
}

static void Equals_DifferentXsAndYs_ReturnsTrue(CuTest* tc) {
  struct Position lhs = { 42, 1337 };
  struct Position rhs = { 1337, 42 };

  CuAssertTrue(tc, !Position_Equals(&lhs, &rhs));
}

static void Compare_SamePosition_ReturnsZero(CuTest* tc) {
  struct Position pos = { 42, 1337 };

  CuAssertIntEquals(tc, 0, Position_Compare(&pos, &pos));
}

static void Compare_EqualPositions_ReturnsZero(CuTest* tc) {
  struct Position lhs = { 640, 480 };
  struct Position rhs = { 640, 480 };

  CuAssertIntEquals(tc, 0, Position_Compare(&lhs, &rhs));
}

static void Compare_LtXs_ReturnsNegative(CuTest* tc) {
  struct Position lhs = { 640 - 1, 480 };
  struct Position rhs = { 640, 480 };

  CuAssertTrue(tc, Position_Compare(&lhs, &rhs) < 0);
}

static void Compare_GtXs_ReturnsPositive(CuTest* tc) {
  struct Position lhs = { 640 + 1, 480 };
  struct Position rhs = { 640, 480 };

  CuAssertTrue(tc, Position_Compare(&lhs, &rhs) > 0);
}

static void Compare_LtYs_ReturnsNegative(CuTest* tc) {
  struct Position lhs = { 640, 480 - 1 };
  struct Position rhs = { 640, 480 };

  CuAssertTrue(tc, Position_Compare(&lhs, &rhs) < 0);

}

static void Compare_GtYs_ReturnsPositive(CuTest* tc) {
  struct Position lhs = { 640, 480 + 1 };
  struct Position rhs = { 640, 480 };

  CuAssertTrue(tc, Position_Compare(&lhs, &rhs) > 0);
}

static void Compare_DifferentXsAndYs_ReturnsNonZero(CuTest* tc) {
  struct Position lhs = { 640 - 1, 480 + 1 };
  struct Position rhs = { 640, 480 };

  CuAssertTrue(tc, Position_Compare(&lhs, &rhs) != 0);
}

/**
 * External
 */

CuSuite* Position_GetTestSuite() {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, Equals_SamePosition_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_EqualPositions_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentXs_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentYs_ReturnsTrue);
  SUITE_ADD_TEST(suite, Equals_DifferentXsAndYs_ReturnsTrue);

  SUITE_ADD_TEST(suite, Compare_SamePosition_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_EqualPositions_ReturnsZero);
  SUITE_ADD_TEST(suite, Compare_LtXs_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtXs_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_LtYs_ReturnsNegative);
  SUITE_ADD_TEST(suite, Compare_GtYs_ReturnsPositive);
  SUITE_ADD_TEST(suite, Compare_DifferentXsAndYs_ReturnsNonZero);

  return suite;
}