#include "hc08.h"
#include <stdbool.h>
#include <stdio.h>

#define RESULT_CHECK(name)              \
do                                      \
{                                       \
    if(name() == true)                  \
    {                                   \
        printf("Passed: %s\n", #name);  \
    }                                   \
    else                                \
    {                                   \
        printf("Failed: %s\n", #name);  \
    }                                   \
} while (false)

bool test_sub_imm(void)
{
    byte_t opcode = 0xA0;
    bool pass = false;

    /* Overflow: negtive - positive*/
    {
        byte_t A = 0x80;
        byte_t M = 0x01;
        byte_t R = A - M;
        
        // Init
        registers.A = A;
        registers.PC = 0;
        memory.virtual[0] = opcode;
        memory.virtual[1] = M;
        
        // Test
        opcode_map[opcode]();
        
        // Check
        pass = registers.A == R;

        // Show
        if(pass == false)
        {
            display_registers("SUB IMM: A0");
        }

        // Reset
        reset_registers();
        memory.virtual[0] = 0x00;
        memory.virtual[1] = 0x00;
    }

    return pass;
}

bool test_sub_dir(void)
{
    byte_t opcode = 0xB0;
    bool pass = false;

    /* Overflow: negtive - positive*/
    {
        byte_t A = 0x80;
        byte_t M = 0x01;
        byte_t R = A - M;

        byte_t DIR = 0x03;
        
        // Init
        registers.A = A;
        registers.PC = 0;
        memory.virtual[0] = opcode;
        memory.virtual[1] = DIR;
        memory.virtual[DIR] = M;
        
        // Test
        opcode_map[opcode]();
        
        // Check
        pass = registers.A == R;

        // Show
        if(pass == false)
        {
            display_registers("SUB DIR: B0");
        }

        // Reset
        reset_registers();
        memory.virtual[0] = 0x00;
        memory.virtual[1] = 0x00;
        memory.virtual[DIR] = 0x00;
    }

    return pass;
}

bool test_sub_ext(void)
{
    byte_t opcode = 0xC0;
    bool pass = false;

    /* Overflow: negtive - positive*/
    {
        byte_t A = 0x80;
        byte_t M = 0x01;
        byte_t R = A - M;

        uint16_t EXT = 0x0100;
        
        // Init
        registers.A = A;
        registers.PC = 0;
        memory.virtual[0] = opcode;
        memory.virtual[1] = (byte_t)(EXT >> 8);     // little-endian low
        memory.virtual[2] = (byte_t)(EXT & 0x00FF); // little-endian high
        memory.virtual[EXT] = M;
        
        // Test
        opcode_map[opcode]();
        
        // Check
        pass = registers.A == R;

        // Show
        if(pass == false)
        {
            display_registers("SUB EXT: C0");
        }

        // Reset
        reset_registers();
        memory.virtual[0] = 0x00;
        memory.virtual[1] = 0x00;
        memory.virtual[2] = 0x00;
        memory.virtual[EXT] = 0x00;
    }

    return pass;
}

int main(void)
{
    RESULT_CHECK(test_sub_imm);
    RESULT_CHECK(test_sub_dir);
    RESULT_CHECK(test_sub_ext);
}