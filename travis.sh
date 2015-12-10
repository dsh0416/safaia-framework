#!/usr/bin/env sh
mkdir build || true
mkdir build/safaia_framework || true
cd build/safaia_framework
cmake ../../
make

# Unit Test Coverage
if [ "${TRAVIS_OS_NAME}" = "linux" ] && [ "$UNIT_TEST" = "true" ]; then
    ./safaia_framework
    gcov-4.9 ../../tests/main.cpp --object-directory ./CMakeFiles/safaia_framework.dir/tests
elif [ "$UNIT_TEST" = "true" ]; then
    ls
    ./safaia_framework
    gcov ../../tests/main.cpp --object-directory ./CMakeFiles/safaia_framework.dir/tests
fi
