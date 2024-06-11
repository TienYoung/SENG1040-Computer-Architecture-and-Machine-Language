#include "hc08.h"

#include "stdio.h"

Memory memory = {0};
Registers registers = {0};

void Map(byte_t* program, uint32_t size, uint32_t address)
{
    registers.PC = address;
    memcpy(&memory.virtual[registers.PC], program, size);
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
