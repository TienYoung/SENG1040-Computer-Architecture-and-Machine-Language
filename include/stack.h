#include "hc08.h"

#include <stdlib.h>
#include <string.h>

#define STACK_SIZE      0xFFFF // 65536
#define DATA_SIZE       0xFFFF // 65536
#define VIRTUAL_SIZE       0xFFFF // 65536

byte_t* program;

struct Memory
{
    uint32_t stack[STACK_SIZE];
    byte_t data[DATA_SIZE];
    byte_t virtual[VIRTUAL_SIZE];
} memory = { .stack = {0}, .virtual = {0}, .data = {0} };

struct Register
{
    byte_t A;    // Accumulator
    uint16_t IR;  // Index Register(H:X)
    uint16_t SP;  // Stack Pointer;
    uint16_t PC;  // Program Counter;
    byte_t CCR;  // Condition Code Register;
    // H I N Z C
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

void LDA(byte_t bytes[], ADDRESS_MODE mode)
{
    switch (mode)
    {
        case EXT:
            reg.A = memory.data[BSWAP_16(bytes)];
            reg.PC += 2;
        break;
    }
}

void test()
{
    memory.data[0x0101] = 'S';
}

int parse()
{
    unsigned char opcode = memory.virtual[reg.PC++];
    switch (opcode)
    {
    case 0xC6:
        printf("LDA(Load(EXT));\n");
        LDA(&memory.virtual[reg.PC], EXT);
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