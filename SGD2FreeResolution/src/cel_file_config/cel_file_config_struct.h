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

#ifndef SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_STRUCT_H_
#define SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_STRUCT_H_

struct CelFileConfig_CelFile {
  char* path;
};

struct CelFileConfig_RepeatCelFile {
  char* path;
};

struct CelFileConfig {
  struct CelFileConfig_CelFile interface_bar_background_left;
  struct CelFileConfig_RepeatCelFile interface_bar_background_left_center;

  struct CelFileConfig_CelFile interface_bar_background_right;
  struct CelFileConfig_RepeatCelFile interface_bar_background_right_center;

  struct CelFileConfig_CelFile life_orb_interface;
  struct CelFileConfig_CelFile life_orb_red;
  struct CelFileConfig_CelFile life_orb_green;

  struct CelFileConfig_CelFile mana_orb_interface;
  struct CelFileConfig_CelFile mana_orb_blue;

  struct CelFileConfig_RepeatCelFile left_screen_background;
  struct CelFileConfig_RepeatCelFile right_screen_background;

  struct CelFileConfig_RepeatCelFile left_screen_background_border;
  struct CelFileConfig_RepeatCelFile right_screen_background_border;

  struct CelFileConfig_CelFile left_screen_border;
  struct CelFileConfig_CelFile right_screen_border;
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern const struct CelFileConfig CelFileConfig_kDefault;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* SGD2FR_CEL_FILE_CONFIG_CEL_FILE_CONFIG_STRUCT_H_ */
