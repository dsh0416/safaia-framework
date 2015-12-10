#!/usr/bin/env sh
mkdir build || true
mkdir build/safaia_framework || true
cd build/safaia_framework
cmake ../../
make

# Unit Test Coverage
if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
    gcov-4.9 ../../main.cpp --object-directory ./CMakeFiles/safaia_framework.dir
else
    gcov ../../main.cpp --object-directory ./CMakeFiles/safaia_framework.dir
fi
