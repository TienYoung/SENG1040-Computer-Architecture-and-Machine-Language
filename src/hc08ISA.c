#include "hc08ISA.h"
#include "hc08.h"
#include "stack.h"


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