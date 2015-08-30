cmake_minimum_required(VERSION 3.2)
project(safaia_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(safaia_framework ${SOURCE_FILES} framework/Safaia.cpp framework/Safaia.h)