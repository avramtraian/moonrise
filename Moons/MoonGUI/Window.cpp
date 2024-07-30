/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#include <MoonGUI/Application.h>
#include <MoonGUI/Window.h>

namespace GUI {

ErrorOr<RefPtr<Window>> Window::construct(Application& application, WindowMode start_mode, Optional<u32> width, Optional<u32> height)
{
    RefPtr<Window> window = adopt_ref(new Window());
    if (!window.is_valid())
        return Error::OutOfMemory;

    // Depending on the implementation of the native window, the platform-specific layer might require the
    // window to be already registered by the time the native window initialization function is invoked.
    application.register_window(window);

    TRY(window->m_native_window.initialize(
        width,
        height,
        start_mode == WindowMode::Maximized ? Native::WindowStartMaximized::Yes : Native::WindowStartMaximized::No,
        Native::WindowStartInFullscreen::No,
        "Moonrise Default Window"sv
    ));

    return window;
}

Window::~Window()
{
    m_native_window.destroy();
}

} // namespace GUI
