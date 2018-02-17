#include <iostream>
#include <chip8_system.h>
#include <thread>
#include "SDL.h"
#include "renderer.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char** argv) {
    chip8_system chip8;
    chip8.init();
    chip8.load("roms/PONG");

    std::unique_ptr<gpu_renderer> gRenderer = std::make_unique<gpu_renderer>();
    gRenderer->init();

    for(;;)
    {
        chip8.cpuCycle();

        if (chip8.m_drawFlag)
        {
            chip8.m_drawFlag = false;
            gRenderer->updateFramebuffer(chip8.m_gfx_buffer);
        }

        chip8.setKeys();
        SDL_Delay(SCREEN_TICKS_PER_FRAME);
    }

    return 0;
}