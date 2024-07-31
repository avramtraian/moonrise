/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#pragma once

#include <AT/Types.h>

namespace GUI::Native {

enum class EventType : u8 {
    None = 0,
    ApplicationClosed,

    WindowClosed,
    WindowResized,
    WindowMoved,

    MouseMoved,
    MouseWheelScrolled,
    MouseButtonPressed,
    MouseButtonReleased,

    KeyPressed,
    KeyReleased,
};

class Event {
    AT_MAKE_NONCOPYABLE(Event);
    AT_MAKE_NONMOVABLE(Event);

public:
    NODISCARD ALWAYS_INLINE EventType get_type() const { return m_type; }

protected:
    ALWAYS_INLINE explicit Event(EventType type)
        : m_type(type)
    {}

private:
    EventType m_type;
};

class ApplicationClosedEvent : public Event {
public:
    ALWAYS_INLINE ApplicationClosedEvent()
        : Event(EventType::ApplicationClosed)
    {}
};

class WindowResizedEvent : public Event {
public:
    ALWAYS_INLINE WindowResizedEvent(u32 client_area_width, u32 client_area_height)
        : Event(EventType::WindowResized)
        , m_client_area_width(client_area_width)
        , m_client_area_height(client_area_height)
    {}

    NODISCARD ALWAYS_INLINE u32 get_client_area_width() const { return m_client_area_width; }
    NODISCARD ALWAYS_INLINE u32 get_client_area_height() const { return m_client_area_height; }

private:
    u32 m_client_area_width;
    u32 m_client_area_height;
};

} // namespace GUI::Native
