add_executable(test_chip8_emulator test_cpu.cpp)
target_link_libraries(test_chip8_emulator libcpu ${CONAN_LIBS})
