#include "hc08.h"

#include "stdio.h"

HC08_Memory memory = {0};
HC08_Registers registers = {0};

void Map(byte_t* program, uint32_t size, uint32_t address)
{
    registers.PC = address;
    memcpy(&memory.virtual[registers.PC], program, size);
}

void reset_registers(void)
{
    registers.A = 0x00;
    registers.IR = 0x0000;
    registers.SP = 0x00FF;
    registers.PC = 0xFFFE;

    registers.ccr.V = 0;
    registers.ccr._6 = 1;
    registers.ccr._5 = 1;
    registers.ccr.H = 0;
    registers.ccr.I = 1;
    registers.ccr.N = 0;
    registers.ccr.Z = 0;
    registers.ccr.C = 0;
}

void step()
{
    unsigned char opcode = memory.virtual[registers.PC];
    opcode_map[opcode]();
    printf("Opcode: %x\n", opcode);
}

void display_registers(const char* instruction)
{
    printf("Instruction: %s\n", instruction);
    printf("Registers:\n");
    printf("  Accumulator: %#X\n", registers.A);
    printf("  Index Register: %#X\n", registers.IR);
    printf("  Stack Pointer: %#X\n", registers.SP);
    printf("  Program Counter: %#X\n", registers.PC);
    printf("  Condition Code Register:\n");
    printf("  V:%d H:%d I:%d N:%d Z:%d C:%d\n",
        registers.ccr.V,
        registers.ccr.H,
        registers.ccr.I,
        registers.ccr.N,
        registers.ccr.Z,
        registers.ccr.C
    );
}
