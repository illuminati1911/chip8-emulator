//
// Created by Ville Välimaa on 08/04/2017.
//

#include <cstring>
#include <iostream>
#include <fstream>
#include "chip8_system.h"
#include "utils.h"

void chip8_system::init()
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

    // INIT CPU JUMP TABLES
    m_CPU_JUMP_TABLE[0x0] = &chip8_system::cpu_0x0XXX;
    m_CPU_JUMP_TABLE[0x1] = &chip8_system::cpu_0x1XXX;
    m_CPU_JUMP_TABLE[0x2] = &chip8_system::cpu_0x2XXX;
    m_CPU_JUMP_TABLE[0x3] = &chip8_system::cpu_0x3XXX;
    m_CPU_JUMP_TABLE[0x4] = &chip8_system::cpu_0x4XXX;
    m_CPU_JUMP_TABLE[0x5] = &chip8_system::cpu_0x5XXX;
    m_CPU_JUMP_TABLE[0x6] = &chip8_system::cpu_0x6XXX;
    m_CPU_JUMP_TABLE[0x7] = &chip8_system::cpu_0x7XXX;
    m_CPU_JUMP_TABLE[0x8] = &chip8_system::cpu_0x8XXX;
    m_CPU_JUMP_TABLE[0x9] = &chip8_system::cpu_0x9XXX;
    m_CPU_JUMP_TABLE[0xA] = &chip8_system::cpu_0xAXXX;
    m_CPU_JUMP_TABLE[0xB] = &chip8_system::cpu_0xBXXX;
    m_CPU_JUMP_TABLE[0xC] = &chip8_system::cpu_0xCXXX;
    m_CPU_JUMP_TABLE[0xD] = &chip8_system::cpu_0xDXXX;
    m_CPU_JUMP_TABLE[0xE] = &chip8_system::cpu_0xEXXX;
    m_CPU_JUMP_TABLE[0xF] = &chip8_system::cpu_0xFXXX;

    m_CPU_SUBINSTR_0x0XXX_TABLE[0x0] = &chip8_system::cpu_sub_0x0000;
    m_CPU_SUBINSTR_0x0XXX_TABLE[0xE] = &chip8_system::cpu_sub_0x000E;

    m_CPU_SUBINSTR_0x8XXX_TABLE[0x0] = &chip8_system::cpu_sub_0x8XY0;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0x1] = &chip8_system::cpu_sub_0x8XY1;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0x2] = &chip8_system::cpu_sub_0x8XY2;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0x3] = &chip8_system::cpu_sub_0x8XY3;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0x4] = &chip8_system::cpu_sub_0x8XY4;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0x5] = &chip8_system::cpu_sub_0x8XY5;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0x6] = &chip8_system::cpu_sub_0x8XY6;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0x7] = &chip8_system::cpu_sub_0x8XY7;
    m_CPU_SUBINSTR_0x8XXX_TABLE[0xE] = &chip8_system::cpu_sub_0x8XYE;

    // INIT REGISTERS & FLAGS
    memset(m_V, 0x0, CHIP8_CPU_REGISTER_COUNT);
    m_pc = 0x200;
    m_opcode = 0x0;
    m_I = 0x0;

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

bool chip8_system::load(const char *filename)
{
    std::ifstream file(filename, std::ios::in
                               | std::ios::binary
                               | std::ios::ate);
    if (!file.is_open())
    {
        utils::PRINT_CHIP8_LOG("COULD NOT OPEN FILE!");
        return false;
    }

    // READ ROM TO BUFFER
    std::streampos size = file.tellg();
    //unsigned char *program_buffer = new unsigned char[size]; // TODO: CHECK IF NEEDED AT ALL
    file.seekg(0, std::ios::beg);
    file.read((char *)m_memory, size);
    file.close();
    printf("SIZE OF THE ROM IS %llu\n", (unsigned long long)size);

    // VERIFY THAT ROM FITS TO CHIP-8 MEMORY
    if (!utils::VERIFY_CHIP8_ROM_FIT(&size, CHIP8_MEMORY_SIZE))
    {
        //delete[] program_buffer;
        return false;
    }

    // TODO: CHECK IF NEEDED AT ALL
    // WRITE BUFFER TO EMULATOR MEMORY
    //for (int i = 0; i < size; i ++)
    //    m_memory[CHIP8_PROGRAM_MEMORY_START + i] = program_buffer[i];

    //delete[] program_buffer; // TODO: CHECK IF NEEDED AT ALL
    utils::PRINT_CHIP8_LOG("PROGRAM SUCCESSFULLY LOADED!");
    return true;
}

void chip8_system::cpuCycle()
{
    // FETCH OPCODE
    m_opcode = m_memory[m_pc] << 8 | m_memory[m_pc + 1];
    std::cout << std::hex << m_opcode << std::endl;
    // OPCODE => JUMP TABLE => EXECUTE
    (this->*m_CPU_JUMP_TABLE[(m_opcode & 0xF000) >> 12])();
}

void chip8_system::setKeys()
{

}

// CPU OPCODES

void chip8_system::cpu_0x0XXX() {
    utils::PRINT_CHIP8_LOG("0");
    (this->*m_CPU_SUBINSTR_0x0XXX_TABLE[m_opcode & 0x000F])();
}

// 0x1NNN: Jumps to address at NNN
void chip8_system::cpu_0x1XXX() {
    utils::PRINT_CHIP8_LOG("1");
    m_pc = m_opcode & 0x0FFF;
}

// 0x2NNN: Calls subroutine at NNN
void chip8_system::cpu_0x2XXX() {
    utils::PRINT_CHIP8_LOG("2");
    m_stack[m_stack_pointer] = m_pc;
    m_stack_pointer += 1;
    m_pc = m_opcode & 0x0FFF;
    m_pc += 2;
}

// 0x3XNN: Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
void chip8_system::cpu_0x3XXX() {
    utils::PRINT_CHIP8_LOG("3");
    m_V[(m_opcode & 0x0F00) >> 8] == (m_opcode & 0x00FF)
        ? m_pc += 4
        : m_pc += 2;
}

// 0x4XNN: Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
void chip8_system::cpu_0x4XXX() {
    utils::PRINT_CHIP8_LOG("4");
    m_V[(m_opcode & 0x0F00) >> 8] == (m_opcode & 0x00FF)
        ? m_pc += 2
        : m_pc += 4;
}

// 0x5XY0: Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)
void chip8_system::cpu_0x5XXX() {
    utils::PRINT_CHIP8_LOG("5");
    m_V[(m_opcode & 0x0F00) >> 8] == m_V[(m_opcode & 0x00F0) >> 4]
        ? m_pc += 4
        : m_pc += 2;
}

// 0x6XNN: Sets VX to NN
void chip8_system::cpu_0x6XXX() {
    utils::PRINT_CHIP8_LOG("6");
    m_V[(m_opcode & 0x0F00) >> 8] = m_opcode & 0x00FF;
    m_pc += 2;
}

// 0x7XNN: Adds NN to VX
void chip8_system::cpu_0x7XXX() {
    utils::PRINT_CHIP8_LOG("7");
    m_V[(m_opcode & 0x0F00) >> 8] += m_opcode & 0x00FF;
    m_pc += 2;
}

//
void chip8_system::cpu_0x8XXX() {
    utils::PRINT_CHIP8_LOG("8");
    (this->*m_CPU_SUBINSTR_0x8XXX_TABLE[m_opcode & 0x000F])();
    m_pc += 2;
}

void chip8_system::cpu_0x9XXX() {
    utils::PRINT_CHIP8_LOG("9");
}

void chip8_system::cpu_0xAXXX() {
    utils::PRINT_CHIP8_LOG("A");
}

void chip8_system::cpu_0xBXXX() {
    utils::PRINT_CHIP8_LOG("B");
}

void chip8_system::cpu_0xCXXX() {
    utils::PRINT_CHIP8_LOG("C");
}

void chip8_system::cpu_0xDXXX() {
    utils::PRINT_CHIP8_LOG("D");
}

void chip8_system::cpu_0xEXXX() {
    utils::PRINT_CHIP8_LOG("E");
}

void chip8_system::cpu_0xFXXX() {
    utils::PRINT_CHIP8_LOG("F");
}


// CPU OPCODES SUB INSTRUCTIONS

// 0x00E0: Clear the screen
void chip8_system::cpu_sub_0x0000() {
    memset(m_gfx_buffer, 0x0, CHIP8_GFX_RESOLUTION);
    m_drawFlag = true;
    m_pc += 2;
}

// 0x00EE: Return from subroutine
void chip8_system::cpu_sub_0x000E() {
    m_stack_pointer -= 1;
    m_pc = m_stack[m_stack_pointer];
    m_pc += 2;
}

void chip8_system::cpu_sub_0x8XY0() {
    m_V[(m_opcode & 0x0F00 >> 8)] = (m_opcode & 0x00F0) >> 4;
}

void chip8_system::cpu_sub_0x8XY1() {
    m_V[(m_opcode & 0x0F00 >> 8)] = ((m_opcode & 0x0F00) >> 8) | ((m_opcode & 0x00F0) >> 4);
}

void chip8_system::cpu_sub_0x8XY2() {
    m_V[(m_opcode & 0x0F00 >> 8)] = ((m_opcode & 0x0F00) >> 8) & ((m_opcode & 0x00F0) >> 4);
}

void chip8_system::cpu_sub_0x8XY3() {

}

void chip8_system::cpu_sub_0x8XY4() {

}

void chip8_system::cpu_sub_0x8XY5() {

}

void chip8_system::cpu_sub_0x8XY6() {

}

void chip8_system::cpu_sub_0x8XY7() {

}

void chip8_system::cpu_sub_0x8XYE() {

}