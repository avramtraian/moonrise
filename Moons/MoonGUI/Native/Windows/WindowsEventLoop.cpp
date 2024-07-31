/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#include <MoonCore/Log.h>
#include <MoonGUI/Native/EventLoop.h>
#include <MoonGUI/Native/Windows/WindowsHeaders.h>

namespace GUI::Native {

ErrorOr<void> EventLoop::enter_locking_event_loop()
{
    if (m_event_callback == nullptr) {
        // This is an invalid state as there is no way to exit the event loop, as no external code will ever be reached again.
        errorln("Trying to enter a locking event loop without a callback being set!"sv);
        return Error::InvalidParameter;
    }

    // Set the value of the optional as false.
    m_should_exit_locking_event_loop = false;

    MSG message = {};
    while (GetMessageA(&message, nullptr, 0, 0) >= 0) {
        // Dispatch the platform window messages.
        TranslateMessage(&message);
        DispatchMessageA(&message);

        // Check if we should exit the locking event loop.
        AT_ASSERT(m_should_exit_locking_event_loop.has_value());
        if (m_should_exit_locking_event_loop.value())
            break;
    }

    return {};
}

void EventLoop::exit_locking_event_loop()
{
    if (!m_should_exit_locking_event_loop.has_value()) {
        errorln("Trying to exit from a locking event loop but none is currently active!"sv);
        return;
    }

    m_should_exit_locking_event_loop = true;
}

} // namespace GUI::Native
