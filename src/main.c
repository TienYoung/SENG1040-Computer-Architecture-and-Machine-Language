#include <stdio.h>
#include <stdlib.h>

#include "elf.h"
#include "hc08.h"
#include "stack.h"

#define FILE_CHECK(call) do {                   \
    if(call != 0)                               \
    {                                           \
        fprintf(stderr, "ERROR: file io\n");    \
    }                                           \
} while(0)                                      \

int main(int argc, char* argv[]) {
    printf("HC08 emulator\n");

    const char* filename = "project1_strip.abs";

    FILE* file = fopen(filename, "rb");
    if(file == NULL)
    {
        fprintf(stderr, "Error: cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    byte_t _2_bytes[2] = {0x00, 0x00};
    byte_t _4_bytes[4] = {0x00, 0x00, 0x00, 0x00};

    // File header
    fseek(file, E_PHOFF, SEEK_SET);
    fread(_4_bytes, sizeof(byte_t), 4, file);
    uint32_t e_phoff = BSWAP_32(_4_bytes);

    fseek(file, E_PHNUM, SEEK_SET);
    fread(_2_bytes, sizeof(byte_t), 2, file);
    uint16_t e_phnum = BSWAP_16(_2_bytes);

    fseek(file, E_PHENTSIZE, SEEK_SET);
    fread(_2_bytes, sizeof(byte_t), 2, file);
    uint16_t e_phentsize = BSWAP_16(_2_bytes);
    
    printf("File header:\n");
    printf("PH offest:\t%#x\n", e_phoff);
    printf("PH Size:\t%#x\n", e_phentsize);
    printf("PH Numer:\t%#x\n", e_phnum);
    puts("");

    // Program header
    for(size_t i = 0; i < e_phnum; i ++)
    {
        // Identifies the type of the segment.
        fseek(file, e_phoff + e_phentsize * i + P_TYPE, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_type = BSWAP_32(_4_bytes);

        // Offset of the segment in the file image.
        fseek(file, e_phoff + e_phentsize * i + P_OFFSET, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_offset = BSWAP_32(_4_bytes);

        // Virtual address of the segment in memory.
        fseek(file, e_phoff + e_phentsize * i + P_VADDR, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_vaddr = BSWAP_32(_4_bytes);

        // On systems where physical address is relevant, reserved for segment's physical address.
        fseek(file, e_phoff + e_phentsize * i + P_PADDR, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_paddr = BSWAP_32(_4_bytes);

        // Size in bytes of the segment in the file image. May be 0.
        fseek(file, e_phoff + e_phentsize * i + P_FILESZ, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_filesz = BSWAP_32(_4_bytes);

        // Size in bytes of the segment in memory. May be 0.
        fseek(file, e_phoff + e_phentsize * i + P_MEMSZ, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_memsz = BSWAP_32(_4_bytes);

        // Segment-dependent flags (position for 32-bit structure).
        fseek(file, e_phoff + e_phentsize * i + P_FLAGS, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_flags = BSWAP_32(_4_bytes);

        // 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with p_vaddr equating p_offset modulus p_align.
        fseek(file, e_phoff + e_phentsize * i + P_ALIGN, SEEK_SET);
        fread(_4_bytes, sizeof(byte_t), 4, file);
        uint32_t p_align = BSWAP_32(_4_bytes);

        printf("Program header #%d:\n", i);
        printf("Type:\t\t%#x\n", p_type);
        printf("Offset:\t\t%#x\n", p_offset);
        printf("Vaddr:\t\t%#x\n", p_vaddr);
        printf("Paddr:\t\t%#x\n", p_paddr);
        printf("File size:\t%#x\n", p_filesz);
        printf("Memory size:\t%#x\n", p_memsz);
        printf("Flags:\t\t%#x\n", p_flags);
        printf("Align:\t\t%#x\n", p_align);
        puts("");

        if (i == 1)
        {
            byte_t* program = malloc(p_memsz);
            fseek(file, p_offset, SEEK_SET);
            fread(program, sizeof(byte_t), p_memsz, file);
            Map(program, p_memsz, p_vaddr);
            free(program);
        }
    }

    test();
    parse();
    parse();
    parse();
    parse();
    parse();

    //fseek(file, p_offset, SEEK_SET);
    //fpos_t programStart = 0;
    //FILE_CHECK(fgetpos(file, &programStart));
    //while (1)
    //{
    //    fpos_t programSize = 0;
    //    FILE_CHECK(fgetpos(file, &programSize));
    //    programSize = programSize - programStart;
    //    if (programSize > p_filesz)
    //        break;

    //    byte_t byte;
    //    fread(&byte, sizeof(byte_t), 1, file);

    //    parse(byte);
    //}


    if(fclose(file) != 0)
    {
        fprintf(stderr, "Error: cannot close file: %s\n", filename);
    }

    return EXIT_SUCCESS;
}