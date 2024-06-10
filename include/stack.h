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

struct Register
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
} reg;

typedef enum
{
    IMM, DIR, EXT, IX2, IX1, IX, SP2, SP1, REL
} ADDRESS_MODE;

void Map(byte_t* program, uint32_t size, uint32_t address)
{
    memcpy(&memory.virtual[address], program, size);
    reg.PC = address;
}

void LDHA(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case IMM:
        reg.IR = BSWAP_16(&memory.virtual[reg.PC]);
        reg.PC += 2;
        reg.ccr.V = 0;
        reg.ccr.N = (int)reg.IR < 0;
        reg.ccr.Z = reg.IR == 0;
        break;
    }
}

void TXS()
{
    reg.SP = reg.IR - 1;
    reg.PC++;
}

void CLI()
{
    reg.ccr.I = 0;
    reg.PC++;
}

void LDA(ADDRESS_MODE mode)
{
    switch (mode)
    {
    case EXT:
        reg.A = BSWAP_16(&memory.virtual[reg.PC]);
        reg.PC += 2;
        break;
    }
}

void test()
{
    memory.virtual[0x0101] = 3;
}

void printA()
{
    printf("Accumulator: %d\n", reg.A);
}

int parse()
{
    unsigned char opcode = memory.virtual[reg.PC++];
    switch (opcode)
    {
    case 0x45:
        printf("LDHX(Load(IMM));\n");
        LDHA(IMM);
        break;
    case 0x94:
        printf("TXS();\n");
        TXS();
        break;
    case 0x9A:
        printf("CLI();\n");
        CLI();
        break;
    case 0xC6:
        printf("LDA(Load(EXT));\n");
        LDA(EXT);
        printA();
        break;
    case 0xA4:
        printf("AND(Load(IMM));\n");
        break;
    case 0x27:
        printf("BEQ(Load(REL));\n");
        break;
    case 0xC7:
        printf("STA(Load(EXT));\n");
        break;
    case 0xCC:
        printf("JMP(Load(EXT));\n");
        break;
    default:
        printf("%#X\n", opcode); // data
    }
}