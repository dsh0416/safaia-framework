#!/usr/bin/env sh
mkdir build || true
mkdir build/safaia_framework || true
cd build/safaia_framework
cmake ../../
make

# Unit Test Coverage
gcov ../../main.cpp --object-directory ./CMakeFiles/safaia_framework.dir