#pragma once

extern void(*opcode_map[256])(void);

// Bit-Manipulation
// 0
void BRSET0_DIR(void);
void BRCLR0_DIR(void);
void BRSET1_DIR(void);
void BRCLR1_DIR(void);
void BRSET2_DIR(void);
void BRCLR2_DIR(void);
void BRSET3_DIR(void);
void BRCLR3_DIR(void);
void BRSET4_DIR(void);
void BRCLR4_DIR(void);
void BRSET5_DIR(void);
void BRCLR5_DIR(void);
void BRSET6_DIR(void);
void BRCLR6_DIR(void);
void BRSET7_DIR(void);
void BRCLR7_DIR(void);
// 1
void BSET0_DIR(void);
void BCLR0_DIR(void);
void BSET1_DIR(void);
void BCLR1_DIR(void);
void BSET2_DIR(void);
void BCLR2_DIR(void);
void BSET3_DIR(void);
void BCLR3_DIR(void);
void BSET4_DIR(void);
void BCLR4_DIR(void);
void BSET5_DIR(void);
void BCLR5_DIR(void);
void BSET6_DIR(void);
void BCLR6_DIR(void);
void BSET7_DIR(void);
void BCLR7_DIR(void);

// Branch
// 2
void  BRA_REL(void);
void  BRN_REL(void);
void  BHI_REL(void);
void  BLS_REL(void);
void  BCC_REL(void);
void  BCS_REL(void);
void  BNE_REL(void);
void  BEQ_REL(void);
void BHCC_REL(void);
void BHCS_REL(void);
void  BPL_REL(void);
void  BMI_REL(void);
void  BMC_REL(void);
void  BMS_REL(void);
void  BIL_REL(void);
void  BIH_REL(void);

// Read-Modify-Write
// 3
void  NEG_DIR(void);
void CBEQ_DIR(void);
/*      NULL      */
void  COM_DIR(void);
void  LSR_DIR(void);
void STHX_DIR(void);
void  ROR_DIR(void);
void  ASR_DIR(void);
void  LSL_DIR(void);
void  ROL_DIR(void);
void  DEC_DIR(void);
void DBNZ_DIR(void);
void  INC_DIR(void);
void  TST_DIR(void);
/*      NULL      */
void  CLR_DIR(void);

// 4
void  NEGA_INH(void);
void CBEQA_IMM(void);
void   MUL_INH(void);
void  COMA_INH(void);
void  LSRA_INH(void);
void  LTHX_IMM(void);
void  RORA_INH(void);
void  ASRA_INH(void);
void  LSLA_INH(void);
void  ROLA_INH(void);
void  DECA_INH(void);
void DBNZA_INH(void);
void  INCA_INH(void);
void  TSTA_INH(void);
void   MOA_DD (void);
void  CLRA_INH(void);

// 5
void  NEGX_INH (void);
void CBEQX_IMM (void);
void   DIV_INH (void);
void  COMX_INH (void);
void  LSRX_INH (void);
void  LTHX_DIR (void);
void  RORX_INH (void);
void  ASRX_INH (void);
void  LSLX_INH (void);
void  ROLX_INH (void);
void  DECX_INH (void);
void DBNZX_INH (void);
void  INCX_INH (void);
void  TSTX_INH (void);
void   MOX_DIX_(void);
void  CLRX_INH (void);

// 6 IX1
void  NEG_IX1 (void);
void CBEQ_IX1_(void);
void  NSA_INH (void);
void  COM_IX1 (void);
void  LSR_IX1 (void);
void CPHX_IMM (void);
void  ROR_IX1 (void);
void  ASR_IX1 (void);
void  LSL_IX1 (void);
void  ROL_IX1 (void);
void  DEC_IX1 (void);
void DBNZ_IX1 (void);
void  INC_IX1 (void);
void  TST_IX1 (void);
void  MOV_IMD (void);
void  CLR_IX1 (void);

// 9E6 SP1

// 7 IX
void  NEG_IX  (void);
void CBEQ_IX_ (void);
void  DAA_INN (void);
void  COM_IX  (void);
void  LSR_IX  (void);
void CPHX_DIR (void);
void  ROR_IX  (void);
void  ASR_IX  (void);
void  LSL_IX  (void);
void  ROL_IX  (void);
void  DEC_IX  (void);
void DBNZ_IX  (void);
void  INC_IX  (void);
void  TST_IX  (void);
void  MOV_IX_D(void);
void  CLR_IX  (void);

// 8 INH
void  RTI_INH(void);
void  RTS_INH(void);
/*      NULL      */
void  SWI_INH(void);
void  TAP_INH(void);
void  TPA_INH(void);
void PULA_INH(void);
void PSHA_INH(void);
void PULX_INH(void);
void PSHX_INH(void);
void PULH_INH(void);
void PSHH_INH(void);
void CLRH_INH(void);
/*      NULL      */
void STOP_INH(void);
void WAIT_INH(void);

// 9 INH
void BEG_REL(void);
void BLT_REL(void);
void BGT_REL(void);
void BLE_REL(void);
void TXS_INH(void);
void TSX_INH(void);
/*      NULL      */
void TAX_INH(void);
void CLC_INH(void);
void SEC_INH(void);
void CLI_INH(void);
void SEI_INH(void);
void RSP_INH(void);
void NOP_INH(void);
/*      STAR      */
void TXA_INH(void);

// Register/Memory
// A IMM
void SUB_IMM(void);
void CMP_IMM(void);
void SBC_IMM(void);
void CPX_IMM(void);
void AND_IMM(void);
void BIT_IMM(void);
void LDA_IMM(void);
void AIS_IMM(void);
void EOR_IMM(void);
void ADC_IMM(void);
void ORA_IMM(void);
void ADD_IMM(void);
/*      NULL      */
void BSR_REL(void);
void LDX_IMM(void);
void AIX_IMM(void);

// B: DIR
void SUB_DIR(void);
void CMP_DIR(void);
void SBC_DIR(void);
void CPX_DIR(void);
void AND_DIR(void);
void BIT_DIR(void);
void LDA_DIR(void);
void STA_DIR(void);
void EOR_DIR(void);
void ADC_DIR(void);
void ORA_DIR(void);
void ADD_DIR(void);
void JMP_DIR(void);
void JSR_DIR(void);
void LDX_DIR(void);
void STX_DIR(void);

// C: EXT
void SUB_EXT(void);
void CMP_EXT(void);
void SBC_EXT(void);
void CPX_EXT(void);
void AND_EXT(void);
void BIT_EXT(void);
void LDA_EXT(void);
void STA_EXT(void);
void EOR_EXT(void);
void ADC_EXT(void);
void ORA_EXT(void);
void ADD_EXT(void);
void JMP_EXT(void);
void JSR_EXT(void);
void LDX_EXT(void);
void STX_EXT(void);

// D: IX2
void SUB_IX2(void);
void CMP_IX2(void);
void SBC_IX2(void);
void CPX_IX2(void);
void AND_IX2(void);
void BIT_IX2(void);
void LDA_IX2(void);
void STA_IX2(void);
void EOR_IX2(void);
void ADC_IX2(void);
void ORA_IX2(void);
void ADD_IX2(void);
void JMP_IX2(void);
void JSR_IX2(void);
void LDX_IX2(void);
void STX_IX2(void);

// 9ED: SP2

// E: IX1
void SUB_IX1(void);
void CMP_IX1(void);
void SBC_IX1(void);
void CPX_IX1(void);
void AND_IX1(void);
void BIT_IX1(void);
void LDA_IX1(void);
void STA_IX1(void);
void EOR_IX1(void);
void ADC_IX1(void);
void ORA_IX1(void);
void ADD_IX1(void);
void JMP_IX1(void);
void JSR_IX1(void);
void LDX_IX1(void);
void STX_IX1(void);

// 9EE: SP1

// F: IX
void SUB_IX(void);
void CMP_IX(void);
void SBC_IX(void);
void CPX_IX(void);
void AND_IX(void);
void BIT_IX(void);
void LDA_IX(void);
void STA_IX(void);
void EOR_IX(void);
void ADC_IX(void);
void ORA_IX(void);
void ADD_IX(void);
void JMP_IX(void);
void JSR_IX(void);
void LDX_IX(void);
void STX_IX(void);
