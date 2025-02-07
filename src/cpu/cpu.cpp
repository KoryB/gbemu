//
// Created by Kory Byrne on 2/2/25.
//

#include "cpu.h"

#include "../constants.h"
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

        // See: https://gbdev.io/gb-opcodes/optables/octal
        switch (r_ir)
        {
            case 0000:
                return nop.activate();

            // ld from immediate value, recall reg 6 indicates indirect [HL] mode
            case 0006: case 0016: case 0026: case 0036: case 0046: case 0056: case 0076:
                return ld_r8_n8.activate(&get_r8(middle_octal(r_ir)));

            // ld instructions, but recall that reg 6 indicates indirect [HL] mode
            case 0100: case 0101: case 0102: case 0103: case 0104: case 0105: case 0107:
            case 0110: case 0111: case 0112: case 0113: case 0114: case 0115: case 0117:
            case 0120: case 0121: case 0122: case 0123: case 0124: case 0125: case 0127:
            case 0130: case 0131: case 0132: case 0133: case 0134: case 0135: case 0137:
            case 0140: case 0141: case 0142: case 0143: case 0144: case 0145: case 0147:
            case 0150: case 0151: case 0152: case 0153: case 0154: case 0155: case 0157:
            case 0170: case 0171: case 0172: case 0173: case 0174: case 0175: case 0177:
                return ld_r8_r8.activate(
                    &get_r8(middle_octal(r_ir)),
                    &get_r8(low_octal(r_ir));

            // Eventually this won't be necessary as the whole table will be full
            default:
                return nop.activate();
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

