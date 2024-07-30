#
# Copyright (c) 2024 Traian Avram. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause.
#

cmake_minimum_required(VERSION 3.14)
project(Moonrise CXX C)

#
# Set the project global C++ configuration settings.
#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disables compiler-specific extensions.
set(CXX_EXTENSIONS OFF)
set(COMPILE_WARNING_AS_ERROR ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /WX /EHsc")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
endif ()

# All binaries will be placed in the following directory.
set(MOONRISE_BUILD_DIRECTORY "${CMAKE_SOURCE_DIR}/Build/${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MOONRISE_BUILD_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MOONRISE_BUILD_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MOONRISE_BUILD_DIRECTORY})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${MOONRISE_BUILD_DIRECTORY})

# Make the CMake predefined targets appear nicer if using the Visual Studio toolchain.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_EXPORT_LIBRARY_PREFIX "")

add_subdirectory(AT)
add_subdirectory(Moons)
add_subdirectory(Applications)
