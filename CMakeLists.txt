cmake_minimum_required(VERSION 3.2)
project(safaia_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -stdlib=libc++")

set(SOURCE_FILES main.cpp)

set(SAFAIA_HEADER_FILES framework/Safaia.h framework/Log.h framework/Request.h framework/Route.h framework/Ecp.h framework/Response.h)

add_executable(safaia_framework ${SOURCE_FILES} ${SAFAIA_HEADER_FILES})

file(COPY views DESTINATION ./)