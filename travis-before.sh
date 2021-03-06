#!/usr/bin/env bash
if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
    wget --no-check-certificate http://cmake.org/files/v3.4/cmake-3.4.0-Linux-x86_64.sh -O /tmp/cmake_install.sh
    mkdir -p /tmp/cmake
    sh /tmp/cmake_install.sh --exclude-subdir --prefix=/tmp/cmake
    cmake --version
    pip install --user cpp-coveralls
else
    brew update
    brew unlink cmake
    brew install cmake
    brew install pyenv
    pyenv install 2.7.6
    pyenv rehash
    pip install cpp-coveralls
    pyenv rehash
fi