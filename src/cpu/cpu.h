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
    // TODO KB: This doesn't work because of endianness?
    struct reg
    {
        std::uint8_t high;
        std::uint8_t low;

        // ReSharper disable once CppNonExplicitConvertingConstructor
        reg(const std::uint16_t full) // NOLINT(*-explicit-constructor)
            : high((full & 0xFF00) >> 8)
            , low(full & 0x00FF) { }
        reg(const std::uint8_t high, const std::uint8_t low) : high(high), low(low) {}

        [[nodiscard]] std::uint16_t full() const { return (high << 8) | low; }
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
        std::uint8_t &get_r8(std::uint8_t r8_id);
        reg &get_r16(std::uint8_t r16_id);

        std::uint8_t read_pc();

        // These are all separate because they have different cycle properties
        void ld_r8_r8(std::uint8_t r8_id_1, std::uint8_t r8_id_2);      // LD r8,r8
        void ld_r8_n8(std::uint8_t r8_id);                              // LD r8,n8
        void ld_r16_n16(std::uint8_t r16_id);                           // LD r16,n16
        void ld_ihl_r8(std::uint8_t r8_id);                             // LD [HL],r8
        void ld_ihl_n8();                                               // LD [HL],n8
        void ld_r8_ihl(std::uint8_t r8_id);                             // LD r8,[HL]
        void ld_ir16_a(std::uint8_t r16_id);                            // LD [r16],A
        void ld_in16_a();                                               // LD [n16],A
        void ldh_in16_a();                                              // LDH [n16],A
        void ldh_ic_a();                                                // LDH [C],A
        void ld_a_ir16(std::uint8_t reg16_id);                          // LD A,[r16]
        void ld_a_in16();                                               // LD A,[n16]
        void ldh_a_in16();                                              // LDH A,[n16]
        void ldh_a_ic();                                                // LDH A,[C]
        void ldi_ihl_a();                                               // LD [HLI],A
        void ldd_ihl_a();                                               // LD [HLD],A
        void ldi_a_ihl();                                               // LD A,[HLI]
        void ldd_a_ihl();                                               // LD A,[HLD]



        std::shared_ptr<mem::memory_map> memory_map;
    };
}

#endif //CPU_H
