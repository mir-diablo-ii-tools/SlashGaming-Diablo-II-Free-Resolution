;
; SlashGaming Diablo II Free Resolution
; Copyright (C) 2019-2024  Mir Drualga
;
; This file is part of SlashGaming Diablo II Free Resolution.
;
;  This program is free software: you can redistribute it and/or modify
;  it under the terms of the GNU Affero General Public License as published
;  by the Free Software Foundation, either version 3 of the License, or
;  (at your option) any later version.
;
;  This program is distributed in the hope that it will be useful,
;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;  GNU Affero General Public License for more details.
;
;  You should have received a copy of the GNU Affero General Public License
;  along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
;  Additional permissions under GNU Affero General Public License version 3
;  section 7
;
;  If you modify this Program, or any covered work, by linking or combining
;  it with Diablo II (or a modified version of that game and its
;  libraries), containing parts covered by the terms of Blizzard End User
;  License Agreement, the licensors of this Program grant you additional
;  permission to convey the resulting work. This additional permission is
;  also extended to any combination of expansions, mods, and remasters of
;  the game.
;
;  If you modify this Program, or any covered work, by linking or combining
;  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
;  Glide, OpenGL, or Rave wrapper (or modified versions of those
;  libraries), containing parts not covered by a compatible license, the
;  licensors of this Program grant you additional permission to convey the
;  resulting work.
;
;  If you modify this Program, or any covered work, by linking or combining
;  it with any library (or a modified version of that library) that links
;  to Diablo II (or a modified version of that game and its libraries),
;  containing parts not covered by a compatible license, the licensors of
;  this Program grant you additional permission to convey the resulting
;  work.
;

global _D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01
global _D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc03
global _D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc04

extern _Sgd2fr_D2Client_GetResolutionRegistry

section .data

section .bss

section .text

;
; External
;

_D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc01:
    push ebp
    mov ebp, esp

    sub esp, 4

    push eax
    push ecx
    push edx

    lea ecx, dword [ebp - 4]
    push ecx
    push eax
    call _Sgd2fr_D2Client_GetResolutionRegistry
    add esp, 8

    pop edx
    pop ecx
    pop eax

    mov esi, dword [ebp - 4]
    add esp, 4

    leave
    ret

_D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc03:
    push ebp
    mov ebp, esp

    sub esp, 4

    push eax
    push ecx
    push edx

    lea ecx, dword [ebp - 4]
    push ecx
    push edi
    call _Sgd2fr_D2Client_GetResolutionRegistry
    add esp, 8

    pop edx
    pop ecx
    pop eax

    mov esi, dword [ebp - 4]
    add esp, 4

    leave
    ret

_D2Client_GetResolutionRegistryPatch_1_13C_InterceptionFunc04:
    push ebp
    mov ebp, esp

    sub esp, 4

    push eax
    push ecx
    push edx

    lea eax, dword [ebp - 4]
    push eax
    push ecx
    call _Sgd2fr_D2Client_GetResolutionRegistry
    add esp, 8

    pop edx
    pop ecx
    pop eax

    mov esi, dword [ebp - 4]
    add esp, 4

    leave
    ret
