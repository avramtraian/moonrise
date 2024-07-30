/*
 * Copyright (c) 2024 Traian Avram. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause.
 */

#pragma once

#include <AT/Error.h>
#include <MoonGUI/GUI.h>

namespace GUI {

class Application {
    AT_MAKE_NONCOPYABLE(Application);
    AT_MAKE_NONMOVABLE(Application);

public:
    GUI_API static ErrorOr<void> construct();
    GUI_API static void destruct();

    NODISCARD GUI_API static Application& get();

private:
    Application() = default;
    ~Application() = default;
};

} // namespace GUI
