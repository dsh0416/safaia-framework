cmake_minimum_required(VERSION 3.2)
project(safaia_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

if ($ENV{UNIT_TEST})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(SOURCE_FILES main-test.cpp)
    message(STATUS "Unit Test Mode ON")
else()
    set(SOURCE_FILES main.cpp)
    message(STATUS "Unit Test Mode OFF")
endif ($ENV{UNIT_TEST})

set(SAFAIA_HEADER_FILES framework/safaia/Safaia.h framework/safaia/Log.h framework/safaia/Request.h framework/safaia/Route.h framework/safaia/Ecp.h framework/safaia/Response.h framework/safaia/UnitTest.h)

add_executable(safaia_framework ${SOURCE_FILES} ${SAFAIA_HEADER_FILES})

file(COPY views DESTINATION ./)