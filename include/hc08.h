#pragma once

typedef unsigned char   byte_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef char            char_t;
typedef short           int16_t;
typedef int             int32_t;

#if __GNUC__
    #define BSWAP_16(x) __builtin_bswap16(*(uint16_t*)(x))
    #define BSWAP_32(x) __builtin_bswap32(*(uint32_t*)(x))
#elif __clang__
    #define BSWAP_16(x) __builtin_bswap16(*(uint16_t*)(x))
    #define BSWAP_32(x) __builtin_bswap32(*(uint32_t*)(x))
#else 
    #define BSWAP_16(x) _byteswap_ushort(*(uint16_t*)(x))
    #define BSWAP_32(x) _byteswap_ulong(*(uint32_t*)(x))
#endif

typedef struct 
{
    uint16_t IR; // Index Register(H:X)
    uint16_t SP; // Stack Pointer;
    uint16_t PC; // Program Counter;
    byte_t A;    // Accumulator
    struct CCR   // Condition Code Register;
    {
        byte_t V : 1;
        byte_t _6 : 1;
        byte_t _5 : 1;
        byte_t H : 1;
        byte_t I : 1;
        byte_t N : 1;
        byte_t Z : 1;
        byte_t C : 1;
    } ccr;
} HC08_Registers;

extern HC08_Registers registers;

#define MEM_SIZE 65536
extern byte_t memory[MEM_SIZE]; // 0xFFFF - 64KB

#include "hc08_ops.h"

void memory_map(byte_t *program, uint32_t size, uint32_t address);

void memory_reset(void);

void program_step(void);

void registers_reset(void);

void registers_display(void);

extern void(*hook_exec)(const char* asm, const HC08_Registers* registers, const byte_t* memory);