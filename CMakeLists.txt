cmake_minimum_required(VERSION 3.22)
project(ascii-shade)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(ascii-shade ${SOURCES})
