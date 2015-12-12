#!/usr/bin/env sh
mkdir build || true
mkdir build/safaia_framework || true
cd build/safaia_framework
cmake ../../
make

# Unit Test Coverage
if [ "$UNIT_TEST" = "true" ]; then
    ./safaia_framework
fi
