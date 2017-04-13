//
// Created by Ville Välimaa on 08/04/2017.
//

#ifndef CHIP8_EMULATOR_CPU_H
#define CHIP8_EMULATOR_CPU_H
#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_CPU_REGISTER_COUNT 16
#define CHIP8_GFX_RESOLUTION 64 * 32
#define CHIP8_STACK_LEVELS 16
#define CHIP8_FONTSET_SIZE 80
#define CHIP8_PROGRAM_MEMORY_START 512


class cpu {
    private:
        /*
         * MEMORY MAP:
         * 0x000 -> 0x1FF: FONT DATA
         * 0x200 -> 0xFFF: PROGRAM RAM AND SYSTEM ROM
         * */
        unsigned short m_opcode;
        unsigned char m_memory[CHIP8_MEMORY_SIZE];
        unsigned char m_V[CHIP8_CPU_REGISTER_COUNT];
        unsigned short m_i;
        unsigned short m_pc;

        // FONT SET
        unsigned char m_fontset[CHIP8_FONTSET_SIZE];

        // RENDERING BUFFER
        unsigned char m_gfx_buffer[CHIP8_GFX_RESOLUTION];

        // TIMERS
        unsigned char m_delay_timer;
        unsigned char m_audio_timer;

        // STACK
        unsigned short m_stack[CHIP8_STACK_LEVELS];
        unsigned short m_stack_pointer;

        // KEYBOARD 0x0 -> 0xF
        unsigned char m_keyboard[16];
    public:
        bool m_drawFlag;

        void init();
        bool load(const char *filename);
        void cycle();
        void setKeys();
};


#endif //CHIP8_EMULATOR_CPU_H
