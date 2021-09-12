/*
 * Implementations for the CPU instructions in the stack operations group.
 *
 */

#include "i8080.h"

// Load immediate stack pointer
void CPU_8080::LXI_SP(uint8_t hi, uint8_t lo)
{
    uint16_t address = (hi << 8) | lo;
    sp = address;
    pc += 3;
    cycles += 10;
}

// Push Register Pair D & E on stack
void CPU_8080::PUSH_D()
{
    memory[sp-1] = d;
    memory[sp-2] = e;
    sp = sp - 2;
    pc += 1;
}

// Push Register Pair H & L on stack
void CPU_8080::PUSH_H()
{
    memory[sp-1] = h;
    memory[sp-2] = l;
    sp = sp - 2;
    pc += 1;
    cycles += 11;
}

// Pop Register Pair H & L off stack
void CPU_8080::POP_H()
{
    l = memory[sp];
    h = memory[sp+1];
    sp = sp + 2;
    pc += 1;
    cycles += 10;
}

// Push Register Pair B & C on stack
void CPU_8080::PUSH_B()
{
    memory[sp-1] = b;
    memory[sp-2] = c;
    sp = sp - 2;
    pc += 1;
    cycles += 11;
}

// Pop Register Pair B & C off stack
void CPU_8080::POP_B()
{
    c = memory[sp];
    b = memory[sp+1];
    sp = sp + 2;
    pc += 1;
    cycles += 10;
}

// Pop Register Pair D & E off stack
void CPU_8080::POP_D()
{
    e = memory[sp];
    d = memory[sp+1];
    sp = sp + 2;
    pc += 1;
    cycles += 10;
}

// Push Flags and A on stack
void CPU_8080::PUSH_PSW()
{
    uint8_t flags = 0x00;
    if (cc.cy) { flags |= 0x01; }   // bit 0
                 flags |= 0x02;     // bit 1 always set
    if (cc.p)  { flags |= 0x04; }   // bit 2
                                    // bit 3 always 0
    if (cc.ac) { flags |= 0x10; }   // bit 4
                                    // bit 5 always 0
    if (cc.z)  { flags |= 0x40; }   // bit 6
    if (cc.s)  { flags |= 0x80; }   // bit 7

    memory[sp-1] = a;
    memory[sp-2] = flags;
    sp = sp - 2;
    pc += 1;
    cycles += 11;
}

// Pop Flags and A Off Stack
void CPU_8080::POP_PSW()
{
    uint8_t flags = memory[sp];
    cc.cy = (flags & 0x01) != 0;   // bit 0
    cc.p  = (flags & 0x04) != 0;   // bit 2
    cc.ac = (flags & 0x10) != 0;   // bit 4
    cc.z  = (flags & 0x40) != 0;   // bit 6
    cc.s  = (flags & 0x80) != 0;   // bit 7

    a = memory[sp+1];
    sp = sp + 2;
    pc += 1;
    cycles += 10;
}
