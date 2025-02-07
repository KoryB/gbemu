//
// Created by Kory Byrne on 2/2/25.
//

#include "operation.h"
#include "cpu.h"


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

}