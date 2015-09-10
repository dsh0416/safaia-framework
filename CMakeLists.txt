cmake_minimum_required(VERSION 3.2)
project(safaia_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_executable(safaia_framework ${SOURCE_FILES} framework/Safaia.h framework/Log.h framework/Request.h framework/Route.h framework/Ecp.h framework/UnitTest.h)
file(COPY views DESTINATION ./)