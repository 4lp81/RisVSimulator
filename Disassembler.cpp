#include "Disassembler.h"
#include <sstream>

Disassembler::Disassembler() {
    // Constructor
}

std::string Disassembler::disassemble(uint32_t instruction) {
    Instruction instr;
    instr.asInt = instruction;

    switch (instr.r.opcode) {
        case OPCODE_R_TYPE:
            return decodeRType(instruction);
        case OPCODE_I_ARITH:
            return decodeIType(instruction);
        case OPCODE_S_TYPE:
            return decodeSType(instruction);
        default:
            return "UNKNOWN COMMAND";
    }
}

std::string Disassembler::decodeRType(uint32_t instruction) {
    Instruction instr;
    instr.asInt = instruction;

    std::string mnemonic = "UNKNOWN COMMAND";

    if (instr.r.funct7 == FUNCT7_ADD_SLL_etc) {
        switch (instr.r.funct3) {
            case FUNCT3_ADD_SUB:
                mnemonic = "add";
                break;
            case FUNCT3_SLL:
                mnemonic = "sll";
                break;
            case FUNCT3_SLT:
                mnemonic = "slt";
                break;
            case FUNCT3_SLTU:
                mnemonic = "sltu";
                break;
            case FUNCT3_XOR:
                mnemonic = "xor";
                break;
            case FUNCT3_SRL_SRA:
                mnemonic = "srl";
                break;
            case FUNCT3_OR:
                mnemonic = "or";
                break;
            case FUNCT3_AND:
                mnemonic = "and";
                break;
        }
    } else if (instr.r.funct7 == FUNCT7_SUB_SRA) {
        switch (instr.r.funct3) {
            case FUNCT3_ADD_SUB:
                mnemonic = "sub";
                break;
            case FUNCT3_SRL_SRA:
                mnemonic = "sra";
                break;
        }
    }

    std::stringstream ss;
    ss << mnemonic << " x" << instr.r.rd << ", x" << instr.r.rs1 << ", x" << instr.r.rs2;
    return ss.str();
}

std::string Disassembler::decodeIType(uint32_t instruction) {
    Instruction instr;
    instr.asInt = instruction;

    std::string mnemonic = "UNKNOWN COMMAND";
    switch (instr.i.funct3) {
        case FUNCT3_ADD_SUB:
            mnemonic = "addi";
            break;
        case FUNCT3_SLL:
            mnemonic = "slli";
            break;
        case FUNCT3_SLT:
            mnemonic = "slti";
            break;
        case FUNCT3_SLTU:
            mnemonic = "sltiu";
            break;
        case FUNCT3_XOR:
            mnemonic = "xori";
            break;
        case FUNCT3_SRL_SRA:
            mnemonic = "srli";
            break;
        case FUNCT3_OR:
            mnemonic = "ori";
            break;
        case FUNCT3_AND:
            mnemonic = "andi";
            break;
    }

    std::stringstream ss;
    ss << mnemonic << " x" << instr.i.rd << ", x" << instr.i.rs1 << ", " << instr.i.imm;
    return ss.str();
}

std::string Disassembler::decodeSType(uint32_t instruction) {
    Instruction instr;
    instr.asInt = instruction;

    // Combine imm_low and imm_high to form complete immediate
    int32_t imm = (instr.s.imm_high << 5) | instr.s.imm_low;

    std::string mnemonic = "UNKNOWN COMMAND";
    switch (instr.s.funct3) {
        case FUNCT3_ADD_SUB:
            mnemonic = "sb";
            break;
        case FUNCT3_SLL:
            mnemonic = "sh";
            break;
        case FUNCT3_SLT:
            mnemonic = "sw";
            break;
    }

    std::stringstream ss;
    ss << mnemonic << " x" << instr.s.rs2 << ", " << imm << "(x" << instr.s.rs1 << ")";
    return ss.str();
}
