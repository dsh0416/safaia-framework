#!/usr/bin/env sh
if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
    wget --no-check-certificate http://cmake.org/files/v3.4/cmake-3.4.0-Linux-x86_64.sh -O /tmp/cmake_install.sh
    mkdir -p /tmp/cmake
    sh /tmp/cmake_install.sh --exclude-subdir --prefix=/tmp/cmake
    export PATH="/tmp/cmake/bin:${PATH}"
    cmake --version
else
    brew update
    brew unlink cmake
    brew install cmake
fi
mkdir build || true
mkdir build/safaia_framework || true
cd build/safaia_framework
cmake ../../
make