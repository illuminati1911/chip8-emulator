#include <iostream>
#include <chip8_system.h>
#include <thread>
#include "SDL.h"

int main(int argc, char** argv) {
    chip8_system chip8;

    // setup OpenGL here
    // and input

    chip8.init();
    chip8.load("roms/PONG");

    for(;;)
    {
        chip8.cpuCycle();

        if (chip8.m_drawFlag)
        {
            //renderFrame();
        }

        chip8.setKeys();

        // TEMP SOLUTION! REPLACE LATER WITH OPENGL RENDERER
        std::this_thread::sleep_for (std::chrono::milliseconds(16));
    }


    return 0;
}