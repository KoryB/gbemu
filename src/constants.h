//
// Created by Kory Byrne on 2/4/25.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

namespace gb
{

constexpr std::uint8_t high_octal(const std::uint8_t x) { return x & 0b11'000'000 >> 6; }
constexpr std::uint8_t middle_octal(const std::uint8_t x) { return x & 0070 >> 3; }
constexpr std::uint8_t low_octal(const std::uint8_t x) { return x & 0007; }

}

namespace gb::vals
{
constexpr int cpu_clock_frequency = 4'194'304;  // 4 MiHz
}

#endif //CONSTANTS_H
