#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE=${1:-Debug}
SDKROOT=$(xcrun --sdk macosx --show-sdk-path) # Query the active macOS SDK path
mkdir -p build && cd build
cmake \
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
  -DCMAKE_OSX_SYSROOT="${SDKROOT}" \
  -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
  ..
cmake --build . -- -j"$(getconf _NPROCESSORS_ONLN)"
