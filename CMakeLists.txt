cmake_minimum_required(VERSION 3.7)
project(chip8_emulator)

set(CMAKE_CXX_STANDARD 14)

if(EXISTS ${CMAKE_SOURCE_DIR}/.conan/conanbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/.conan/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

enable_testing()

include_directories(./include)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

#set(SOURCE_FILES main.cpp)
#add_executable(chip8_emulator ${SOURCE_FILES})