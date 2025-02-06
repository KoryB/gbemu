//
// Created by Kory Byrne on 2/2/25.
//

#ifndef OP_CODE_H
#define OP_CODE_H
#include <functional>
#include <vector>

namespace gb::cpu
{

class reg;
class cpu;
class operation
{
public:
    explicit operation(cpu &cpu_, int num_steps)
    : cpu(cpu_)
    , num_steps(num_steps)
    , current_step() { }

    virtual ~operation() = 0;

    void tick()
    {
        if (current_step >= num_steps) return;

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

protected:
    // Not sure how many of these I need
    virtual void m2() { }
    virtual void m3() { }
    virtual void m4() { }
    virtual void m5() { }

    void do_activate();

    cpu& cpu;

    int num_steps;
    int current_step;

};

class ld_r8_r8 final : public operation
{
public:
    ld_r8_r8() = delete;
    ~ld_r8_r8() override = default;

protected:
    void m2() override { };

    void activate(reg* dest, reg* src)
    {
        this->dest = dest;
        this->src = src;
    };

private:
    reg* dest;
    reg* src;
};
}

#endif //OP_CODE_H
