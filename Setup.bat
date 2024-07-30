::
:: Copyright (c) 2024 Traian Avram. All rights reserved.
:: SPDX-License-Identifier: BSD-3-Clause.
::

@echo off

:: Variable that configure that project file generation.
set compiler=cl
set generator=Ninja

:: Push the directory where the batch file is located, as it also represents
:: the root of the project. This is done in order to ensure the same behaviour,
:: no matter from where the script file is invoked.
pushd "%~dp0"

:: Create the 'Build' directory, if it doesn't exist.
if not exist "Build/" ( mkdir "Build" )

pushd "Build"

:: Create the configuration-specific directories, if they don't exist.
if not exist "Debug/" ( mkdir "Debug" )
if not exist "Release/" ( mkdir "Release" )

cmake -S ../ -B "Debug"   -DCMAKE_CXX_COMPILER=%compiler% -G %generator% -DCMAKE_BUILD_TYPE=Debug
cmake -S ../ -B "Release" -DCMAKE_CXX_COMPILER=%compiler% -G %generator% -DCMAKE_BUILD_TYPE=Release

popd

:: Pop the directory where the batch file is located.
popd
