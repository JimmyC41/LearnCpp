#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE=${1:-Debug}

export CC=clang
export CXX=clang++

unset CMAKE_TOOLCHAIN_FILE

SDKROOT=$(xcrun --sdk macosx --show-sdk-path) # Query the active macOS SDK path

rm -rf build
mkdir build && cd build

cmake -G "Unix Makefiles" \
      -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
      -DCMAKE_C_COMPILER="$CC" \
      -DCMAKE_CXX_COMPILER="$CXX" \
      -DCMAKE_OSX_SYSROOT="${SDKROOT}" \
      -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
      ..

cmake --build . -- -j"$(getconf _NPROCESSORS_ONLN)"
