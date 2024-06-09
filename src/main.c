#include <stdio.h>
#include <stdlib.h>

#include "elf.h"
#include "stack.h"

int main(int argc, char* argv[]) {
    printf("HC08 emulator\n");

    const char* filename = "project1_strip.abs";

    FILE* file = fopen(filename, "rb");
    if(file == NULL)
    {
        fprintf(stderr, "Error: cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // fpos_t pos = 0;
    fseek(file, E_PHOFF, SEEK_SET);
    unsigned char bytes[4] = {0x00, 0x00, 0x00, 0x00};
    fread(bytes, 1, sizeof(bytes), file);
    
    printf("Program offset: %#X", __builtin_bswap32(*(int*)bytes));


    // fseek(file, END_OF_HEADER, SEEK_SET);
    

    // while (!feof(file))
    // {
    //     char byte;
    //     fread(&byte, 1, 1, file);
        
    //     parse(byte);
    // }

    if(fclose(file) != 0)
    {
        fprintf(stderr, "Error: cannot close file: %s\n", filename);
    }

    return EXIT_SUCCESS;
}