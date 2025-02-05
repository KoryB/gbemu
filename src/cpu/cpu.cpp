//
// Created by Kory Byrne on 2/2/25.
//

#include "cpu.h"
#include "../memory/memory.h"

namespace gb::cpu
{
    std::uint8_t cpu::read_pc()
    {
        return memory_map->read_addr(r_pc++);
    }

    void cpu::execute()
    {
        const auto opcode = read_pc();

        if (opcode == 0074)
        {
            const auto a_low_nibble = r_af.high & 0x0F;
            r_af.high += 1;

            z(r_af.high == 0);
            n(false);
            h(r_af.high & 0x0F == 0 && a_low_nibble != 0);
        }
    }
}

