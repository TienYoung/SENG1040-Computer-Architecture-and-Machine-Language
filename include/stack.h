#define STACK_SIZE 65536

typedef struct
{
    unsigned int stack[STACK_SIZE];
} Memory;

typedef struct
{
    unsigned char A;    // Accumulator
    unsigned short IR;  // Index Register(H:X)
    unsigned short SP;  // Stack Pointer;
    unsigned short PC;  // Program Counter;
    unsigned char CCR;  // Condition Code Register;
    // H I N Z C
} Register;

typedef enum
{
    IMM, DIR, EXT, IX2, IX1, IX, SP2, SP1, REL
} ADDRESS_MODE;

const char* Load(ADDRESS_MODE mode)
{
    // fetch regiter.pc
}

int parse(void)
{
    unsigned char opcode = 0xC6;
    switch (opcode)
    {
    case 0xC6:
        LDA(Load(EXT));
        break;
    case 0xA4:
        AND(Load(IMM));
        break;
    case 0x27:
        BEQ(Load(REL));
        break;
    case 0xC7:
        STA(Load(EXT));
        break;
    case 0xCC:
        JMP(Load(EXT));
        break;
    }
}