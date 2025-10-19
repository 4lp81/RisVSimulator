//
// Created by arsla on 19.10.2025.
//

#include "CPU.h"
#include <iostream>
#include <iomanip>

CPU::CPU(InsMem* mem) : _instrMem(mem), _pc(0) {
    reset();
}

void CPU::reset() {
    // Initialize all registers to 0
    for (int i = 0; i < 32; i++) {
        _registers[i] = 0;
    }
    _pc = 0;
}

// Extract opcode (bits 6-0)
uint32_t CPU::getOpcode(uint32_t instruction) {
    return instruction & 0x7F;
}

// Extract funct3 (bits 14-12)
uint32_t CPU::getFunct3(uint32_t instruction) {
    return (instruction >> 12) & 0x7;
}

// Extract funct7 (bits 31-25)
uint32_t CPU::getFunct7(uint32_t instruction) {
    return (instruction >> 25) & 0x7F;
}

// Extract rd (destination register, bits 11-7)
uint32_t CPU::getRd(uint32_t instruction) {
    return (instruction >> 7) & 0x1F;
}

// Extract rs1 (source register 1, bits 19-15)
uint32_t CPU::getRs1(uint32_t instruction) {
    return (instruction >> 15) & 0x1F;
}

// Extract rs2 (source register 2, bits 24-20)
uint32_t CPU::getRs2(uint32_t instruction) {
    return (instruction >> 20) & 0x1F;
}

// Extract immediate for I-type instructions (bits 31-20)
int32_t CPU::getImmI(uint32_t instruction) {
    // Sign-extend the 12-bit immediate
    int32_t imm = (instruction >> 20) & 0xFFF;
    if (imm & 0x800) { // If sign bit is set
        imm |= 0xFFFFF000; // Sign extend
    }
    return imm;
}

// Execute ADD instruction: rd = rs1 + rs2
void CPU::executeADD(uint32_t rd, uint32_t rs1, uint32_t rs2) {
    if (rd != 0) { // x0 is always 0 in RISC-V
        _registers[rd] = _registers[rs1] + _registers[rs2];
    }
    std::cout << "ADD x" << rd << ", x" << rs1 << ", x" << rs2
              << " -> x" << rd << " = " << _registers[rd] << std::endl;
}

// Execute ADDI instruction: rd = rs1 + imm
void CPU::executeADDI(uint32_t rd, uint32_t rs1, int32_t imm) {
    if (rd != 0) { // x0 is always 0 in RISC-V
        _registers[rd] = _registers[rs1] + imm;
    }
    std::cout << "ADDI x" << rd << ", x" << rs1 << ", " << imm
              << " -> x" << rd << " = " << _registers[rd] << std::endl;
}

void CPU::step() {
    // Fetch instruction
    uint32_t instruction = _instrMem->fetchInstruction(_pc);

    std::cout << "Executing instruction at PC=" << std::hex << "0x" << _pc
              << ": 0x" << instruction << std::dec << std::endl;

    // Decode opcode
    uint32_t opcode = getOpcode(instruction);
    uint32_t funct3 = getFunct3(instruction);
    uint32_t funct7 = getFunct7(instruction);

    uint32_t rd = getRd(instruction);
    uint32_t rs1 = getRs1(instruction);
    uint32_t rs2 = getRs2(instruction);

    // Decode and execute instruction
    switch (opcode) {
        case 0x33: // R-type instructions (ADD, SUB, etc.)
            if (funct3 == 0x0 && funct7 == 0x00) {
                // ADD instruction
                executeADD(rd, rs1, rs2);
            } else {
                std::cout << "Unknown R-type instruction" << std::endl;
            }
            break;

        case 0x13: // I-type instructions (ADDI, etc.)
            if (funct3 == 0x0) {
                // ADDI instruction
                int32_t imm = getImmI(instruction);
                executeADDI(rd, rs1, imm);
            } else {
                std::cout << "Unknown I-type instruction" << std::endl;
            }
            break;

        default:
            std::cout << "Unknown opcode: 0x" << std::hex << opcode << std::dec << std::endl;
            break;
    }

    // Increment PC by 4 (next instruction)
    _pc += 4;
}

void CPU::run(uint32_t numInstructions) {
    for (uint32_t i = 0; i < numInstructions; i++) {
        step();
        std::cout << "---" << std::endl;
    }
}

uint32_t CPU::getRegister(uint32_t reg) {
    if (reg < 32) {
        return _registers[reg];
    }
    return 0;
}

void CPU::setRegister(uint32_t reg, uint32_t value) {
    if (reg != 0 && reg < 32) { // x0 is always 0
        _registers[reg] = value;
    }
}

uint32_t CPU::getPC() {
    return _pc;
}

void CPU::printRegisters() {
    std::cout << "\n=== Register State ===" << std::endl;
    for (int i = 0; i < 32; i++) {
        std::cout << "x" << std::setw(2) << i << " = "
                  << std::setw(10) << _registers[i]
                  << " (0x" << std::hex << std::setw(8) << std::setfill('0')
                  << _registers[i] << std::dec << std::setfill(' ') << ")";
        if ((i + 1) % 2 == 0) {
            std::cout << std::endl;
        } else {
            std::cout << "    ";
        }
    }
    std::cout << "PC  = " << std::setw(10) << _pc
              << " (0x" << std::hex << std::setw(8) << std::setfill('0')
              << _pc << std::dec << std::setfill(' ') << ")" << std::endl;
    std::cout << "=====================\n" << std::endl;
}