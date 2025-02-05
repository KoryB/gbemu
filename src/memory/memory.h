//
// Created by Kory Byrne on 2/2/25.
//

#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <cstdint>

namespace gb::mem
{

class memory_map
{
public:
    static constexpr std::size_t rom_bank_size = 1 << 14;
    static constexpr std::size_t vram_size = 1 << 13;
    static constexpr std::size_t external_ram_size = 1 << 13;
    static constexpr std::size_t work_ram_size = 1 << 12;
    static constexpr std::size_t echo_ram_size = 0xFDFF - 0xE000 + 1;
    static constexpr std::size_t oam_size = 0xFE9F - 0xFE00 + 1;
    static constexpr std::size_t io_registers_size = 0xFF7F - 0xFF00 + 1;

    [[nodiscard]] std::uint8_t read_addr(std::uint16_t addr) const;

private:
    // TODO KB: Should these be init to something else?

    std::array<std::uint8_t, rom_bank_size> rom_bank_00 = {};  // TODO: Might not even need these. Interface with cart?
    std::array<std::uint8_t, rom_bank_size> rom_bank_01 = {};  // TODO: Switchable via mapper?
    std::array<std::uint8_t, vram_size> vram = {};
    std::array<std::uint8_t, external_ram_size> external_ram = {};  // TODO: Interface with cart?
    std::array<std::uint8_t, work_ram_size> work_ram_01 = {};
    std::array<std::uint8_t, work_ram_size> work_ram_02 = {};
    std::array<std::uint8_t, echo_ram_size> echo_ram = {};
    std::array<std::uint8_t, oam_size> oam = {};
    std::array<std::uint8_t, io_registers_size> io_registers = {}; // TODO: This shouldn't be a buffer
    std::uint8_t interrupt_enable = 0;
};
}

#endif // MEMORY_H
