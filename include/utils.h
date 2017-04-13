//
// Created by Ville Välimaa on 10/04/2017.
//

#ifndef CHIP8_EMULATOR_UTILS_H
#define CHIP8_EMULATOR_UTILS_H


namespace utils
{
    void PRINT_CHIP8_LOG(std::string msg);
    bool VERIFY_CHIP8_ROM_FIT(std::streampos *rom_size, int memory_size);
};


#endif //CHIP8_EMULATOR_UTILS_H
