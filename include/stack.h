#pragma once

#include <stdlib.h>
#include <string.h>

#define STACK_SIZE      0xFFFF // 65536
#define VIRTUAL_SIZE    0xFFFF // 65536

typedef struct
{
    uint32_t stack[STACK_SIZE];
    byte_t virtual[VIRTUAL_SIZE];
} HC08_Memory;