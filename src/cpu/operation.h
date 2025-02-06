//
// Created by Kory Byrne on 2/2/25.
//

// ReSharper disable CppPossiblyUninitializedMember
#ifndef OP_CODE_H
#define OP_CODE_H
#include <functional>
#include <vector>

namespace gb::cpu
{

struct reg;
class cpu;

class operation
{
public:
    explicit operation(cpu &cpu_handle, const int num_steps)
    : cpu_handle(cpu_handle)
    , num_steps(num_steps)
    , current_step() { }

    virtual ~operation() = 0;

    void tick()
    {
        if (is_done()) return;

        switch (current_step++)
        {
            case 0:
                return m2();
            case 1:
                return m3();
            case 2:
                return m4();
            case 3:
                return m5();
            default:
                // pass
        }
    };

    bool is_done() const { return current_step >= num_steps; }

protected:
    // Not sure how many of these I need
    virtual void m2() { }
    virtual void m3() { }
    virtual void m4() { }
    virtual void m5() { }

    void set_active_in_cpu();

    cpu& cpu_handle;

    const int num_steps;
    int current_step;

};

class nop final : public operation
{
public:
    explicit nop(cpu &cpu_handle) : operation(cpu_handle, 1) { }

    void activate() { set_active_in_cpu(); }
};

class ld_r8_r8 final : public operation
{
public:
    explicit ld_r8_r8(cpu &cpu_handle) : operation(cpu_handle, 1) { }
    ~ld_r8_r8() override = default;

    void activate(std::uint8_t *dest, std::uint8_t *src)
    {
        set_active_in_cpu();

        this->dest = dest;
        this->src = src;
    };

protected:
    void m2() override;

private:
    std::uint8_t *dest;
    std::uint8_t *src;
};
}

#endif //OP_CODE_H
