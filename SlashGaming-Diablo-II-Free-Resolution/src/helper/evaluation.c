/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2023  Mir Drualga
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

#include "evaluation.h"

#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define EVALUATORS L""

void ShowEvaluationMessage(void) {
  MessageBoxW(
      NULL,
      L"This version of SGD2FreeRes is evaluation software. It is "
          L"normally licensed under the AGPLv3, but the copyright "
          L"holder(s) have permitted temporary internal proprietary "
          L"use by " EVALUATORS L".",
      L"Notice",
      MB_OK
  );
}

void EnforceTimeLimit(void) {
  time_t current_time;
  struct tm dead_tm = { 0 };
  time_t dead_time;

  dead_tm.tm_year = 2021 - 1900;
  dead_tm.tm_mon = 4;
  dead_tm.tm_mday = 1;

  dead_time = mktime(&dead_tm);
  current_time = time(NULL);

  if (difftime(dead_time, current_time) < 0) {
    MessageBoxW(
        NULL,
        L"SGD2FreeRes's evaluation software trial has expired.",
        L"Error",
        MB_OK
    );

    exit(EXIT_FAILURE);
  }
}
