#pragma once

typedef enum
{
    IMM, DIR, EXT, IX2, IX1, IX, SP2, SP1, REL
} ADDRESS_MODE;

void LDHA(ADDRESS_MODE mode);
void TXS();
void CLI();
void LDA(ADDRESS_MODE mode);
void AND(ADDRESS_MODE mode);
void BEQ(ADDRESS_MODE mode);
void STA(ADDRESS_MODE mode);
void JMP(ADDRESS_MODE mode);