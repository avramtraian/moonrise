/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#pragma once

#include <AT/Error.h>
#include <AT/Optional.h>
#include <AT/String.h>

namespace GUI::Native {

enum class WindowStartMaximized : u8 {
    No = 0,
    Yes = 1,
};

enum class WindowStartInFullscreen : u8 {
    No = 0,
    Yes = 1,
};

// The implementation of all the native window API are placed in the corresponding platform-specific file.
// For example, the Windows implementation of the native window is located in "Native/Windows/WindowsNativeWindow.cpp".
class Window {
public:
    Window() = default;
    ~Window() = default;

    // If the width (or height) optional value is not set, the window will be created using the default implementation value.
    ErrorOr<void> initialize(
        Optional<u32> width,
        Optional<u32> height,
        WindowStartMaximized start_maximized,
        WindowStartInFullscreen start_in_fullscreen,
        const String& title
    );

    void destroy();

public:
    NODISCARD ALWAYS_INLINE void* get_handle() const { return m_native_handle; }

private:
    void* m_native_handle { nullptr };
};

} // namespace GUI::Native
