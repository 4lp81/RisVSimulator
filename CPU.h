//
// Created by arsla on 19.10.2025.
//

#ifndef RISVSIMULATOR_CPU_H
#define RISVSIMULATOR_CPU_H

#include <stdint.h>
#include "InsMem.h"

class CPU {
private:
    // 32 general-purpose registers (x0-x31)
    uint32_t _registers[32];

    // Program counter
    uint32_t _pc;

    // Instruction memory
    InsMem* _instrMem;

    // Decode instruction fields
    uint32_t getOpcode(uint32_t instruction);
    uint32_t getFunct3(uint32_t instruction);
    uint32_t getFunct7(uint32_t instruction);
    uint32_t getRd(uint32_t instruction);
    uint32_t getRs1(uint32_t instruction);
    uint32_t getRs2(uint32_t instruction);
    int32_t getImmI(uint32_t instruction);

    // Execute instructions
    void executeADD(uint32_t rd, uint32_t rs1, uint32_t rs2);
    void executeADDI(uint32_t rd, uint32_t rs1, int32_t imm);

public:
    CPU(InsMem* mem);

    // Reset CPU state
    void reset();

    // Execute one instruction
    void step();

    // Run multiple instructions
    void run(uint32_t numInstructions);

    // Register access for debugging
    uint32_t getRegister(uint32_t reg);
    void setRegister(uint32_t reg, uint32_t value);

    // Get PC
    uint32_t getPC();

    // Print register state
    void printRegisters();
};

#endif //RISVSIMULATOR_CPU_H