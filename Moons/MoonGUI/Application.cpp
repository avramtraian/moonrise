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

    // Release the application instance memory.
    delete s_application_instance;
    s_application_instance = nullptr;
}

Application& Application::get()
{
    AT_ASSERT(s_application_instance);
    return *s_application_instance;
}

} // namespace GUI
