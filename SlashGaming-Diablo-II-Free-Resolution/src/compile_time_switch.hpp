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

#ifndef SGD2FR_COMPILE_TIME_SWITCH_HPP_
#define SGD2FR_COMPILE_TIME_SWITCH_HPP_

/**
 * Strictly a place where compile-time switch can be easily changed to
 * alter software behavior.
 */

/**
 * If true, allow the user to configure the asset paths. Useful for
 * debugging purposes or for customization-centric users.
 */
constexpr bool kIsAssetsPathCustomizable = false;

/**
 * If true, a custom MPQ will be used to store the additional assets
 * required. Set to false if running a mod where it will be stored in
 * Patch_D2.mpq instead.
 */
constexpr bool kIsLoadCustomMpq = true;

/**
 * If true, the inventory arrangement sources from 800x600 entries in
 * calculations. Otherwise, sources from 640x480 entries.
 *
 * Warning: Setting this value to true will make inventory slots for
 * heights less than 600 display incorrect.
 */
constexpr bool kIsSourceInventoryArrange800 = false;

#endif // SGD2FR_COMPILE_TIME_SWITCH_HPP_
