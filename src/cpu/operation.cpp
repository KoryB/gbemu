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
    }

    void ld_r8_r8::m2()
    {
        *dest = *src;
    }

}