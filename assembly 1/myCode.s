PER EQU 0x400E0E00
SODR EQU 0x400E0E30
CODR EQU 0x400E0E34
OER EQU 0x400E0E10
PDSR EQU 0x400E0E3C
ISR EQU 0x400E0E4C
		
		AREA mycode, CODE, READONLY
		EXPORT __main
		ENTRY

__main
	MOV R4, #2_11100
	
	LDR R5,=PER
	STR R4, [R5]
	
	LDR R5,=OER
	STR R4, [R5]

wait
	LDR R1, =ISR
	LDR R2, [R1]
	CMP R2, #2_1
	BEQ loop
	B wait


stop
	MOV R4, #2_11100
	
	LDR R5,=CODR
	STR R4, [R5]
	
	B wait

loop

	LDR r1, =ISR
	LDR r2, [r1]
	CMP r2, #2_10
	BEQ stop
	
	; turn on 1,2,3
	MOV r4, #2_11100
	
	LDR r5,=SODR
	STR r4, [r5]
	
	BL delay
	
	LDR r1, =ISR
	LDR r2, [r1]
	CMP r2, #2_10
	BEQ stop
	
	; trun off 1
	MOV r4, #2_100
	
	LDR r5,=CODR
	STR r4, [r5]
	
	BL delay
	
	LDR r1, =ISR
	LDR r2, [r1]
	CMP r2, #2_10
	BEQ stop
	
	; turn on 1
	MOV r4, #2_100
	
	LDR r5,=SODR
	STR r4, [r5]
	
	; turn off 2
	MOV r4, #2_1000
	
	LDR r5,=CODR
	STR r4, [r5]
	
	BL delay
	
	LDR r1, =ISR
	LDR r2, [r1]
	CMP r2, #2_10
	BEQ stop
	
	; turn off 1, 3
	MOV r4, #2_10100
	
	LDR r5,=CODR
	STR r4, [r5]
	
	BL delay
	
	LDR r1, =ISR
	LDR r2, [r1]
	CMP r2, #2_10
	BEQ stop
	
	; turn on 1, 2
	MOV r4, #2_1100
	
	LDR r5,=SODR
	STR r4, [r5]
	
	BL delay
	
	LDR r1, =ISR
	LDR r2, [r1]
	CMP r2, #2_10
	BEQ stop
	
	; turn off 1
	MOV r4, #2_100
	
	LDR r5,=CODR
	STR r4, [r5]
	
	BL delay
	
	LDR r1, =ISR
	LDR r2, [r1]
	CMP r2, #2_10
	BEQ stop
	
	; turn off 2
	MOV r4, #2_1000
	
	LDR r5,=CODR
	STR r4, [r5]
	
	BL loop

delay
	MOV r4, #0
	LDR r5, =0x00C0000

loop_delay
	ADD r4,r4,#1
	
	CMP r4,r5
	BNE loop_delay
	
	BX lr
	
here B here
	END