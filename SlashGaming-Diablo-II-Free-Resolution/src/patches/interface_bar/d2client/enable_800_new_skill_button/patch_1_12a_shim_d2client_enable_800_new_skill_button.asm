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

global _D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc01
global _D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc03
global _D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc06
global _D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc11
global _D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc12
global _D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc13
global _D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc17

extern _Sgd2fr_D2Client_Get800NewSkillButtonEnabledValue
extern _Sgd2fr_D2Client_IsMouseOver800NewSkillButton
extern _Sgd2fr_D2Client_Set800NewSkillPopupText
extern _Sgd2fr_D2Client_Draw800NewSkillButton

section .data

section .bss

section .text

;
; External
;

_D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc01:
    push ebp
    mov ebp, esp

    push ecx
    push edx

    call _Sgd2fr_D2Client_Get800NewSkillButtonEnabledValue

    pop edx
    pop ecx

    leave
    ret

_D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc03:
    push ebp
    mov ebp, esp

    push edx

    call _Sgd2fr_D2Client_IsMouseOver800NewSkillButton

    pop edx

    ; Affects the instructions:
    ; cmp ecx, eax
    ; jl
    mov ecx, 0

    leave
    ret

_D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc06:
    push ebp
    mov ebp, esp

    push ecx
    push edx

    call _Sgd2fr_D2Client_IsMouseOver800NewSkillButton

    pop edx
    pop ecx

    leave
    ret

_D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc11:
    push ebp
    mov ebp, esp

    push edx

    call _Sgd2fr_D2Client_IsMouseOver800NewSkillButton

    pop edx

    ; Affects the instructions:
    ; cmp eax, ecx
    ; jge
    mov ecx, eax
    mov eax, 0

    leave
    ret

_D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc12:
    push ebp
    mov ebp, esp

    push eax
    push ecx
    push edx

    call _Sgd2fr_D2Client_Set800NewSkillPopupText

    pop edx
    pop ecx
    pop eax

    leave
    ret

_D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc13:
    push ebp
    mov ebp, esp

    push ecx
    push edx

    ; Pushes the CelContext for the Level button.
    lea eax, dword [ebp + 0x20]
    push eax
    call _Sgd2fr_D2Client_Draw800NewSkillButton
    add esp, 4

    pop edx
    pop ecx

    leave
    ret

_D2Client_Enable800NewSkillButtonPatch_1_12A_InterceptionFunc17:
    push ebp
    mov ebp, esp

    push ecx
    push edx

    ; Pushes the CelContext for the Level button.
    lea eax, dword [ebp + 0x8]
    push eax
    call _Sgd2fr_D2Client_Draw800NewSkillButton
    add esp, 4

    pop edx
    pop ecx

    leave
    ret
