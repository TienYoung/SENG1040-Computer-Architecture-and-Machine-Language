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

int parse(unsigned char opcode)
{
    switch (opcode)
    {
    case 0xC6:
        printf("LDA(Load(EXT));\n");
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