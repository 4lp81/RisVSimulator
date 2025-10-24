#ifndef RISVSIMULATOR_DISASSEMBLER_H
#define RISVSIMULATOR_DISASSEMBLER_H

#include <cstdint>
#include <string>

// Instruction field masks and shifts
#define OPCODE_MASK         0x7F
#define RD_MASK             0x1F
#define RD_SHIFT            7
#define FUNCT3_MASK         0x7
#define FUNCT3_SHIFT        12
#define RS1_MASK            0x1F
#define RS1_SHIFT           15
#define RS2_MASK            0x1F
#define RS2_SHIFT           20
#define FUNCT7_MASK         0x7F
#define FUNCT7_SHIFT        25

// I-Type immediate
#define IMM_I_MASK          0xFFF
#define IMM_I_SHIFT         20
#define IMM_I_SIGN_BIT      0x800
#define IMM_I_SIGN_EXT      0xFFFFF000

// S-Type immediate
#define IMM_S_LOW_MASK      0x1F
#define IMM_S_LOW_SHIFT     7
#define IMM_S_HIGH_MASK     0x7F
#define IMM_S_HIGH_SHIFT    25
#define IMM_S_SIGN_BIT      0x800
#define IMM_S_SIGN_EXT      0xFFFFF000

// Opcodes
#define OPCODE_R_TYPE       0x33
#define OPCODE_I_ARITH      0x13
#define OPCODE_I_LOAD       0x03
#define OPCODE_S_TYPE       0x23

// funct3 values for R-Type
#define FUNCT3_ADD_SUB      0x0
#define FUNCT3_SLL          0x1
#define FUNCT3_SLT          0x2
#define FUNCT3_SLTU         0x3
#define FUNCT3_XOR          0x4
#define FUNCT3_SRL_SRA      0x5
#define FUNCT3_OR           0x6
#define FUNCT3_AND          0x7

// funct7 values for R-Type
#define FUNCT7_ADD_SLL_etc  0x00
#define FUNCT7_SUB_SRA      0x20

// Instruction format structs mit bitfields
struct RType {
    uint32_t opcode : 7;
    uint32_t rd : 5;
    uint32_t funct3 : 3;
    uint32_t rs1 : 5;
    uint32_t rs2 : 5;
    uint32_t funct7 : 7;
};

struct IType {
    uint32_t opcode : 7;
    uint32_t rd : 5;
    uint32_t funct3 : 3;
    uint32_t rs1 : 5;
    int32_t imm : 12;
};

struct SType {
    uint32_t opcode : 7;
    uint32_t imm_low : 5;
    uint32_t funct3 : 3;
    uint32_t rs1 : 5;
    uint32_t rs2 : 5;
    uint32_t imm_high : 7;
};
union Instruction {
    uint32_t asInt;
    RType r;
    IType i;
    SType s;
};


class Disassembler {
public:
    Disassembler();

    // Disassemble a single 32-bit instruction
    std::string disassemble(uint32_t instruction);

private:
    // Helper functions for decoding different instruction types
    std::string decodeRType(uint32_t instruction);
    std::string decodeIType(uint32_t instruction);
    std::string decodeSType(uint32_t instruction);
};

#endif //RISVSIMULATOR_DISASSEMBLER_H
