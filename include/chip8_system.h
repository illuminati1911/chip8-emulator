//
// Created by Ville Välimaa on 08/04/2017.
//
//
//
// ██████╗██╗  ██╗██╗██████╗      █████╗     ███████╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗
//██╔════╝██║  ██║██║██╔══██╗    ██╔══██╗    ██╔════╝████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗
//██║     ███████║██║██████╔╝    ╚█████╔╝    █████╗  ██╔████╔██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝
//██║     ██╔══██║██║██╔═══╝     ██╔══██╗    ██╔══╝  ██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗
//╚██████╗██║  ██║██║██║         ╚█████╔╝    ███████╗██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║
// ╚═════╝╚═╝  ╚═╝╚═╝╚═╝          ╚════╝     ╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
//
//

#ifndef CHIP8_EMULATOR_CHIP8_SYSTEM_H
#define CHIP8_EMULATOR_CHIP8_SYSTEM_H
#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_CPU_REGISTER_COUNT 16
#define CHIP8_GFX_RESOLUTION 64 * 32
#define CHIP8_STACK_LEVELS 16
#define CHIP8_FONTSET_SIZE 80
#define CHIP8_PROGRAM_MEMORY_START 512

class chip8_system {
    private:
        /*
         * MEMORY MAP:
         * 0x000 -> 0x1FF: FONT DATA
         * 0x200 -> 0xFFF: PROGRAM RAM AND SYSTEM ROM
         * */
        unsigned short m_opcode;
        unsigned char m_memory[CHIP8_MEMORY_SIZE];
        unsigned char m_V[CHIP8_CPU_REGISTER_COUNT];
        unsigned short m_I;
        unsigned short m_pc;

        // FONT SET
        unsigned char m_fontset[CHIP8_FONTSET_SIZE];

        // TIMERS
        unsigned char m_delay_timer;
        unsigned char m_audio_timer;

        // STACK
        unsigned short m_stack[CHIP8_STACK_LEVELS];
        unsigned short m_stack_pointer;

        // CPU INSTRUCTIONS & JUMP TABLES
        typedef void (chip8_system::*cpu_instr)();
        cpu_instr m_CPU_JUMP_TABLE[0x10];
        cpu_instr m_CPU_SUBINSTR_0x0XXX_TABLE[0x10];
        cpu_instr m_CPU_SUBINSTR_0x8XXX_TABLE[0x10];
        cpu_instr m_CPU_SUBINSTR_0xEXXX_TABLE[0xA2];
        cpu_instr m_CPU_SUBINSTR_0xFXXX_TABLE[0x66];

        void cpu_0x0XXX();
        void cpu_0x1XXX();
        void cpu_0x2XXX();
        void cpu_0x3XXX();
        void cpu_0x4XXX();
        void cpu_0x5XXX();
        void cpu_0x6XXX();
        void cpu_0x7XXX();
        void cpu_0x8XXX();
        void cpu_0x9XXX();
        void cpu_0xAXXX();
        void cpu_0xBXXX();
        void cpu_0xCXXX();
        void cpu_0xDXXX();
        void cpu_0xEXXX();
        void cpu_0xFXXX();

        void cpu_sub_0x0000();
        void cpu_sub_0x000E();
        void cpu_sub_0x8XY0();
        void cpu_sub_0x8XY1();
        void cpu_sub_0x8XY2();
        void cpu_sub_0x8XY3();
        void cpu_sub_0x8XY4();
        void cpu_sub_0x8XY5();
        void cpu_sub_0x8XY6();
        void cpu_sub_0x8XY7();
        void cpu_sub_0x8XYE();
        void cpu_sub_0xEX9E();
        void cpu_sub_0xEXA1();
        void cpu_sub_0xFX07();
        void cpu_sub_0xFX0A();
        void cpu_sub_0xFX15();
        void cpu_sub_0xFX18();
        void cpu_sub_0xFX1E();
        void cpu_sub_0xFX29();
        void cpu_sub_0xFX33();
        void cpu_sub_0xFX55();
        void cpu_sub_0xFX65();

    public:
        // RENDERING BUFFER
        bool m_drawFlag;
        unsigned char m_gfx_buffer[CHIP8_GFX_RESOLUTION];

        // KEYBOARD 0x0 -> 0xF
        unsigned char m_keyboard[16];

        void init();
        bool load(const char *filename);
        void cpuCycle();
        void setKeys();
};


#endif //CHIP8_EMULATOR_CHIP8_SYSTEM_H
