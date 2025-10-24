#include <iostream>
#include <iomanip>
#include "Disassembler.h"

int main() {
    Disassembler disassembler;

    uint32_t instructions[] = {
        0xFE010113,
        0x00812E23,
        0x02010413,
        0xFEA42623,
        0xFEC42783,
        0x02F787B3,
        0x00078513,
        0x01C12403,
        0x02010113,
        0x00008067,
    };

    int numInstructions = sizeof(instructions) / sizeof(instructions[0]);

    std::cout << "RISC-V Disassembler" << std::endl;
    std::cout << "===================" << std::endl << std::endl;

    for (int i = 0; i < numInstructions; i++) {
        std::cout << "[" << std::setw(2) << i << "] 0x" << std::hex << std::setw(8) << std::setfill('0')
                  << instructions[i] << std::dec << std::setfill(' ') << " -> "
                  << disassembler.disassemble(instructions[i]) << std::endl;
    }

    return 0;
}
