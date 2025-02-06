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

    void cpu::tick()
    {
        current_operation.get().tick();

        if (current_operation.get().is_done())
        {
            r_ir = read_pc();
        }

        if (r_ir == 0000)
        {
            nop.activate();
        }
        else if (r_ir & 0x11 == 0b0100'0000)  // 01xx
        {

            ld_r8_r8.activate(&r_bc.high, &r_bc.low);
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

