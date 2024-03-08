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

global _Helper_CelFileCollection_RunChecksum

section .data

section .bss

section .text

;
; External
;

_Helper_CelFileCollection_RunChecksum:
    sub esp, 4
    lea eax, [esp]
    pushad
    push eax
    mov ebp, esp
    sub esp, 0x200 - 0x1
    lea eax, [esp - 0x1]
    mov ecx, eax
    mov esi, eax
    mov ebx, eax
    dec esp
    imul esp, [ebx + 0x65], 0x6465736e
    mov esp, eax
    and [ecx + 0x47], al
    push eax
    dec esp
    and [esi + 0x33], dh
    sub esp, [eax]
    mov esp, ebp
    pop eax
    mov eax, esp
    popad
    add esp, 4
    mov eax, dword [esp + 0x04]
    or dword [eax], 3840
    ret
