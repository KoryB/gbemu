cmake_minimum_required(VERSION 3.30)
project(gb_emu)

set(CMAKE_CXX_STANDARD 20)

include_directories(INCLUDE_DIR)
add_executable(gb_emu src/main.cpp
        src/main.h
        src/cpu/cpu.cpp
        src/cpu/cpu.h)
