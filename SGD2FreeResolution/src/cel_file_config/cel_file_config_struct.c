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

#include "cel_file_config_struct.h"

#include "../cel_file/cel_file_interface_bar_background.h"

const struct CelFileConfig CelFileConfig_kDefault[] = {
    /* interface_bar_background_left */
    {
        CEL_FILE_INTERFACE_BAR_BACKGROUND_LEFT_PATH_DEFAULT,

        /* CelFileConfig_DrawSetting */
        {
            /* CelFileConfig_OriginPoint */
            {
                CelFileConfig_PointType_kPercent,
                { 0, CelFileConfig_kPercent100 },
            },

            /* CelFileConfig_DestPosition */
            {
                { 0, CelFileConfig_kPercent100 },
                { 117 + 48, 0 }
            },

            /* width and height */
            20,
            47
        }
    },

    /* interface_bar_background_left_center */
    {
        CEL_FILE_INTERFACE_BAR_BACKGROUND_LEFT_CENTER_PATH_DEFAULT,

        /* CelFileConfig_RepeatDrawSetting */
        {
            CelFileConfig_RepeatAlignHorizontal_kLeft,
            CelFileConfig_RepeatAlignVertical_kBottom,

            /* CelFileConfig_DestPosition */
            {
                { 0, CelFileConfig_kPercent100 },
                { (117 + 48) + 20, 0 }
            },
            221,
            47
        }
    },
};
