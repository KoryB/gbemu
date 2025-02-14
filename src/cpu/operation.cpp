//
// Created by Kory Byrne on 2/2/25.
//

#include "operation.h"
#include "cpu.h"
#include "../memory/memory.h"


namespace gb::cpu
{

void operation::set_active_in_cpu()
{
    cpu_handle.set_operation(*this);
    current_step = 0;
}

bool operation::is_active() const
{
    return cpu_handle.is_active(*this);
}


void ld_r8_r8::m2()
{
    *dest = *src;
}


void ld_r8_n8::m2()
{
    cpu_handle.r_intermediate.low = cpu_handle.read_pc();
}

void ld_r8_n8::m3()
{
    *dest = cpu_handle.r_intermediate.low;
}


void ld_r8_ihl::m2()
{
    cpu_handle.r_intermediate.low = cpu_handle.memory_map->read_addr(cpu_handle.r_hl.full());
}


void ld_r8_ihl::m3()
{
    *dest = cpu_handle.r_intermediate.low;
}


void ld_ihl_r8::m2()
{
    cpu_handle.memory_map->write_addr(cpu_handle.r_hl.full(), *src);
}

// NOP for m3, but required for timing
void ld_ihl_r8::m3() { }


void ld_ihl_n8::m2()
{
    cpu_handle.r_intermediate.low = cpu_handle.read_pc();
}

void ld_ihl_n8::m3()
{
    cpu_handle.memory_map->write_addr(
        cpu_handle.r_hl.full(), cpu_handle.r_intermediate.low);
}

// NOP for m4, but required for timing
void ld_ihl_n8::m4() { }


}
