/*
 * Test file for increment and decrement group instructions
 *
 */

#include <string>
#include <gtest/gtest.h>

#include "../include/i8080.h"

TEST(IncDecGroup, INX_H_VerifyIncrementNoOverflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0xde);
    cpu.Set_l(0xad);
    cpu.WriteMemoryAt(0x0000, 0x23); // INX_H instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xde, cpu.Get_h());
    ASSERT_EQ(0xae, cpu.Get_l());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INX_H_VerifyIncrementResetsRegWhenOverflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0xff);
    cpu.Set_l(0xff);
    cpu.WriteMemoryAt(0x0000, 0x23); // INX_H instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x00, cpu.Get_h());
    ASSERT_EQ(0x00, cpu.Get_l());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INX_D_VerifyIncrementNoOverflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0xde);
    cpu.Set_e(0xad);
    cpu.WriteMemoryAt(0x0000, 0x13); // INX_D instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xde, cpu.Get_d());
    ASSERT_EQ(0xae, cpu.Get_e());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INX_D_VerifyIncrementResetsRegWhenOverflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0xff);
    cpu.Set_e(0xff);
    cpu.WriteMemoryAt(0x0000, 0x13); // INX_D instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x00, cpu.Get_d());
    ASSERT_EQ(0x00, cpu.Get_e());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_B_VerifyNormalDecrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0x1a);
    cpu.WriteMemoryAt(0x0000, 0x05); // DCR_B

    cpu.RegularInstruction();

    ASSERT_EQ(0x19, cpu.Get_b());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_B_WhenBIs0ThenWrapToFf)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0x00);
    cpu.WriteMemoryAt(0x0000, 0x05); // DCR_B

    cpu.RegularInstruction();

    ASSERT_EQ(0xff, cpu.Get_b());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_C_VerifyNormalDecrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_c(0x1a);
    cpu.WriteMemoryAt(0x0000, 0x0d); // DCR_C

    cpu.RegularInstruction();

    ASSERT_EQ(0x19, cpu.Get_c());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_C_WhenBIs0ThenWrapToFf)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_c(0x00);
    cpu.WriteMemoryAt(0x0000, 0x0d); // DCR_C

    cpu.RegularInstruction();

    ASSERT_EQ(0xff, cpu.Get_c());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_M_VerifyNormalDecrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x3a);
    cpu.Set_l(0x7c);
    cpu.WriteMemoryAt(0x3a7c, 0x40);
    cpu.WriteMemoryAt(0x0000, 0x35); // DCR_M

    cpu.RegularInstruction();

    ASSERT_EQ(0x3f, cpu.ReadMemoryAt(0x3a7c));
    ASSERT_EQ(0x01, cpu.Get_pc());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
}

TEST(IncDecGroup, DCR_M_WhenMIs0ThenWrapToFf)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x3a);
    cpu.Set_l(0x7c);
    cpu.WriteMemoryAt(0x3a7c, 0x00);
    cpu.WriteMemoryAt(0x0000, 0x35); // DCR_M

    cpu.RegularInstruction();

    ASSERT_EQ(0xff, cpu.ReadMemoryAt(0x3a7c));
    ASSERT_EQ(0x01, cpu.Get_pc());
    ASSERT_EQ(false, cpu.Get_z());
    ASSERT_EQ(true, cpu.Get_s());
    ASSERT_EQ(true, cpu.Get_p());
}

TEST(IncDecGroup, DCR_A_VerifyNormalDecrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x1a);
    cpu.WriteMemoryAt(0x0000, 0x3d); // DCR_A

    cpu.RegularInstruction();

    ASSERT_EQ(0x19, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_A_WhenBIs0ThenWrapToFf)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x00);
    cpu.WriteMemoryAt(0x0000, 0x3d); // DCR_A

    cpu.RegularInstruction();

    ASSERT_EQ(0xff, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INX_B_VerifyIncrementNoOverflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0xde);
    cpu.Set_c(0xad);
    cpu.WriteMemoryAt(0x0000, 0x03); // INX_B instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xde, cpu.Get_b());
    ASSERT_EQ(0xae, cpu.Get_c());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INX_B_VerifyIncrementResetsRegWhenOverflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0xff);
    cpu.Set_c(0xff);
    cpu.WriteMemoryAt(0x0000, 0x03); // INX_B instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0x00, cpu.Get_b());
    ASSERT_EQ(0x00, cpu.Get_c());
    ASSERT_EQ(0x01, cpu.Get_pc());
}


TEST(IncDecGroup, DCX_H_VerifyDecrementNoUnderflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0xde);
    cpu.Set_l(0xad);
    cpu.WriteMemoryAt(0x0000, 0x2b); // DCX_H instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xde, cpu.Get_h());
    ASSERT_EQ(0xac, cpu.Get_l());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCX_H_VerifyDecrementWithUnderflow)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x00);
    cpu.Set_l(0x00);
    cpu.WriteMemoryAt(0x0000, 0x2b); // DCX_H instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xff, cpu.Get_h());
    ASSERT_EQ(0xff, cpu.Get_l());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_D_VerifyNormalDecrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0x1a);
    cpu.WriteMemoryAt(0x0000, 0x15); // DCR_D

    cpu.RegularInstruction();

    ASSERT_EQ(0x19, cpu.Get_d());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, DCR_D_WhenBIs0ThenWrapToFf)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0x00);
    cpu.WriteMemoryAt(0x0000, 0x15); // DCR_D

    cpu.RegularInstruction();

    ASSERT_EQ(0xff, cpu.Get_d());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INR_B_VerifyNormalIncrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0x1a);
    cpu.WriteMemoryAt(0x0000, 0x04); // INR_B

    cpu.RegularInstruction();

    ASSERT_EQ(0x1b, cpu.Get_b());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INR_B_WhenBIsFfThenWrapTo00)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0xff);
    cpu.WriteMemoryAt(0x0000, 0x04); // INR_B

    cpu.RegularInstruction();

    ASSERT_EQ(0x00, cpu.Get_b());
    ASSERT_EQ(true, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INR_A_VerifyNormalIncrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x1a);
    cpu.WriteMemoryAt(0x0000, 0x3c); // INR_A

    cpu.RegularInstruction();

    ASSERT_EQ(0x1b, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INR_A_WhenAIsFfThenWrapTo00)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xff);
    cpu.WriteMemoryAt(0x0000, 0x3c); // INR_A

    cpu.RegularInstruction();

    ASSERT_EQ(0x00, cpu.Get_a());
    ASSERT_EQ(true, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INR_D_VerifyNormalIncrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0x1a);
    cpu.WriteMemoryAt(0x0000, 0x14); // INR_D

    cpu.RegularInstruction();

    ASSERT_EQ(0x1b, cpu.Get_d());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INR_D_WhenDIsFfThenWrapTo00)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0xff);
    cpu.WriteMemoryAt(0x0000, 0x14); // INR_D

    cpu.RegularInstruction();

    ASSERT_EQ(0x00, cpu.Get_d());
    ASSERT_EQ(true, cpu.Get_z());
    ASSERT_EQ(false, cpu.Get_s());
    ASSERT_EQ(false, cpu.Get_cy());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(IncDecGroup, INR_M_VerifyNormalIncrement)
{
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x23);
    cpu.Set_l(0x45);
    cpu.WriteMemoryAt(0x0000, 0x34); // INR_M
    cpu.WriteMemoryAt(0x2345, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbc, cpu.ReadMemoryAt(0x2345));
    ASSERT_EQ(0x01, cpu.Get_pc());
}
