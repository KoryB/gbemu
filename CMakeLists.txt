cmake_minimum_required(VERSION 3.30)
project(gb_emu)

set(CMAKE_CXX_STANDARD 20)

add_executable(gb_emu src/main.cpp
        src/cpu/cpu.cpp
        src/cpu/cpu.h
        src/cpu/alu.cpp
        src/cpu/alu.h
        src/cpu/idu.cpp
        src/cpu/idu.h
        src/cpu/control_unit.cpp
        src/cpu/control_unit.h
        src/cpu/op_code.cpp
        src/cpu/op_code.h
        src/memory/memory.cpp
        src/memory/memory.h
        src/constants.h)
