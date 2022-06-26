/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2022  Mir Drualga
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

/*
  SlashGaming Diablo II Free Resolution utilizes the API of D2DX.
  This is the text from D2DX's file's license header:

  This file is part of D2DX.

  Copyright (C) 2021  Bolrog

  D2DX is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  D2DX is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with D2DX.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "glide3x_d2dx.hpp"

#include <filesystem>

#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.hpp>

/*
  ID2DXConfigurator is a pseudo-COM interface that can be used to integrate with D2DX.
  It is suitable e.g. for "high-res" mods that want to use arbitrary resolutions.
  It can be accessed via the helper d2dx::TryGetConfigurator, or manually by 
  using LoadLibrary/GetProcAddress to get a pointer to _D2DXGetConfigurator@4.
  Note that the object is not really refcounted and there's no need to call AddRef/Release.
  Example use:
    ID2DXConfigurator* d2dxConfigurator = d2dx::TryGetConfigurator();
    if (d2dxConfigurator)
    {
      d2dxConfigurator->SetCustomResolution(1000, 500);
    }
    grSstWinOpen(hWnd, ...)
*/
MIDL_INTERFACE("B11C5FA4-983F-4E34-9E43-BD82F9CCDB65")
ID2DXConfigurator : public IUnknown
{
public:
  /*
    Tell D2DX that the following call(s) to grSstWinOpen intends this custom resolution,
    and to ignore the 'screen_resolution' argument. To return to normal behavior, call
    this method with a width and height of zero.
    Returns S_OK on success and an HRESULT error code otherwise.
  */
  virtual HRESULT STDMETHODCALLTYPE SetCustomResolution(
    int width,
    int height) = 0;

  /*
    Get a suggested custom resolution from D2DX (typically close to 640x480 or 800x600,
    but in the aspect ratio of the monitor).
    This method allows matching D2DX's default behavior.
    Returns S_OK on success and an HRESULT error code otherwise.
  */
  virtual HRESULT STDMETHODCALLTYPE GetSuggestedCustomResolution(
    /* [out] */ int* width,
    /* [out] */ int* height) = 0;
};

/*
* This is the declaration of function that needs to be loaded via
* GetProcAddress.
*/

#if 0

extern "C" {

D2DX_EXPORTED ID2DXConfigurator* __stdcall D2DXGetConfigurator();

} // extern "C"

#endif // 0

namespace sgd2fr {
namespace d2dx_glide {
namespace {

typedef ID2DXConfigurator* (__stdcall *GetConfiguratorFuncType)(void);

static const char* const kGetConfiguratorFuncName =
    "_D2DXGetConfigurator@0";

static GetConfiguratorFuncType GetConfiguratorFunc() {
  HMODULE glide3x_handle = GetModuleHandleW(L"glide3x.dll");
  if (glide3x_handle == nullptr) {
    ::mdc::error::ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"GetModuleHandleW",
        GetLastError()
    );

    return nullptr;
  }

  FARPROC raw_func_ptr = GetProcAddress(
      glide3x_handle,
      kGetConfiguratorFuncName
  );

  if (raw_func_ptr == nullptr) {
    ::mdc::error::ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        L"GetProcAddress",
        GetLastError()
    );

    return nullptr;
  }

  return reinterpret_cast<GetConfiguratorFuncType>(raw_func_ptr);
}

static ID2DXConfigurator* D2DXGetConfigurator() {
  static ID2DXConfigurator* configurator = GetConfiguratorFunc()();

  return configurator;
}

} // namespace

bool IsD2dxGlideWrapper(const wchar_t* path) {
  if (!::std::filesystem::exists(path)) {
    return false;
  }

  HMODULE glide3x_handle = GetModuleHandleW(path);
  bool is_library_already_loaded = (glide3x_handle != nullptr);

  if (!is_library_already_loaded) {
    glide3x_handle = LoadLibraryW(path);
  }

  if (glide3x_handle == nullptr) {
    ::mdc::error::ExitOnWindowsFunctionError(
        __FILEW__,
        __LINE__,
        is_library_already_loaded
            ? L"GetModuleHandleW"
            : L"LoadLibraryW",
        GetLastError()
    );

    return false;
  }

  FARPROC get_configurator_func = GetProcAddress(
      glide3x_handle,
      kGetConfiguratorFuncName
  );

  if (!is_library_already_loaded) {
    FreeLibrary(glide3x_handle);
  }

  return (get_configurator_func != nullptr);
}

HRESULT SetCustomResolution(
    int width,
    int height
) {
  return D2DXGetConfigurator()->SetCustomResolution(width, height);
}

HRESULT GetSuggestedCustomResolution(
    /* [out] */ int* width,
    /* [out] */ int* height
) {
  return D2DXGetConfigurator()->GetSuggestedCustomResolution(width, height);
}

} // namespace d2dx_glide
} // namespace sgd2fr
