/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2021  Mir Drualga
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

#ifndef SGD2FR_CEL_FILE_CONFIG_CEL_FILE_DRAW_SETTING_H_
#define SGD2FR_CEL_FILE_CONFIG_CEL_FILE_DRAW_SETTING_H_

enum CelFileConfig_PointType {
  CelFileConfig_PointType_kUnspecified = 0,
  CelFileConfig_PointType_kPercent = 1,
  CelFileConfig_PointType_kValue = 2,
};

enum {
  CelFileConfig_kPercent100 = 10000,
  CelFileConfig_kPercent50 =
      CelFileConfig_kPercent100 / 2,
  CelFileConfig_kPercent25 =
      CelFileConfig_kPercent50 / 2,
  CelFileConfig_kPercent75 = CelFileConfig_kPercent50
      + CelFileConfig_kPercent25,
};

struct CelFileConfig_PointPercent {
  /* Values must be between 0 to 10000. */
  int x_percent;
  int y_percent;
};

struct CelFileConfig_PointValue {
  int x_value;
  int y_value;
};

struct CelFileConfig_OriginPoint {
  enum CelFileConfig_PointType type;

  union {
    struct CelFileConfig_PointPercent percent;
    struct CelFileConfig_PointValue value;
  };
};

struct CelFileConfig_DestPosition {
  /* Determines the destination position to draw the Cel File. */
  struct CelFileConfig_PointPercent position;

  /* Determines the offset to apply after position percent calculations. */
  struct CelFileConfig_PointValue offset;
};

struct CelFileConfig_DrawSetting {
  /* Determines the origin point in the Cel File. */
  struct CelFileConfig_OriginPoint origin;

  /* Determines the destination position to draw the Cel File. */
  struct CelFileConfig_DestPosition destination;

  /*
   * Determines the width and height of the combined Cel File. Used
   * for row width detection and sanity checks.
   */
  int width;
  int height;
};

enum CelFileConfig_RepeatAlignmentHorizontal {
  CelFileConfig_RepeatAlignHorizontal_kUnspecified = 0,
  CelFileConfig_RepeatAlignHorizontal_kLeft = 1,
  CelFileConfig_RepeatAlignHorizontal_kRight = 2,
};

enum CelFileConfig_RepeatAlignVertical {
  CelFileConfig_RepeatAlignVertical_kUnspecified = 0,
  CelFileConfig_RepeatAlignVertical_kBottom = 1,
  CelFileConfig_RepeatAlignVertical_kTop = 2,
};

struct CelFileConfig_RepeatDrawSetting {
  /* Determines the alignment of the repeated Cel File. */
  enum CelFileConfig_RepeatAlignHorizontal align_horizontal;
  enum CelFileConfig_RepeatAlignVertical align_vertical;

  /* Determines the position to draw the repeated Cel File. */
  struct CelFileConfig_DestPosition destination;

  /*
   * Determines the width and height for a complete cycle of a
   * repeatable Cel File. Used for row width detection and sanity
   * checks.
   */
  int width;
  int height;
};

#endif /* SGD2FR_CEL_FILE_CONFIG_CEL_FILE_DRAW_SETTING_H_ */
