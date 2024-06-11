#include "hc08.h"

#include <stdlib.h>
#include <string.h>

#define STACK_SIZE      0xFFFF // 65536
#define VIRTUAL_SIZE       0xFFFF // 65536

byte_t* program;

struct Memory
{
    uint32_t stack[STACK_SIZE];
    byte_t virtual[VIRTUAL_SIZE];
} memory = {.stack = {0}, .virtual = {0}};

struct Registers
{
    uint16_t IR;  // Index Register(H:X)
    uint16_t SP;  // Stack Pointer;
    uint16_t PC;  // Program Counter;
    byte_t A;     // Accumulator
    struct CCR    // Condition Code Register;
    {
        byte_t V : 1;
        byte_t _1 : 1;
        byte_t _2 : 1;
        byte_t H : 1;
        byte_t I : 1;
        byte_t N : 1;
        byte_t Z : 1;
        byte_t C : 1;
    } ccr;
} registers;

void display_registers(const char* instruction)
{
    printf("Current: %s\n", instruction);
    printf("Registers:\n");
    printf("  Accumulator: %#X\n", registers.A);
    printf("  Index Register: %#X\n", registers.IR);
    printf("  Stack Pointer: %#X\n", registers.SP);
    printf("  Program Counter: %#X\n", registers.PC);
    printf("  Condition Code Register:\n");
    printf("    V:%d H:%d I:%d N:%d Z:%d C:%d\n",
        registers.ccr.V,
        registers.ccr.H,
        registers.ccr.I,
        registers.ccr.N,
        registers.ccr.Z,
        registers.ccr.C
    );
}


typedef enum
{
    IMM, DIR, EXT, IX2, IX1, IX, SP2, SP1, REL
} ADDRESS_MODE;

void Map(byte_t* program, uint32_t size, uint32_t address)
{
    registers.PC = address;
    memcpy(&memory.virtual[registers.PC], program, size);
}


// Instruction Set
void LDHA(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case IMM:
        registers.IR = BSWAP_16(&memory.virtual[registers.PC + 1]);
        registers.PC += 3;
        registers.ccr.V = 0;
        registers.ccr.N = (int16_t)registers.IR < 0;
        registers.ccr.Z = registers.IR == 0;
        break;
    }
}

void TXS()
{
    registers.PC += 1;
    registers.SP = registers.IR - 1;
}

void CLI()
{
    registers.PC += 1;
    registers.ccr.I = 0;
}

void LDA(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case EXT:
        uint16_t ext = BSWAP_16(&memory.virtual[registers.PC + 1]);
        registers.A = memory.virtual[ext];
        registers.PC += 3;
        registers.ccr.V = 0;
        registers.ccr.N = (char_t)registers.A < 0;
        registers.ccr.Z = registers.A == 0;
        break;
    }
}

void AND(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case IMM:
        registers.A &= memory.virtual[registers.PC + 1];
        registers.PC += 2;
        registers.ccr.V = 0;
        registers.ccr.N = (char_t)registers.A < 0;
        registers.ccr.Z = registers.A == 0;
        break;
    }
}

void BEQ(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case REL:
        if (registers.ccr.Z == 1)
        {
            char_t rel = memory.virtual[registers.PC + 1];
            registers.PC += 0x0002 + rel;
        }
        else
        {
            registers.PC += 2;
        }
        break;
    }
}

void STA(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case EXT:
        uint16_t ext = BSWAP_16(&memory.virtual[registers.PC + 1]);
        memory.virtual[ext] = registers.A;
        registers.PC += 3;
        registers.ccr.V = 0;
        registers.ccr.N = (char_t)registers.A < 0;
        registers.ccr.Z = registers.A == 0;
        break;
    }
}

void JMP(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case EXT:
        uint16_t ext = BSWAP_16(&memory.virtual[registers.PC + 1]);
        registers.PC = ext;
        break;
    }
}

void step()
{
    unsigned char opcode = memory.virtual[registers.PC];
    switch (opcode)
    {
    case 0x45:
        LDHA(IMM);
        display_registers("LDHA(IMM)");
        break;
    case 0x94:
        TXS();
        display_registers("TXS");
        break;
    case 0x9A:
        CLI();
        display_registers("CLI");
        break;
    case 0xC6:
        LDA(EXT);
        display_registers("LDA(EXT)");
        break;
    case 0xA4:
        AND(IMM);
        display_registers("AND(IMM)");
        break;
    case 0x27:
        BEQ(REL);
        display_registers("BEQ(REL)");
        break;
    case 0xC7:
        STA(EXT);
        display_registers("STA(EXT)");
        break;
    case 0xCC:
        JMP(EXT);
        display_registers("JMP(EXT)");
        break;
    default:
        fprintf(stderr, "Warning: Unknown opcode %#X\n", opcode);
        break;
    }
}