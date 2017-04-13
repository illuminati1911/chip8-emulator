#include <iostream>
#include <cpu.h>

int main(int argc, char** argv) {
    cpu chip8_cpu;

    // setup OpenGL here
    // and input

    chip8_cpu.init();
    chip8_cpu.load("PONG");

    /*for(;;)
    {
        chip8_cpu.cycle();

        if (chip8_cpu.m_drawFlag)
        {
            //renderFrame();
        }

        chip8_cpu.setKeys();
    }*/


    return 0;
}