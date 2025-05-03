#!/usr/bin/env bash
set -euo pipefail
BUILD_TYPE=${1:-Debug}
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
cmake --build . -- -j$(nproc)