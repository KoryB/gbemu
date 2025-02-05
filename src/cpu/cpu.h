//
// Created by Kory Byrne on 2/2/25.
//

#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <memory>

namespace gb::mem
{
    class memory_map;
}

namespace gb::cpu
{
    union reg
    {
        std::uint16_t full;

        struct
        {
            std::uint8_t high;
            std::uint8_t low;
        };

        // ReSharper disable once CppNonExplicitConvertingConstructor
        reg(const std::uint16_t full) : full(full) {} // NOLINT(*-explicit-constructor)
        reg(const std::uint8_t high, const std::uint8_t low) : high(high), low(low) {}
    };

    class cpu
    {
    public:
        void set_memory(const std::shared_ptr<mem::memory_map> &memory_map)
        {
            this->memory_map = memory_map;
        }

        // TODO KB: ??? Tick ???
        void fetch();
        void execute();

        // Registers
        std::uint8_t r_ir = 0;
        std::uint8_t r_ie = 0;
        reg r_af = 0;
        reg r_bc = 0;
        reg r_de = 0;
        reg r_hl = 0;
        std::uint16_t r_pc = 0;
        std::uint16_t r_sp = 0;

        // Zero Flag, set and cleared by various instructions
        [[nodiscard]] bool z() const { return r_af.low & 0x80; }
        void z(const bool set) { r_af.low = (r_af.low & ~0x80) | (set << 7); }

        // TODO KB: Figure out what these really do... They seem weird
        [[nodiscard]] bool n() const { return r_af.low & 0x40; }
        void n(const bool set) { r_af.low = (r_af.low & ~0x40) | (set << 6); }

        [[nodiscard]] bool h() const { return r_af.low & 0x20; }
        void h(const bool set) { r_af.low = (r_af.low & ~0x20) | (set << 5); }

        // Carry Flag, for addition. Also used by conditional jumps
        [[nodiscard]] bool c() const { return r_af.low & 0x10; }
        void c(const bool set) { r_af.low = (r_af.low & ~0x10) | (set << 1); }

    private:
        std::uint8_t read_pc();
        std::shared_ptr<mem::memory_map> memory_map;
    };
}

#endif //CPU_H
