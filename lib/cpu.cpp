//
// Created by Ville Välimaa on 08/04/2017.
//

#include <cstring>
#include <iostream>
#include <fstream>
#include "cpu.h"
#include "utils.h"

void cpu::init()
{
    // FONTSET
    const unsigned char chip8_fontset[CHIP8_FONTSET_SIZE] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0,		// 0
            0x20, 0x60, 0x20, 0x20, 0x70,		// 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0,		// 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0,		// 3
            0x90, 0x90, 0xF0, 0x10, 0x10,		// 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0,		// 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0,		// 6
            0xF0, 0x10, 0x20, 0x40, 0x40,		// 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0,		// 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0,		// 9
            0xF0, 0x90, 0xF0, 0x90, 0x90,		// A
            0xE0, 0x90, 0xE0, 0x90, 0xE0,		// B
            0xF0, 0x80, 0x80, 0x80, 0xF0,		// C
            0xE0, 0x90, 0x90, 0x90, 0xE0,		// D
            0xF0, 0x80, 0xF0, 0x80, 0xF0,		// E
            0xF0, 0x80, 0xF0, 0x80, 0x80		// F
    };

    // INIT REGISTERS & FLAGS
    m_pc = 0x200;
    m_opcode = 0x0;
    m_i = 0x0;
    memset(m_V, 0x0, CHIP8_CPU_REGISTER_COUNT);

    // CLEAR DISPLAY
    memset(m_gfx_buffer, 0x0, CHIP8_GFX_RESOLUTION);
    m_drawFlag = true;

    // CLEAR STACK
    memset(m_stack, 0x0, CHIP8_STACK_LEVELS);
    m_stack_pointer = 0x0;

    // RESET TIMERS
    m_audio_timer = 0x0;
    m_delay_timer = 0x0;

    // LOAD FONTSET TO MEMORY (MEMORY MAP AREA: 0x000 -> 0x1FF)
    for (int i = 0; i < CHIP8_FONTSET_SIZE; i++)
        m_memory[i] = chip8_fontset[i];
}

bool cpu::load(const char *filename)
{
    std::ifstream file(filename, std::ios::in
                               | std::ios::binary
                               | std::ios::ate);
    if (file.is_open())
    {
        // READ ROM TO BUFFER
        std::streampos size = file.tellg();
        unsigned char *program_buffer = new unsigned char[size];
        file.seekg(0, std::ios::beg);
        file.read((char *)program_buffer, size);
        file.close();
        printf("SIZE OF THE ROM IS %llu\n", (unsigned long long)size);

        // VERIFY THAT ROM FITS TO CHIP-8 MEMORY
        if (!utils::VERIFY_CHIP8_ROM_FIT(&size, CHIP8_MEMORY_SIZE))
        {
            delete[] program_buffer;
            return false;
        }

        // WRITE BUFFER TO EMULATOR MEMORY
        for (int i = 0; i < size; i ++)
            m_memory[CHIP8_PROGRAM_MEMORY_START + i] = program_buffer[i];

        delete[] program_buffer;
    } else {
        utils::PRINT_CHIP8_LOG("COULD NOT OPEN FILE!");
        return false;
    }
    utils::PRINT_CHIP8_LOG("PROGRAM SUCCESFULLY LOADED!");
    return true;
}

void cpu::cycle()
{

}

void cpu::setKeys()
{

}