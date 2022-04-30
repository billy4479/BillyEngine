#!/bin/sh

# This script is made for pure convenience to speed up the process on my system
#
# It depends on `mingw-w64-toolchain` and `mingw-w64-cmake` (Archlinux packages)

set -e

# Build the generator
cmake -S . -B build -G Ninja
cmake --build build -t Generator

# Crosscompile the rest
cmake -S . -B build-cross -G Ninja \
    -D CMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-x86_64-w64-mingw32.cmake \
    -D Gen_DIR=build \
    -D BUNDLE_DEPENDENCIES=OFF \
    $@
cmake --build build-cross

# Pack the libraries
pushd build-cross
mkdir -p dist
cp -v Demo/Demo.exe _deps/**/*.dll _deps/**/**/*.dll *.dll /usr/x86_64-w64-mingw32/bin/*.dll dist
zip -r dist.zip dist
popd

