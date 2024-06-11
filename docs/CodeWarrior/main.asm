;*******************************************************************
;* This stationery serves as the framework for a user application. *
;* For a more comprehensive program that demonstrates the more     *
;* advanced functionality of this processor, please see the        *
;* demonstration applications, located in the examples             *
;* subdirectory of the "Freescale CodeWarrior for HC08" program    *
;* directory.                                                      *
;*******************************************************************

; Include derivative-specific definitions
            INCLUDE 'derivative.inc'
            

; export symbols
            XDEF _Startup, main
            ; we export both '_Startup' and 'main' as symbols. Either can
            ; be referenced in the linker .prm file or from C/C++ later on
            
            
            
            XREF __SEG_END_SSTACK   ; symbol defined by the linker for the end of the stack


; variable/data section
MY_ZEROPAGE: SECTION  SHORT         ; Insert here your data definition

DATA_PORT:			EQU	$0100		; mem-mapped address where data comes from
STATUS_PORT:		EQU	$0101		; mem-mapped address where device tells us if there is data ready
MSB:				EQU	%10000000	; most significant bit as a bit-mask
STORE_PLACE:		EQU	$1000		; where to place data that is read

; code section
;
; in this program, the loop continually reads the data from the STATUS PORT and when the most significant bit (MSB)
; is set (turned on / high value) - the program will read the data from the DATA PORT and move it (store it) into
; a STORE LOCATION in memory ... and then the program continues to run through the loop (over and over)
MyCode:     SECTION
main:
_Startup:
            LDHX   #__SEG_END_SSTACK ; initialize the stack pointer
            TXS
			CLI			; enable interrupts

loop:
			LDA	STATUS_PORT			; read from the device’s status register
			AND	#MSB				; and the accumulator to extract the high-order bit
			BEQ	loop				; if not, try again …
			LDA	DATA_PORT			; read the data and …
			STA	STORE_PLACE			; … store it where needed
			JMP	loop				; wait for more data to be ready

