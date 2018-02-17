cmake_minimum_required(VERSION 3.7)
project(chip8_emulator)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 14)

enable_testing()

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(./include)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)