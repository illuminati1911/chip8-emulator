#include <iostream>
#include <chip8_system.h>

int main(int argc, char** argv) {
    chip8_system chip8;

    // setup OpenGL here
    // and input

    chip8.init();
    chip8.load("PONG");

    /*for(;;)
    {
        chip8_cpu.cycle();

        if (chip8_cpu.m_drawFlag)
        {
            //renderFrame();
        }

        chip8_cpu.setKeys();

        // TEMP SOLUTION! REPLACE LATER WITH OPENGL RENDERER
        std::this_thread::sleep_for (std::chrono::milliseconds(16));
    }*/


    return 0;
}