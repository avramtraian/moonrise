/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#include <MoonCore/Log.h>
#include <MoonGUI/Native/NativeWindow.h>
#include <MoonGUI/Native/Windows/WindowsHeaders.h>

namespace GUI::Native {

ErrorOr<void> Window::initialize(
    Optional<u32> width, Optional<u32> height, WindowStartMaximized start_maximized, WindowStartInFullscreen start_in_fullscreen, const String& title
)
{
    static bool s_is_window_class_registered = false;
    if (!s_is_window_class_registered) {
        WNDCLASSA window_class = {};
        window_class.lpszClassName = "MoonriseDefaultWindowClass";
        window_class.hInstance = GetModuleHandle(nullptr);
        window_class.lpfnWndProc = DefWindowProcA;

        RegisterClassA(&window_class);
        s_is_window_class_registered = true;
    }

    DWORD window_style_flags = WS_VISIBLE;

    if (start_in_fullscreen == WindowStartInFullscreen::No)
        window_style_flags |= WS_OVERLAPPEDWINDOW;

    if (start_maximized == WindowStartMaximized::Yes)
        window_style_flags |= WS_MAXIMIZE;

    m_native_handle = CreateWindowA(
        "MoonriseDefaultWindowClass",
        title.c_str(),
        window_style_flags,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        static_cast<int>(width.value_or(static_cast<u32>(CW_USEDEFAULT))),
        static_cast<int>(height.value_or(static_cast<u32>(CW_USEDEFAULT))),
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    if (m_native_handle == nullptr) {
        errorln("Failed to create the native window instance!"sv);
        return Error::Unknown;
    }

    return {};
}

void Window::destroy()
{
    if (m_native_handle == nullptr)
        return;

    DestroyWindow(static_cast<HWND>(m_native_handle));
    m_native_handle = nullptr;
}

} // namespace GUI::Native
