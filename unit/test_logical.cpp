/*
 * Test file for logical gnd rotate group instructions
 *
 */

#include <string>
#include <gtest/gtest.h>

#include "../include/i8080.h"

using namespace std;

TEST(LogicalGroup, XRA_A_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf0);
    cpu.Set_cy(true);
    cpu.WriteMemoryAt(0x0000, 0xaf); // XRA_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x00, cpu.Get_a());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, ANA_A_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf0);
    cpu.Set_cy(true);
    cpu.Set_s(false);
    cpu.Set_p(false);
    cpu.Set_z(true);
    cpu.WriteMemoryAt(0x0000, 0xa7); // ANA_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xf0, cpu.Get_a());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(true, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, ANA_M_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf0);
    cpu.Set_h(0x23);
    cpu.Set_l(0x45);
    cpu.Set_cy(true);
    cpu.Set_s(false);
    cpu.Set_p(false);
    cpu.Set_z(true);
    cpu.WriteMemoryAt(0x0000, 0xa6); // ANA_M instruction
    cpu.WriteMemoryAt(0x2345, 0xff);

    cpu.RegularInstruction();

    ASSERT_EQ(0xf0, cpu.Get_a());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(true, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, CPI_VerifyEqualNumbers) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf0);
    cpu.WriteMemoryAt(0x0000, 0xfe); // CPI instruction
    cpu.WriteMemoryAt(0x0001, 0xf0);

    cpu.RegularInstruction();


    ASSERT_EQ(0xf0, cpu.Get_a()); // A Must not be modified -__-
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(true, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0002, cpu.Get_pc());
}

TEST(LogicalGroup, CPI_VerifyAIsGreater) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf4);
    cpu.WriteMemoryAt(0x0000, 0xfe); // CPI instruction
    cpu.WriteMemoryAt(0x0001, 0xf0);

    cpu.RegularInstruction();

    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(false, cpu.Get_p());
    ASSERT_EQ(0x0002, cpu.Get_pc());
}

TEST(LogicalGroup, CPI_VerifyDataIsGreater) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf0);
    cpu.WriteMemoryAt(0x0000, 0xfe); // CPI instruction
    cpu.WriteMemoryAt(0x0001, 0xf4);

    cpu.RegularInstruction();

    ASSERT_EQ(true, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(true, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0002, cpu.Get_pc());
}

TEST(LogicalGroup, RRC) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf2);
    cpu.Set_cy(true);
    cpu.WriteMemoryAt(0x0000, 0x0f); // RRC instruction

    cpu.RegularInstruction();

    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(0x79, cpu.Get_a());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, RRC_CarrySet) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0b11110001);
    cpu.Set_cy(false);
    cpu.WriteMemoryAt(0x0000, 0x0f); // RRC instruction

    cpu.RegularInstruction();

    ASSERT_EQ(true, cpu.Get_cy());
    ASSERT_EQ(0b11111000, cpu.Get_a());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, RLC) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xf2);
    cpu.Set_cy(false);
    cpu.WriteMemoryAt(0x0000, 0x07); // RLC instruction

    cpu.RegularInstruction();

    ASSERT_EQ(true, cpu.Get_cy());
    ASSERT_EQ(0xe5, cpu.Get_a());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, ANI) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x3a);
    cpu.WriteMemoryAt(0x0000, 0xe6); // ANI instruction
    cpu.WriteMemoryAt(0x0001, 0x0f);

    cpu.RegularInstruction();

    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0a, cpu.Get_a());
    ASSERT_EQ(0x0002, cpu.Get_pc());
}

TEST(LogicalGroup, ORA_M_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x33);
    cpu.Set_h(0x23);
    cpu.Set_l(0x45);
    cpu.Set_cy(true);
    cpu.Set_z(true);
    cpu.Set_s(true);
    cpu.Set_p(false);
    cpu.WriteMemoryAt(0x0000, 0xb6); // ORA_M instruction
    cpu.WriteMemoryAt(0x2345, 0x0f);

    cpu.RegularInstruction();

    ASSERT_EQ(0x3f, cpu.Get_a());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, ORA_B_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x33);
    cpu.Set_b(0x0f);
    cpu.Set_cy(true);
    cpu.Set_z(true);
    cpu.Set_s(true);
    cpu.Set_p(false);
    cpu.WriteMemoryAt(0x0000, 0xb0); // ORA_B instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x3f, cpu.Get_a());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, ORA_H_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x33);
    cpu.Set_h(0x0f);
    cpu.Set_cy(true);
    cpu.Set_z(true);
    cpu.Set_s(true);
    cpu.Set_p(false);
    cpu.WriteMemoryAt(0x0000, 0xb4); // ORA_H instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x3f, cpu.Get_a());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, RAR) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x6a);
    cpu.Set_cy(true);
    cpu.WriteMemoryAt(0x0000, 0x1f); // RAR instruction

    cpu.RegularInstruction();

    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(0xb5, cpu.Get_a());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, ORI) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xb5);
    cpu.Set_cy(true);
    cpu.WriteMemoryAt(0x0000, 0xf6); // ORI instruction
    cpu.WriteMemoryAt(0x0001, 0x0f);

    cpu.RegularInstruction();

    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(0xbf, cpu.Get_a());
    ASSERT_EQ(0x0002, cpu.Get_pc());
}

TEST(LogicalGroup, CMP_E_Ex1) {
    //
    // Subtracts contents of reg from accumulator
    // Leaving both unchanged.
    // Zero bit is set if both quantities are equal
    // Carry bit set if contents of reg are greater than acc.
    //
    // Before test
    // A            = 0x0a
    // E            = 0x05
    // Subtraction:
    // Acc      = 0AH = 0 0 0 0 1 0 1 0
    // (-E Reg) = -5H = 1 1 1 1 1 0 1 1
    //                  ---------------
    //            +-- 1 0 0 0 0 0 1 0 1 = result
    //            |
    //            +-> carry = 1, causing the carry bit to be reset
    //
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x0a);
    cpu.Set_e(0x05);
    cpu.Set_cy(true);
    cpu.WriteMemoryAt(0x0000, 0xbb); // CMP E instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x0a, cpu.Get_a());
    ASSERT_EQ(0x05, cpu.Get_e());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}

TEST(LogicalGroup, CMP_E_Ex2) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x02);
    cpu.Set_e(0x05);
    cpu.Set_cy(true);
    cpu.WriteMemoryAt(0x0000, 0xbb); // CMP E instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x02, cpu.Get_a());
    ASSERT_EQ(0x05, cpu.Get_e());
    ASSERT_EQ(true, cpu.Get_cy());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(true, cpu.Get_s());
    ASSERT_EQ(false, cpu.Get_p());
    ASSERT_EQ(0x0001, cpu.Get_pc());
}
