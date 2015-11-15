#!/usr/bin/env sh

mkdir build || true
mkdir build/safaia_framework || true
cd build/safaia_framework
cmake ../../
make

# Add the following line after importing googletest
# make test