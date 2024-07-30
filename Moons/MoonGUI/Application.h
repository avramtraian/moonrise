/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#pragma once

#include <AT/Error.h>
#include <AT/Vector.h>
#include <MoonGUI/GUI.h>
#include <MoonGUI/Window.h>

namespace GUI {

class Application {
    AT_MAKE_NONCOPYABLE(Application);
    AT_MAKE_NONMOVABLE(Application);

public:
    GUI_API static ErrorOr<void> construct();
    GUI_API static void destruct();

    NODISCARD GUI_API static Application& get();

public:
    // Returns an empty optional if there is no registered window with the provided native handle.
    GUI_API Optional<RefPtr<Window>> get_window_from_native_handle(void* window_native_handle);

    // Returns a vector of windows that don't have a valid native handle yet. Depending on the native window
    // implementation, the window might be registered before the native handle is available.
    GUI_API Vector<RefPtr<Window>> get_windows_without_valid_native_handles();

    void register_window(RefPtr<Window> window);
    void unregister_window(const RefPtr<Window>& window);

private:
    Application() = default;
    ~Application() = default;

private:
    Vector<RefPtr<Window>> m_windows;
};

} // namespace GUI
