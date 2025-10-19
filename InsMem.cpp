//
// Created by arsla on 15.10.2025.
//

#include "InsMem.h"

#include <iostream>
#include <ostream>

InsMem::InsMem() {
    std::cout << "Instruction Memory initialized" << std::endl;
    uint32_t* pMem = (uint32_t*)_memory;

    // ADDI x1, x0, 10    -> x1 = 0 + 10 = 10
    // Encoding: imm[11:0]=10, rs1=0, funct3=0, rd=1, opcode=0x13
    pMem[0] = 0x00A00093;

    // ADDI x2, x0, 20    -> x2 = 0 + 20 = 20
    // Encoding: imm[11:0]=20, rs1=0, funct3=0, rd=2, opcode=0x13
    pMem[1] = 0x01400113;

    // ADD x3, x1, x2     -> x3 = x1 + x2 = 10 + 20 = 30
    // Encoding: funct7=0, rs2=2, rs1=1, funct3=0, rd=3, opcode=0x33
    pMem[2] = 0x002081B3;

    // ADDI x4, x3, -5    -> x4 = x3 + (-5) = 30 - 5 = 25
    // Encoding: imm[11:0]=-5 (0xFFB), rs1=3, funct3=0, rd=4, opcode=0x13
    pMem[3] = 0xFFB18213;
}


uint32_t InsMem::fetchInstruction(uint32_t addr) {
    std::cout << "fetchInstruction call at" << addr << std::endl;
    //ToDo Von dieser instructions (2 instruction add oder addi) erkennen ob add oder addi
    //und die register usseschrieba
    return *((uint32_t*) &_memory[addr]);
    //return 0; // ToDo implement it
}

