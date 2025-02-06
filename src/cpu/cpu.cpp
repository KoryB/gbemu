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

    std::uint8_t &cpu::get_r8(const std::uint8_t r8_id)
    {
        switch (r8_id)
        {
            case 0x00:
                return r_bc.high;
            case 0x01:
                return r_bc.low;
            case 0x02:
                return r_de.high;
            case 0x03:
                return r_de.low;
            case 0x04:
                return r_hl.high;
            case 0x05:
                return r_hl.low;
            case 0x07:
            default:
                // TODO KB: What to do? Return A for now I guess
                return r_af.high;
        }
    }

    reg &cpu::get_r16(const std::uint8_t r16_id)
    {
        switch (r16_id)
        {
            case 0x000:
            case 0x001:
            default:
                return r_bc;
            case 0x010:
            case 0x011:
                return r_de;

        }
    }

}

