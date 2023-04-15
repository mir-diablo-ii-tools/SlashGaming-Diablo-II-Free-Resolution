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

#include "checksum_hash.h"

#include <stddef.h>
#include <stdio.h>
#include <windows.h>

#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.h>

static HCRYPTPROV crypt_provider;
static int is_crypt_provider_init = 0;

static void InitCryptProvider(void) {
  BOOL is_crypt_acquire_context_success;

  if (is_crypt_provider_init) {
    return;
  }

  is_crypt_acquire_context_success = CryptAcquireContextW(
      &crypt_provider,
      NULL,
      NULL,
      PROV_RSA_FULL,
      CRYPT_VERIFYCONTEXT);

  if (!is_crypt_acquire_context_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"CryptAcquireContextW",
        GetLastError());
    goto return_bad;
  }

  is_crypt_provider_init = 1;

  return;

return_bad:
  return;
}

static void DeinitCryptProvider(void) {
  BOOL is_crypt_release_context_success;

  if (!is_crypt_provider_init) {
    return;
  }

  is_crypt_release_context_success = CryptReleaseContext(crypt_provider, 0);

  if (!is_crypt_release_context_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"CryptReleaseContext",
        GetLastError());
    goto return_bad;
  }

  is_crypt_provider_init = 0;

  return;

return_bad:
  return;
}

/**
 * External
 */

void Sha1_GenerateHash(
    char* sha1_str,
    const char* data,
    size_t data_length) {
  size_t i;
  BOOL is_crypt_create_hash_success;
  BOOL is_crypt_destroy_hash_success;
  BOOL is_crypt_hash_data_success;
  BOOL is_crypt_get_hash_param_success;

  HCRYPTHASH hash;
  BYTE sha1_data[Sha1_kLength / 2];
  size_t sha1_length;

  InitCryptProvider();

  is_crypt_create_hash_success = CryptCreateHash(
      crypt_provider,
      CALG_SHA1,
      0,
      0,
      &hash);

  if (!is_crypt_create_hash_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"CryptCreateHash",
        GetLastError());
    goto return_bad;
  }

  is_crypt_hash_data_success = CryptHashData(hash, data, data_length, 0);
  if (!is_crypt_hash_data_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"CryptHashData",
        GetLastError());
    goto crypt_destroy_hash;
  }

  sha1_length = Sha1_kLength;
  is_crypt_get_hash_param_success = CryptGetHashParam(
      hash,
      HP_HASHVAL,
      sha1_data,
      &sha1_length,
      0);
  if (!is_crypt_get_hash_param_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"CryptGetHashParam",
        GetLastError());
    goto crypt_destroy_hash;
  }

  for (i = 0; i < (Sha1_kLength / 2); ++i) {
    sprintf(&sha1_str[i * 2], "%2.2X", sha1_data[i]);
  }
  sha1_str[Sha1_kLength] = '\0';

  is_crypt_destroy_hash_success = CryptDestroyHash(hash);
  if (!is_crypt_destroy_hash_success) {
    Mdc_Error_ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"CryptDestroyHash",
        GetLastError());
    goto return_bad;
  }

  return;

crypt_destroy_hash:
  CryptDestroyHash(hash);

return_bad:
  return;
}
