; Description: LC3 Tower of Hanoi Implementation 

;Author: Brody Larson
;------------------------------------------------------------------------------
; BEGIN_RESERVED_SECTION: do not change ANYTHING in reserved the section!
; The ONLY exception to this is that you MAY change the .FILL value for
; any memory location marked for modification. This makes debugging easier
; as you need only change your code and re-assemble. Your test value(s) will
; already be set.

                .ORIG x3000
                BR main

option          .FILL 0  ; YOU_MAY_MODIFY_VAL ; 0 => Hanoi, non-0 => printMove
numDisks        .FILL 3  ; YOU_MAY_MODIFY_VAL
startTower      .FILL 1  ; YOU_MAY_MODIFY_VAL
endTower        .FILL 3  ; YOU_MAY_MODIFY_VAL

                ; misc strings for printing
digits          .STRINGZ "0123456789"
msg1            .STRINGZ "Move disk ";
msg2            .STRINGz " from tower ";
msg3            .STRINGz " to tower ";
endMsg          .STRINGz "\nThe world has ended\n"

stack           .FILL 0x4000

main            LD   R6,stack           ; initialize stack
                LD   R5,stack           ; initialize frame pointer

                LD   R0,endTower        ; both function have three parameters
                PUSH R0                 ; so put them on stack before JSR
                LD   R0,startTower
                PUSH R0
                LD   R0,numDisks
                PUSH R0

                LD   R0,option          ; get option to test
                BRZ  testHanoi

testPrintMove   JSR  printMove
                BR   endTest

testHanoi       JSR  hanoi

endTest         ADD  R6,R6,#3           ; clean up parameters
                LEA  R0,endMsg
                PUTS
theEnd          HALT                    ; check R5, R6 here, should be initial 'stack' value

; END_RESERVED_SECTION

;----  S t u d e n t   c o d e   g o e s   h e r e  --------------------------

; void printMove(disk, from, to)
ENDLINE .FILL x000A

; disk @ FP   ; from at FP   ; to @ FP   ; complete line


printMove
		PUSH R7
		PUSH R5
		ADD R5, R6, #-1
diskPrint
		LEA R0, msg1
		PUTS
		LDR R1, R5, #3 ;Data of first paramater, others are above it
		LEA R0, digits
		ADD R0, R0, R1
		LDR R0, R0, #0
		OUT	
fromPrint
		LEA R0, msg2
		PUTS		
		LDR R1, R5,#4
		LEA R0, digits
		ADD R0, R0, R1
		LDR R0, R0, #0
		OUT				
toPrint
		LEA R0, msg3
		PUTS
		LDR R1, R5, #5
		LEA R0, digits
		ADD R0, R0, R1
		LDR R0, R0, #0
		OUT
		LD R0, ENDLINE
		OUT
exit
		POP R5
		POP R7

                RET                     ; return to caller

;------------------------------------------------------------------------------
 
; void hanoi(numDisks, fromDisk, toDisk)

; numDisks @ R5   ; fromTower @ R5   ; toTower @ R5   ; auxTower @ R5   ; complete line

negONE	.FILL #-1
;NOTE: toTower is +5 from R6 and R5, from is -1 from toTower, and numDisks is +2 from toTower

hanoi
	PUSH R7
	PUSH R5
	ADD R6,R6, #-1 ;Space for local
	ADD R5, R6, #0 ;Sets new FP

baseCASE
	LDR R1, R5, #3 ;R1 has numDisks
	LD R2, negONE  ;R1 has negative one, for comparison later
	ADD R2, R2, R1 ;Testing if numdisks == 1
	BRnp baseCASEFAIL
baseCASEHIT ;Preparing for a call to PrintMove
	.ZERO R0    ;1st push is to, 2nd from, 3rd numdisks
	LDR R0, R5, #5
	PUSH R0
	LDR R0, R5, #4
	PUSH R0
	LDR R0, R5, #3
	PUSH R0
	JSR printMove
	ADD R6, R6, #3
	BRnzp cleanUP
baseCASEFAIL
	.ZERO R0
	.ZERO R1
	LDR R2, R5, #5 ;to
	LDR R3, R5, #4 ;from
	ADD R2, R2, R3 ;To + From
	NOT R2, R2
	ADD R2, R2, #1 ;2's comp
	ADD R1, R2, #6
	STR R1, R5, #0 ; Storing auxTower
;Begin setup for function calls
;hanoi(numDisks - 1, fromTower, auxTower)
functions
	LDR R0, R5, #0 ;auxtower
	PUSH R0
	LDR R1, R5, #4
	PUSH R1 ; fromTower
	LDR R0, R5, #3
	ADD R0, R0, #-1
	PUSH R0 ;numDisks - 1
	JSR hanoi
	ADD  R6,R6,#3
;printMove(numDisks, fromTower, toTower)
	LDR R0, R5, #5
	PUSH R0
	LDR R0, R5,#4
	PUSH R0
	LDR R0, R5,#3
	PUSH R0
	JSR printMove
	ADD  R6,R6,#3
;hanoi(numDisks - 1, auxTower, toTower)
	LDR R0, R5, #5
	PUSH R0
	LDR R0, R5, #0
	PUSH R0
	LDR R0, R5, #3
	ADD R0, R0, #-1
	PUSH R0
	JSR hanoi
	ADD R6, R6, #3
cleanUP
	ADD R6,R6, #1 ;Remove locals
	POP R5
	POP R7
        RET                     ; return to caller
;------------------------------------------------------------------------------
                .END
