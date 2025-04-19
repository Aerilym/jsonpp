#!/bin/bash

mkdir -p build && cd build
cmake -DCODE_COVERAGE=ON ..
cmake --build .
ctest --verbose
