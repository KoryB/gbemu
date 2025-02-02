//
// Created by Kory Byrne on 2/2/25.
//

#ifndef CPU_H
#define CPU_H

#include <cstdint>

namespace gb::cpu
{
    class Cpu
    {
    public:
        constexpr auto ClockFrequency = 4'194'304;  // 4 MiHz

    private:
        // TODO KB: ??? Tick ???
        void fetch();
        void execute();

        // Registers
        std::uint8_t r_ir = 0;
        std::uint8_t r_ie = 0;
        std::uint8_t r_a = 0;
        std::uint8_t r_f = 0;
        std::uint8_t r_b = 0;
        std::uint8_t r_c = 0;
        std::uint8_t r_d = 0;
        std::uint8_t r_e = 0;
        std::uint8_t r_h = 0;
        std::uint8_t r_l = 0;
        std::uint16_t r_pc = 0;
        std::uint16_t r_sp = 0;
    };
}

#endif //CPU_H
