/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#include <AT/OwnPtr.h>
#include <MoonCore/Log.h>
#include <MoonGUI/Application.h>

namespace GUI {

static Application* s_application_instance;

ErrorOr<void> Application::construct()
{
    if (s_application_instance) {
        errorln("The application instance was already initialized!"sv);
        return Error::Unknown;
    }

    s_application_instance = new Application;
    if (!s_application_instance)
        return Error::OutOfMemory;
    return {};
}

void Application::destruct()
{
    if (!s_application_instance) {
        errorln("The application instance was already destroyed!"sv);
        return;
    }

    // Report if any window is referenced by anyone except the application instance.
    for (const auto& window : s_application_instance->m_windows) {
        if (window->get_reference_count() != 1) {
            // By the time the global application instance is destroyed, all widgets or objects that hold
            // a reference to a window should have been destroyed. This is most likely a memory leak!
            errorln("Window with native handle '{}' has an invalid reference count!"sv, window->native().get_handle());
        }
    }

    s_application_instance->m_windows.clear_and_shrink();

    // Release the application instance memory.
    delete s_application_instance;
    s_application_instance = nullptr;
}

Application& Application::get()
{
    AT_ASSERT(s_application_instance);
    return *s_application_instance;
}

Optional<RefPtr<Window>> Application::get_window_from_native_handle(void* window_native_handle)
{
    if (window_native_handle == nullptr) {
        // If the caller expects this function to return the window with an invalid native handle,
        // they should use the 'get_windows_without_valid_native_handles' function.
        warnln("Trying to invoke 'get_window_from_native_handle' for an invalid native handle is not supported."sv);
        return {};
    }

    for (const auto& window : m_windows) {
        if (window->native().get_handle() == window_native_handle)
            return window;
    }

    // There is no registered window with the provided native handle.
    return {};
}

Vector<RefPtr<Window>> Application::get_windows_without_valid_native_handles()
{
    Vector<RefPtr<Window>> windows_without_valid_native_handles;
    for (const auto& window : m_windows) {
        if (window->native().get_handle() == nullptr)
            windows_without_valid_native_handles.add(window);
    }

    return windows_without_valid_native_handles;
}

void Application::register_window(RefPtr<Window> window)
{
    bool window_is_already_registered = false;

    for (const auto& registered_window : m_windows) {
        if (window->native().get_handle() == registered_window->native().get_handle()) {
            window_is_already_registered = true;
            break;
        }
    }

    if (window_is_already_registered) {
        errorln("The window with native handle '{}' is already registered by the application!"sv, window->native().get_handle());
        return;
    }

    m_windows.add(move(window));
}

void Application::unregister_window(const RefPtr<Window>& window)
{
    Optional<usize> window_index;
    for (usize index = 0; index < m_windows.count(); ++index) {
        if (window->native().get_handle() == m_windows[index]->native().get_handle()) {
            window_index = index;
            break;
        }
    }

    if (!window_index.has_value()) {
        errorln("The window with native handle '{}' was already unregistered by the application!"sv, window->native().get_handle());
        return;
    }

    m_windows.remove(window_index.value());
}

} // namespace GUI
