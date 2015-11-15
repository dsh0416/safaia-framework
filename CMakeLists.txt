cmake_minimum_required(VERSION 3.2)
project(safaia_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp)

set(SAFAIA_HEADER_FILES framework/safaia/Safaia.h framework/safaia/Log.h framework/safaia/Request.h framework/safaia/Route.h framework/safaia/Ecp.h framework/safaia/Response.h)

add_executable(safaia_framework ${SOURCE_FILES} ${SAFAIA_HEADER_FILES})

file(COPY views DESTINATION ./)