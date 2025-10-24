cmake_minimum_required(VERSION 4.0)
project(RisVSimulator)

set(CMAKE_CXX_STANDARD 26)

add_executable(RiscVSimulator main.cpp
        Disassembler.cpp
        Disassembler.h
        Disassembler.cpp
)
