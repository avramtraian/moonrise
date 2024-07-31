/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#pragma once

#include <AT/Badge.h>
#include <AT/Error.h>
#include <AT/Optional.h>
#include <MoonGUI/Forward.h>
#include <MoonGUI/Native/Event.h>

namespace GUI::Native {

using PFN_EventLoopCallback = void (*)(void* window_native_handle, const Event& event);

// The API defined by this class is implemented in two files, depending on whether or not it is platform specific.
// The platform generic implementation can be found 'Native/EventLoop.cpp', while the Windows implementations,
// for example, are found in 'Native/Windows/WindowsEventLoop.cpp'.
class EventLoop {
    AT_MAKE_NONCOPYABLE(EventLoop);
    AT_MAKE_NONMOVABLE(EventLoop);

public:
    explicit EventLoop(Badge<Application>) {}
    ~EventLoop() = default;

    ALWAYS_INLINE void set_event_callback(PFN_EventLoopCallback event_callback) { m_event_callback = event_callback; }
    NODISCARD ALWAYS_INLINE PFN_EventLoopCallback get_event_callback() const { return m_event_callback; }

    // Enters the platform-specific window message dispatching loop that blocks the calling thread until
    // a new message is posted. The set event callback will be invoked when an event occurs, otherwise
    // the thread will be sleeping.
    ErrorOr<void> enter_locking_event_loop();

    void exit_locking_event_loop();

private:
    PFN_EventLoopCallback m_event_callback { nullptr };

    // The optional has a value only when the event loop is currently in a locking event loop.
    Optional<bool> m_should_exit_locking_event_loop;
};

} // namespace GUI::Native
