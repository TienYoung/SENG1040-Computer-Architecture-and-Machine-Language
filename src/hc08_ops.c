#include "hc08_ops.h"
#include "hc08.h"
#include "stack.h"

// Empty and star
#define OPS_EPT empty_func
#define OPS_STR empty_func
void empty_func(void){}

void(*opcode_map[])(void) = {
/*HIGH\LOW 0           1           2           3           4           5           6           7           8           9           A           B           C           D           E           F   */
/*0*/ BRSET0_DIR, BRCLR0_DIR, BRSET1_DIR, BRCLR1_DIR, BRSET2_DIR, BRCLR2_DIR, BRSET3_DIR, BRCLR3_DIR, BRSET4_DIR, BRCLR4_DIR, BRSET5_DIR, BRCLR5_DIR, BRSET6_DIR, BRCLR6_DIR, BRSET7_DIR, BRCLR7_DIR,
/*1*/  BSET0_DIR,  BCLR0_DIR,  BSET1_DIR,  BCLR1_DIR,  BSET2_DIR,  BCLR2_DIR,  BSET3_DIR,  BCLR3_DIR,  BSET4_DIR,  BCLR4_DIR,  BSET5_DIR,  BCLR5_DIR,  BSET6_DIR,  BCLR6_DIR,  BSET7_DIR,  BCLR7_DIR,
/*2*/    BRA_REL,    BRN_REL,    BHI_REL,    BLS_REL,    BCC_REL,    BCS_REL,    BNE_REL,    BEQ_REL,   BHCC_REL,   BHCS_REL,    BPL_REL,    BMI_REL,    BMC_REL,    BMS_REL,    BIL_REL,    BIH_REL, 
/*3*/    NEG_DIR,   CBEQ_DIR,    OPS_EPT,    COM_DIR,    LSR_DIR,   STHX_DIR,    ROR_DIR,    ASR_DIR,    LSL_DIR,    ROL_DIR,    DEC_DIR,   DBNZ_DIR,    INC_DIR,    TST_DIR,    OPS_EPT,    CLR_DIR, 
/*4*/   NEGA_INH,  CBEQA_IMM,    MUL_INH,   COMA_INH,   LSRA_INH,   LTHX_IMM,   RORA_INH,   ASRA_INH,   LSLA_INH,   ROLA_INH,   DECA_INH,  DBNZA_INH,   INCA_INH,   TSTA_INH,    MOA_DD,    CLRA_INH,
/*5*/   NEGX_INH,  CBEQX_IMM,    DIV_INH,   COMX_INH,   LSRX_INH,   LTHX_DIR,   RORX_INH,   ASRX_INH,   LSLX_INH,   ROLX_INH,   DECX_INH,  DBNZX_INH,   INCX_INH,   TSTX_INH,    MOX_DIX_,  CLRX_INH,
/*6*/    NEG_IX1,   CBEQ_IX1_,   NSA_INH,    COM_IX1,    LSR_IX1,   CPHX_IMM,    ROR_IX1,    ASR_IX1,    LSL_IX1,    ROL_IX1,    DEC_IX1,   DBNZ_IX1,    INC_IX1,    TST_IX1,    MOV_IMD,    CLR_IX1, 
/*7*/    NEG_IX,    CBEQ_IX_ ,   DAA_INN,    COM_IX,     LSR_IX,    CPHX_DIR,    ROR_IX,     ASR_IX,     LSL_IX,     ROL_IX,     DEC_IX ,   DBNZ_IX,     INC_IX,     TST_IX,     MOV_IX_D,   CLR_IX,  
/*8*/    RTI_INH,    RTS_IMM,    OPS_EPT,    SWI_INH,    TAP_INH,    TPA_INH,   PULA_INH,   PSHA_INH,   PULX_INH,   PSHX_INH,   PULH_INH,   PSHH_INH,   CLRH_INH,    OPS_EPT,   STOP_INH,   WAIT_INH, 
/*9*/    BEG_REL,    BLT_REL,    BGT_REL,    BLE_REL,    TXS_INH,    TSX_INH,    OPS_EPT,    TAX_INH,    CLC_INH,    SEC_INH,    CLI_INH,    SEI_INH,    RSP_INH,    NOP_INH,    OPS_STR,    TXA_INH,
/*A*/    SUB_IMM,    CMP_IMM,    SBC_IMM,    CPX_IMM,    AND_IMM,    BIT_IMM,    LDA_IMM,    AIS_IMM,    EOR_IMM,    ADC_IMM,    ORA_IMM,    ADD_IMM,    OPS_EPT,    BSR_REL,    LDX_IMM,    AIX_IMM,
/*B*/    SUB_DIR,    CMP_DIR,    SBC_DIR,    CPX_DIR,    AND_DIR,    BIT_DIR,    LDA_DIR,    STA_DIR,    EOR_DIR,    ADC_DIR,    ORA_DIR,    ADD_DIR,    JMP_DIR,    JSR_DIR,    LDX_DIR,    STX_DIR,
/*C*/    SUB_EXT,    CMP_EXT,    SBC_EXT,    CPX_EXT,    AND_EXT,    BIT_EXT,    LDA_EXT,    STA_EXT,    EOR_EXT,    ADC_EXT,    ORA_EXT,    ADD_EXT,    JMP_EXT,    JSR_EXT,    LDX_EXT,    STX_EXT,
/*D*/    SUB_IX2,    CMP_IX2,    SBC_IX2,    CPX_IX2,    AND_IX2,    BIT_IX2,    LDA_IX2,    STA_IX2,    EOR_IX2,    ADC_IX2,    ORA_IX2,    ADD_IX2,    JMP_IX2,    JSR_IX2,    LDX_IX2,    STX_IX2, 
/*E*/    SUB_IX1,    CMP_IX1,    SBC_IX1,    CPX_IX1,    AND_IX1,    BIT_IX1,    LDA_IX1,    STA_IX1,    EOR_IX1,    ADC_IX1,    ORA_IX1,    ADD_IX1,    JMP_IX1,    JSR_IX1,    LDX_IX1,    STX_IX1,
/*F*/    SUB_IX,     CMP_IX,     SBC_IX,     CPX_IX,     AND_IX,     BIT_IX,     LDA_IX,     STA_IX,     EOR_IX,     ADC_IX,     ORA_IX,     ADD_IX,     JMP_IX,     JSR_IX,     LDX_IX,     STX_IX
};

// Bit-Manipulation
// 0: DIR
void BRSET0_DIR(void){}
void BRCLR0_DIR(void){}
void BRSET1_DIR(void){}
void BRCLR1_DIR(void){}
void BRSET2_DIR(void){}
void BRCLR2_DIR(void){}
void BRSET3_DIR(void){}
void BRCLR3_DIR(void){}
void BRSET4_DIR(void){}
void BRCLR4_DIR(void){}
void BRSET5_DIR(void){}
void BRCLR5_DIR(void){}
void BRSET6_DIR(void){}
void BRCLR6_DIR(void){}
void BRSET7_DIR(void){}
void BRCLR7_DIR(void){}

// 1:DIR
void BSET0_DIR(void){}
void BCLR0_DIR(void){}
void BSET1_DIR(void){}
void BCLR1_DIR(void){}
void BSET2_DIR(void){}
void BCLR2_DIR(void){}
void BSET3_DIR(void){}
void BCLR3_DIR(void){}
void BSET4_DIR(void){}
void BCLR4_DIR(void){}
void BSET5_DIR(void){}
void BCLR5_DIR(void){}
void BSET6_DIR(void){}
void BCLR6_DIR(void){}
void BSET7_DIR(void){}
void BCLR7_DIR(void){}

// Branch
// 2
void  BRA_REL(void){}
void  BRN_REL(void){}
void  BHI_REL(void){}
void  BLS_REL(void){}
void  BCC_REL(void){}
void  BCS_REL(void){}
void  BNE_REL(void){}
void BEQ_REL(void)
{
    if (registers.ccr.Z == 1)
    {
        char_t rel = memory.virtual[registers.PC + 1];
        registers.PC += 0x0002 + rel;
    }
    else
    {
        registers.PC += 2;
    }
    display_registers("BEQ_REL");
}
void BHCC_REL(void){}
void BHCS_REL(void){}
void  BPL_REL(void){}
void  BMI_REL(void){}
void  BMC_REL(void){}
void  BMS_REL(void){}
void  BIL_REL(void){}
void  BIH_REL(void){}

// Read-Modify-Write
// 3
void  NEG_DIR(void){}
void CBEQ_DIR(void){}
/*      NULL     */
void  COM_DIR(void){}
void  LSR_DIR(void){}
void STHX_DIR(void){}
void  ROR_DIR(void){}
void  ASR_DIR(void){}
void  LSL_DIR(void){}
void  ROL_DIR(void){}
void  DEC_DIR(void){}
void DBNZ_DIR(void){}
void  INC_DIR(void){}
void  TST_DIR(void){}
/*      NULL     */
void  CLR_DIR(void){}

/* 4
*
*
*
*
*
*/
void  NEGA_INH(void){}
void CBEQA_IMM(void){}
void   MUL_INH(void){}
void  COMA_INH(void){}
void  LSRA_INH(void){}
void LTHX_IMM(void)
{
    registers.IR = BSWAP_16(&memory.virtual[registers.PC + 1]);
    registers.PC += 3;
    registers.ccr.V = 0;
    registers.ccr.N = (int16_t)registers.IR < 0;
    registers.ccr.Z = registers.IR == 0;
    display_registers("LTHX_IMM");
}
void  RORA_INH(void){}
void  ASRA_INH(void){}
void  LSLA_INH(void){}
void  ROLA_INH(void){}
void  DECA_INH(void){}
void DBNZA_INH(void){}
void  INCA_INH(void){}
void  TSTA_INH(void){}
void   MOA_DD (void){}
void  CLRA_INH(void){}

// 5
void  NEGX_INH (void){}
void CBEQX_IMM (void){}
void   DIV_INH (void){}
void  COMX_INH (void){}
void  LSRX_INH (void){}
void  LTHX_DIR (void){}
void  RORX_INH (void){}
void  ASRX_INH (void){}
void  LSLX_INH (void){}
void  ROLX_INH (void){}
void  DECX_INH (void){}
void DBNZX_INH (void){}
void  INCX_INH (void){}
void  TSTX_INH (void){}
void   MOX_DIX_(void){}
void  CLRX_INH (void){}

// 6 IX1
void  NEG_IX1 (void){}
void CBEQ_IX1_(void){}
void  NSA_INH (void){}
void  COM_IX1 (void){}
void  LSR_IX1 (void){}
void CPHX_IMM (void){}
void  ROR_IX1 (void){}
void  ASR_IX1 (void){}
void  LSL_IX1 (void){}
void  ROL_IX1 (void){}
void  DEC_IX1 (void){}
void DBNZ_IX1 (void){}
void  INC_IX1 (void){}
void  TST_IX1 (void){}
void  MOV_IMD (void){}
void  CLR_IX1 (void){}

// 9E6 SP1

// 7 IX
void  NEG_IX  (void){}
void CBEQ_IX_ (void){}
void  DAA_INN (void){}
void  COM_IX  (void){}
void  LSR_IX  (void){}
void CPHX_DIR (void){}
void  ROR_IX  (void){}
void  ASR_IX  (void){}
void  LSL_IX  (void){}
void  ROL_IX  (void){}
void  DEC_IX  (void){}
void DBNZ_IX  (void){}
void  INC_IX  (void){}
void  TST_IX  (void){}
void  MOV_IX_D(void){}
void  CLR_IX  (void){}

// 8 INH
void  RTI_INH(void){}
void  RTS_IMM(void){}
/*      NULL      */
void  SWI_INH(void){}
void  TAP_INH(void){}
void  TPA_INH(void){}
void PULA_INH(void){}
void PSHA_INH(void){}
void PULX_INH(void){}
void PSHX_INH(void){}
void PULH_INH(void){}
void PSHH_INH(void){}
void CLRH_INH(void){}
/*      NULL      */
void STOP_INH(void){}
void WAIT_INH(void){}

// 9 INH
void BEG_REL(void){}
void BLT_REL(void){}
void BGT_REL(void){}
void BLE_REL(void){}
void TXS_INH(void)
{
    registers.PC += 1;
    registers.SP = registers.IR - 1;
    display_registers("TXS_INH");
}
void TSX_INH(void){}
/*      NULL      */
void TAX_INH(void){}
void CLC_INH(void){}
void SEC_INH(void){}
void CLI_INH(void)
{
    registers.PC += 1;
    registers.ccr.I = 0;
    display_registers("CLI_INH");
}
void SEI_INH(void){}
void RSP_INH(void){}
void NOP_INH(void){}
/*      STAR      */
void TXA_INH(void){}

// A IMM
void SUB_IMM(void){}
void CMP_IMM(void){}
void SBC_IMM(void){}
void CPX_IMM(void){}
void AND_IMM(void)
{
    registers.A &= memory.virtual[registers.PC + 1];
    registers.PC += 2;
    registers.ccr.V = 0;
    registers.ccr.N = (char_t)registers.A < 0;
    registers.ccr.Z = registers.A == 0;
    display_registers("ADD_IMM");
}
void BIT_IMM(void){}
void LDA_IMM(void){}
void AIS_IMM(void){}
void EOR_IMM(void){}
void ADC_IMM(void){}
void ORA_IMM(void){}
void ADD_IMM(void){}

/*      NULL      */
void BSR_REL(void){}
void LDX_IMM(void){}
void AIX_IMM(void){}

// B: DIR
void SUB_DIR(void){}
void CMP_DIR(void){}
void SBC_DIR(void){}
void CPX_DIR(void){}
void AND_DIR(void){}
void BIT_DIR(void){}
void LDA_DIR(void){}
void STA_DIR(void){}
void EOR_DIR(void){}
void ADC_DIR(void){}
void ORA_DIR(void){}
void ADD_DIR(void){}
void JMP_DIR(void){}
void JSR_DIR(void){}
void LDX_DIR(void){}
void STX_DIR(void){}

// C: EXT
void SUB_EXT(void){}
void CMP_EXT(void){}
void SBC_EXT(void){}
void CPX_EXT(void){}
void AND_EXT(void){}
void BIT_EXT(void){}
void LDA_EXT(void)
{
    uint16_t ext = BSWAP_16(&memory.virtual[registers.PC + 1]);
    registers.A = memory.virtual[ext];
    registers.PC += 3;
    registers.ccr.V = 0;
    registers.ccr.N = (char_t)registers.A < 0;
    registers.ccr.Z = registers.A == 0;
    display_registers("LDA_EXT");
}
void STA_EXT(void)
{
    uint16_t ext = BSWAP_16(&memory.virtual[registers.PC + 1]);
    memory.virtual[ext] = registers.A;
    registers.PC += 3;
    registers.ccr.V = 0;
    registers.ccr.N = (char_t)registers.A < 0;
    registers.ccr.Z = registers.A == 0;
    display_registers("STA_EXT");
}
void EOR_EXT(void){}
void ADC_EXT(void){}
void ORA_EXT(void){}
void ADD_EXT(void){}
void JMP_EXT(void)
{
    uint16_t ext = BSWAP_16(&memory.virtual[registers.PC + 1]);
    registers.PC = ext;
    display_registers("JMP_EXT");
}
void JSR_EXT(void){}
void LDX_EXT(void){}
void STX_EXT(void){}

// D: IX2
void SUB_IX2(void){}
void CMP_IX2(void){}
void SBC_IX2(void){}
void CPX_IX2(void){}
void AND_IX2(void){}
void BIT_IX2(void){}
void LDA_IX2(void){}
void STA_IX2(void){}
void EOR_IX2(void){}
void ADC_IX2(void){}
void ORA_IX2(void){}
void ADD_IX2(void){}
void JMP_IX2(void){}
void JSR_IX2(void){}
void LDX_IX2(void){}
void STX_IX2(void){}

// 9ED: SP2

// E: IX1
void SUB_IX1(void){}
void CMP_IX1(void){}
void SBC_IX1(void){}
void CPX_IX1(void){}
void AND_IX1(void){}
void BIT_IX1(void){}
void LDA_IX1(void){}
void STA_IX1(void){}
void EOR_IX1(void){}
void ADC_IX1(void){}
void ORA_IX1(void){}
void ADD_IX1(void){}
void JMP_IX1(void){}
void JSR_IX1(void){}
void LDX_IX1(void){}
void STX_IX1(void){}

// 9EE: SP1

// F: IX
void SUB_IX(void){}
void CMP_IX(void){}
void SBC_IX(void){}
void CPX_IX(void){}
void AND_IX(void){}
void BIT_IX(void){}
void LDA_IX(void){}
void STA_IX(void){}
void EOR_IX(void){}
void ADC_IX(void){}
void ORA_IX(void){}
void ADD_IX(void){}
void JMP_IX(void){}
void JSR_IX(void){}
void LDX_IX(void){}
void STX_IX(void){}









