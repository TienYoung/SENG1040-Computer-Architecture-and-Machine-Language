#include "hc08.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define RESULT_CHECK(name)              \
do {                                    \
    if(name() == true) {                \
        printf("Passed: %s\n", #name);  \
    }                                   \
    else {                              \
        printf("Failed: %s\n", #name);  \
        registers_display();            \
    }                                   \
    registers_reset();                  \
    memory_reset();                     \
} while (false)

#define EXPECT_REGISTERS(_A, _IR, _SP, _PC, _V, _H, _I, _N, _Z, _C) \
    (registers.A == _A) &&                                          \
    (registers.IR == _IR) &&                                        \
    (registers.SP == _SP) &&                                        \
    (registers.PC == _PC) &&                                        \
    (registers.ccr.V == _V) &&                                      \
    (registers.ccr.H == _H) &&                                      \
    (registers.ccr.I == _I) &&                                      \
    (registers.ccr.N == _N) &&                                      \
    (registers.ccr.Z == _Z) &&                                      \
    (registers.ccr.C == _C)                                         \



bool test_sub_imm(void) {
    byte_t opcode = 0xA0;

    /* Overflow: negative - positive*/
    byte_t A = 0x80;
    byte_t M = 0x01;
    byte_t R = A - M;
    
    // Init
    registers.A = A;
    registers.PC = 0;
    memory[0] = opcode;
    memory[1] = M;
    
    // Test
    opcode_map[opcode]();
        
    return EXPECT_REGISTERS(R, 0x0000, 0x00FF, 0x0002, 1, 0, 1, 0, 0, 0);
}

bool test_sub_dir(void) {
    byte_t opcode = 0xB0;

    /* Overflow: positive - negative*/
    byte_t A = 0x01;
    byte_t M = 0x80;
    byte_t R = A - M;

    byte_t DIR = 0x03;
    
    // Init
    registers.A = A;
    registers.PC = 0;
    memory[0] = opcode;
    memory[1] = DIR;
    memory[DIR] = M;
    
    // Test
    opcode_map[opcode]();
    
    // Check
    return EXPECT_REGISTERS(R, 0x0000, 0x00FF, 0x0002, 1, 0, 1, 1, 0, 1);
}

bool test_sub_ext(void) {
    byte_t opcode = 0xC0;

    /* Zero: negative - negative*/
    byte_t A = 0x80;
    byte_t M = 0x80;
    byte_t R = A - M;

    uint16_t EXT = 0x0100;
    
    // Init
    registers.A = A;
    registers.PC = 0;
    memory[0] = opcode;
    memory[1] = (byte_t)(EXT >> 8);     // little-endian low
    memory[2] = (byte_t)(EXT & 0x00FF); // little-endian high
    memory[EXT] = M;
    
    // Test
    opcode_map[opcode]();
    
    // Check
    return EXPECT_REGISTERS(R, 0x0000, 0x00FF, 0x0003, 0, 0, 1, 0, 1, 0);
}

bool test_sub_ix2(void) {
    byte_t opcode = 0xD0;
    bool pass = false;

    /* Zero: positive - positive*/
    byte_t A = 0x7F;
    byte_t M = 0x7F;
    byte_t R = A - M;

    uint16_t offset = 0x0100;

    // Init
    registers.A = A;
    registers.IR = 0x0100;
    registers.PC = 0;
    memory[0] = opcode;
    memory[1] = (byte_t)(offset >> 8);     // little-endian low
    memory[2] = (byte_t)(offset & 0x00FF); // little-endian high
    memory[registers.IR + offset] = M;
    
    // Test
    opcode_map[opcode]();
    
    // Check
    return EXPECT_REGISTERS(R, registers.IR, 0x00FF, 0x0003, 0, 0, 1, 0, 1, 0);
}

bool test_sub_ix1(void) {
    byte_t opcode = 0xE0;
    bool pass = false;

    /* Positive: big - little */
    byte_t A = 0x7F;
    byte_t M = 0x0F;
    byte_t R = A - M;

    byte_t offset = 0x01;

    // Init
    registers.A = A;
    registers.IR = 0x0100;
    registers.PC = 0;
    memory[0] = opcode;
    memory[1] = offset;
    memory[registers.IR + offset] = M;
    
    // Test
    opcode_map[opcode]();
    
    // Check
    return EXPECT_REGISTERS(R, registers.IR, 0x00FF, 0x0002, 0, 0, 1, 0, 0, 0);
}

bool test_sub_ix(void) {
    byte_t opcode = 0xF0;
    bool pass = false;

    /* Negative: little - big */
    byte_t A = 0x0F;
    byte_t M = 0x7F;
    byte_t R = A - M;

    // Init
    registers.A = A;
    registers.IR = 0x0100;
    registers.PC = 0;
    memory[0] = opcode;
    memory[registers.IR] = M;
    
    // Test
    opcode_map[opcode]();
    
    // Check
    return EXPECT_REGISTERS(R, registers.IR, 0x00FF, 0x0001, 0, 0, 1, 1, 0, 1);
}


int main(void) {
    registers_reset();
    memory_reset();

    RESULT_CHECK(test_sub_imm);
    RESULT_CHECK(test_sub_dir);
    RESULT_CHECK(test_sub_ext);
    RESULT_CHECK(test_sub_ix2);
    RESULT_CHECK(test_sub_ix1);
    RESULT_CHECK(test_sub_ix);
}