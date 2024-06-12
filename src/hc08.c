#include "hc08.h"

#include "stdio.h"

HC08_Memory memory = {0};
HC08_Registers registers = {0};

void Map(byte_t* program, uint32_t size, uint32_t address)
{
    registers.PC = address;
    memcpy(&memory.virtual[registers.PC], program, size);
}

void step()
{
    unsigned char opcode = memory.virtual[registers.PC];
    opcode_map[opcode]();
    printf("Opcode: %x\n", opcode);
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
