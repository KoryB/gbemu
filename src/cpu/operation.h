//
// Created by Kory Byrne on 2/2/25.
//

// ReSharper disable CppPossiblyUninitializedMember
#ifndef OP_CODE_H
#define OP_CODE_H
#include <functional>

// TODO KB: Can this be done with an intermediate template class?
#define OPERATION_CLASS_HEADER(_class_name) \
class _class_name final : public operation

#define OPERATION_CLASS_BODY(_class_name, _num_steps) \
public: \
    constexpr int num_steps = _num_steps; \
    \
    explicit _class_name(cpu &cpu_handle) : operation(cpu_handle, num_steps) { } \
    ~_class_name() override = default;
// OPERATION_CLASS_BODY

#define OPERATION_CLASS_BODY_ONE_STEP(_class_name) \
OPERATION_CLASS_BODY(_class_name, 1) \
protected: \
    void m2() override;
// OPERATION_CLASS_BODY_ONE_STEP

#define OPERATION_CLASS_BODY_TWO_STEPS(_class_name) \
OPERATION_CLASS_BODY(_class_name, 2) \
protected: \
    void m2() override; \
    void m3() override;
// OPERATION_CLASS_BODY_TWO_STEPS

#define OPERATION_CLASS_BODY_THREE_STEPS(_class_name) \
OPERATION_CLASS_BODY(_class_name, 3) \
protected: \
    void m2() override; \
    void m3() override; \
    void m4() override;
// OPERATION_CLASS_BODY_THREE_STEPS

#define OPERATION_CLASS_BODY_FOUR_STEPS(_class_name) \
OPERATION_CLASS_BODY(_class_name, 4) \
protected: \
void m2() override; \
void m3() override; \
void m4() override; \
void m5() override;
// OPERATION_CLASS_BODY_FOUR_STEPS


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
        if (!is_active()) return;
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

    [[nodiscard]] bool operation::is_active() const;
    [[nodiscard]] bool is_done() const { return current_step >= num_steps; }

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

OPERATION_CLASS_HEADER(nop)
{
    OPERATION_CLASS_BODY_ONE_STEP(nop);

    void activate() { set_active_in_cpu(); }
};


OPERATION_CLASS_HEADER(ld_r8_r8)
{
    OPERATION_CLASS_BODY_ONE_STEP(ld_r8_r8);

public:
    void activate(std::uint8_t *dest, std::uint8_t *src)
    {
        set_active_in_cpu();

        this->dest = dest;
        this->src = src;
    };

private:
    std::uint8_t *dest = nullptr;
    std::uint8_t *src = nullptr;
};


OPERATION_CLASS_HEADER(ld_r8_n8)
{
    OPERATION_CLASS_BODY_TWO_STEPS(ld_r8_n8);

// TODO KB: Should activate() be private and friend cpu?
public:
    void activate(std::uint8_t *dest)
    {
        set_active_in_cpu();

        this->dest = dest;
    }

private:
    std::uint8_t *dest = nullptr;
};

OPERATION_CLASS_HEADER(ld_r8_ihl)
{
    OPERATION_CLASS_BODY_TWO_STEPS(ld_r8_ihl);

public:
    void activate(std::uint8_t *dest)
    {
        set_active_in_cpu();

        this->dest = dest;
    }

private:
    std::uint8_t *dest = nullptr;
};

OPERATION_CLASS_HEADER(ld_ihl_r8)
{
    OPERATION_CLASS_BODY_TWO_STEPS(ld_ihl_r8);

public:
    void activate(std::uint8_t *src)
    {
        set_active_in_cpu();

        this->src = src;
    }

private:
    std::uint8_t *src = nullptr;
};

OPERATION_CLASS_HEADER(ld_ihl_n8)
{
    OPERATION_CLASS_BODY_THREE_STEPS(ld_ihl_n8);

public:
    void activate()
    {
        set_active_in_cpu();
    }
};

}

#undef OPERATION_CLASS_HEADER
#undef OPERATION_CLASS_BODY

#endif //OP_CODE_H
