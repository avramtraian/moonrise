/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#pragma once

#include <AT/Error.h>
#include <AT/RefPtr.h>
#include <MoonGUI/Forward.h>
#include <MoonGUI/Native/NativeWindow.h>

namespace GUI {

enum class WindowMode : u8 {
    Default = 0,
    Maximized,
    Minimized,
    Fullscreen,
};

class Window : public RefCounted {
public:
    // The width and height parameters are always ignored if the provided starting mode requires fixed window dimensions,
    // usually determined by the monitor properties. If the start mode doesn't require fixed window dimensions, but the optionals
    // are empty, the implementation will use the default values.
    GUI_API static ErrorOr<RefPtr<Window>> construct(Application& application, WindowMode start_mode, Optional<u32> width, Optional<u32> height);

    GUI_API virtual ~Window() override;

public:
    Native::Window& native() { return m_native_window; }
    const Native::Window& native() const { return m_native_window; }

private:
    Window() = default;

private:
    Native::Window m_native_window;
};

} // namespace GUI
