/*
 * Test file for move group instructions
 *
 */

#include <string>
#include <gtest/gtest.h>

#include "../include/i8080.h"

TEST(MoveGroup, MOV_M_A_VerifyContentsOfACorreclyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x21);
    cpu.Set_l(0xd0);
    cpu.Set_a(0xad);
    cpu.WriteMemoryAt(0x0000, 0x77); // MOV_M_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.ReadMemoryAt(0x21d0));
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_M_B_VerifyContentsOfBCorreclyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x21);
    cpu.Set_l(0xd0);
    cpu.Set_b(0xad);
    cpu.WriteMemoryAt(0x0000, 0x70); // MOV_M_B instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.ReadMemoryAt(0x21d0));
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, STA_VerifyContentsOfACorrectlyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x32); // STA instruction
    cpu.WriteMemoryAt(0x0001, 0x45); // adr lo byte
    cpu.WriteMemoryAt(0x0002, 0x23); // adr hi byte

    cpu.RegularInstruction();

    ASSERT_EQ(0xcc, cpu.ReadMemoryAt(0x2345));
    ASSERT_EQ(0x03, cpu.Get_pc());
}

TEST(MoveGroup, LDA_VerifyACorrectlyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x00);
    cpu.WriteMemoryAt(0x0000, 0x3a); // STA instruction
    cpu.WriteMemoryAt(0x0001, 0x45); // adr lo byte
    cpu.WriteMemoryAt(0x0002, 0x23); // adr hi byte
    cpu.WriteMemoryAt(0x2345, 0xcc);

    cpu.RegularInstruction();

    ASSERT_EQ(0xcc, cpu.Get_a());
    ASSERT_EQ(0x03, cpu.Get_pc());
}

TEST(MoveGroup, MVI_M_VerifyContentsCorrectlyTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x23);
    cpu.Set_l(0x45);

    ASSERT_EQ(0x00, cpu.ReadMemoryAt(0x2345));

    cpu.WriteMemoryAt(0x0000, 0x36); // MVI_M instruction
    cpu.WriteMemoryAt(0x0001, 0xcc); // Operand

    cpu.RegularInstruction();

    ASSERT_EQ(0xcc, cpu.ReadMemoryAt(0x2345));
    ASSERT_EQ(0x02, cpu.Get_pc());
}

TEST(MoveGroup, XCHG_CheckValuesHaveBeenSwapped) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0xde);
    cpu.Set_l(0xad);
    cpu.Set_d(0xbe);
    cpu.Set_e(0xef);

    cpu.WriteMemoryAt(0x0000, 0xeb); // XCHG instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xbe, cpu.Get_h());
    ASSERT_EQ(0xef, cpu.Get_l());
    ASSERT_EQ(0xde, cpu.Get_d());
    ASSERT_EQ(0xad, cpu.Get_e());
}

TEST(MoveGroup, MOV_E_M_VerifyContentsOfACorreclyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x01);
    cpu.Set_l(0xd0);
    cpu.WriteMemoryAt(0x0000, 0x5e); // MOV_E_M instruction
    cpu.WriteMemoryAt(0x01d0, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_e());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_D_M_VerifyContentsOfACorreclyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x01);
    cpu.Set_l(0xd0);
    cpu.WriteMemoryAt(0x0000, 0x56); // MOV_D_M instruction
    cpu.WriteMemoryAt(0x01d0, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_d());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_A_M_VerifyContentsOfACorreclyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x01);
    cpu.Set_l(0xd0);
    cpu.WriteMemoryAt(0x0000, 0x7e); // MOV_A_M instruction
    cpu.WriteMemoryAt(0x01d0, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_C_M_VerifyContentsOfCCorreclyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x01);
    cpu.Set_l(0xd0);
    cpu.WriteMemoryAt(0x0000, 0x4e); // MOV_C_M instruction
    cpu.WriteMemoryAt(0x01d0, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_c());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_H_M_VerifyContentsOfACorreclyLoaded) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x01);
    cpu.Set_l(0xd0);
    cpu.WriteMemoryAt(0x0000, 0x66); // MOV_H_M instruction
    cpu.WriteMemoryAt(0x01d0, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_h());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, STAX_B) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0x3f);
    cpu.Set_c(0x16);
    cpu.Set_a(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x02); // STAX_B instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xcc, cpu.ReadMemoryAt(0x3f16));
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, LDAX_B_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0x23);
    cpu.Set_c(0x45);
    cpu.WriteMemoryAt(0x0000, 0x0a); // LDAX_B instruction
    cpu.WriteMemoryAt(0x2345, 0xbb);
    ASSERT_EQ(0x00, cpu.Get_a());

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, LDAX_D_VerifyNormalOperation) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0x23);
    cpu.Set_e(0x45);
    cpu.WriteMemoryAt(0x0000, 0x1a); // LDAX_D instruction
    cpu.WriteMemoryAt(0x2345, 0xbb);
    ASSERT_EQ(0x00, cpu.Get_a());

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_H_A_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x21);
    cpu.Set_a(0xad);
    cpu.WriteMemoryAt(0x0000, 0x67); // MOV_H_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_h());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_B_A_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0x21);
    cpu.Set_a(0xad);
    cpu.WriteMemoryAt(0x0000, 0x47); // MOV_B_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_b());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_C_A_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_c(0x21);
    cpu.Set_a(0xad);
    cpu.WriteMemoryAt(0x0000, 0x4f); // MOV_C_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_c());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_D_A_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0x21);
    cpu.Set_a(0xad);
    cpu.WriteMemoryAt(0x0000, 0x57); // MOV_D_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_d());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_A_H_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x21);
    cpu.Set_h(0xad);
    cpu.WriteMemoryAt(0x0000, 0x7c); // MOV_A_H instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_A_D_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x21);
    cpu.Set_d(0xad);
    cpu.WriteMemoryAt(0x0000, 0x7a); // MOV_A_D instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_A_B_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x21);
    cpu.Set_b(0xad);
    cpu.WriteMemoryAt(0x0000, 0x78); // MOV_A_B instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_E_A_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_e(0x21);
    cpu.Set_a(0xad);
    cpu.WriteMemoryAt(0x0000, 0x5f); // MOV_E_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_e());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MVI_B_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_b(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x06); // MVI_B instruction
    cpu.WriteMemoryAt(0x0001, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_b());
    ASSERT_EQ(0x02, cpu.Get_pc());
}

TEST(MoveGroup, MVI_A_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x3e); // MVI_A instruction
    cpu.WriteMemoryAt(0x0001, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_a());
    ASSERT_EQ(0x02, cpu.Get_pc());
}

TEST(MoveGroup, MVI_C_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_c(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x0e); // MVI_C instruction
    cpu.WriteMemoryAt(0x0001, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_c());
    ASSERT_EQ(0x02, cpu.Get_pc());
}

TEST(MoveGroup, MVI_D_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_d(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x16); // MVI_D instruction
    cpu.WriteMemoryAt(0x0001, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_d());
    ASSERT_EQ(0x02, cpu.Get_pc());
}

TEST(MoveGroup, MVI_L_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_l(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x2e); // MVI_L instruction
    cpu.WriteMemoryAt(0x0001, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_l());
    ASSERT_EQ(0x02, cpu.Get_pc());
}

TEST(MoveGroup, MVI_H_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0xcc);
    cpu.WriteMemoryAt(0x0000, 0x26); // MVI_H instruction
    cpu.WriteMemoryAt(0x0001, 0xbb);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_h());
    ASSERT_EQ(0x02, cpu.Get_pc());
}

TEST(MoveGroup, LXI_H_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.WriteMemoryAt(0x0000, 0x21); // LXI_H instruction
    cpu.WriteMemoryAt(0x0001, 0x03);
    cpu.WriteMemoryAt(0x0002, 0x01);

    cpu.RegularInstruction();

    ASSERT_EQ(0x01, cpu.Get_h());
    ASSERT_EQ(0x03, cpu.Get_l());
    ASSERT_EQ(0x03, cpu.Get_pc());
}

TEST(MoveGroup, LXI_B_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.WriteMemoryAt(0x0000, 0x01); // LXI_B instruction
    cpu.WriteMemoryAt(0x0001, 0x03);
    cpu.WriteMemoryAt(0x0002, 0x01);

    cpu.RegularInstruction();

    ASSERT_EQ(0x01, cpu.Get_b());
    ASSERT_EQ(0x03, cpu.Get_c());
    ASSERT_EQ(0x03, cpu.Get_pc());
}

TEST(MoveGroup, LXI_D_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.WriteMemoryAt(0x0000, 0x11); // LXI_D instruction
    cpu.WriteMemoryAt(0x0001, 0x03);
    cpu.WriteMemoryAt(0x0002, 0x01);

    cpu.RegularInstruction();

    ASSERT_EQ(0x01, cpu.Get_d());
    ASSERT_EQ(0x03, cpu.Get_e());
    ASSERT_EQ(0x03, cpu.Get_pc());
}

TEST(MoveGroup, LHLD_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.WriteMemoryAt(0x0000, 0x2a); // LHLD instruction
    cpu.WriteMemoryAt(0x0001, 0x33);
    cpu.WriteMemoryAt(0x0002, 0x20);
    cpu.WriteMemoryAt(0x2033, 0xbb);
    cpu.WriteMemoryAt(0x2034, 0xcc);

    cpu.RegularInstruction();

    ASSERT_EQ(0xbb, cpu.Get_l());
    ASSERT_EQ(0xcc, cpu.Get_h());
    ASSERT_EQ(0x03, cpu.Get_pc());
}

TEST(MoveGroup, SHLD_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0xde);
    cpu.Set_l(0xad);
    cpu.WriteMemoryAt(0x0000, 0x22); // SHLD instruction
    cpu.WriteMemoryAt(0x0001, 0x33);
    cpu.WriteMemoryAt(0x0002, 0x20);
    cpu.WriteMemoryAt(0x2033, 0xbb);
    cpu.WriteMemoryAt(0x2034, 0xcc);

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.ReadMemoryAt(0x2033));
    ASSERT_EQ(0xde, cpu.ReadMemoryAt(0x2034));
    ASSERT_EQ(0x03, cpu.Get_pc());
}

TEST(MoveGroup, MOV_A_C_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x21);
    cpu.Set_c(0xad);
    cpu.WriteMemoryAt(0x0000, 0x79); // MOV_A_C instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_A_E_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x21);
    cpu.Set_e(0xad);
    cpu.WriteMemoryAt(0x0000, 0x7b); // MOV_A_E instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_A_L_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_a(0x21);
    cpu.Set_l(0xad);
    cpu.WriteMemoryAt(0x0000, 0x7d); // MOV_A_L instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_a());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_L_A_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_l(0x21);
    cpu.Set_a(0xad);
    cpu.WriteMemoryAt(0x0000, 0x6f); // MOV_L_A instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_l());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_L_B_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_l(0x21);
    cpu.Set_b(0xad);
    cpu.WriteMemoryAt(0x0000, 0x68); // MOV_L_B instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_l());
    ASSERT_EQ(0x01, cpu.Get_pc());
}

TEST(MoveGroup, MOV_H_C_VerifyContentsTransferred) {
    CPU_8080 cpu;
    cpu.Initialize();
    cpu.Set_h(0x21);
    cpu.Set_c(0xad);
    cpu.WriteMemoryAt(0x0000, 0x61); // MOV_H_C instruction

    cpu.RegularInstruction();

    ASSERT_EQ(0xad, cpu.Get_h());
    ASSERT_EQ(0x01, cpu.Get_pc());
}
