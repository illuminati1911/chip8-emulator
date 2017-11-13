file(GLOB_RECURSE SOURCES *.cpp)
add_executable(chip8_emulator ${SOURCES})
target_link_libraries(chip8_emulator chip8_libs ${SDL2_LIBRARY})