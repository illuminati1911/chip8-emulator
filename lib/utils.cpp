//
// Created by Ville Välimaa on 10/04/2017.
//

#include <iostream>
#include "utils.h"

namespace utils
{
    void PRINT_CHIP8_LOG(std::string msg)
    {
        std::cout << msg << std::endl;
    }

    bool VERIFY_CHIP8_ROM_FIT(std::streampos *rom_size, int memory_size)
    {
        if (memory_size - 512 < *rom_size)
        {
            printf("ERROR! PROGRAM ROM IS TOO LARGE FOR CHIP-8 MEMORY.\n");
            return false;
        }
        return true;
    }
}
