#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE=${1:-Debug}

export CC=clang
export CXX=clang++

mkdir -p build
cd build

cmake -G "Unix Makefiles" \
      -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
      -DCMAKE_C_COMPILER="$CC" \
      -DCMAKE_CXX_COMPILER="$CXX" \
      -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
      ..

cmake --build . -- -j"$(getconf _NPROCESSORS_ONLN)"
