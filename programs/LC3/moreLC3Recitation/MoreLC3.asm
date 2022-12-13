; Recitation MoreLC3
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

            .ORIG x3000

            JSR mirror               ; call function
            HALT

; Parameter and return value
Param           .FILL x5634              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants
One             .FILL #1             ; the number 1       
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
mirror                           ; Mirrors bits 7:0 to 15:8
                                 ; ~20 lines of assembly code

		LD R0,Param          ; load pattern
		AND R1,R0,R0          ; your code here
		LD R2, Mask
		AND R1, R2, R1
		LD R2, One		; Soruce Mask
		LD R3, One		; Dest Mask
		LD R4, Eight
		BRp sLoop
sLoop
		BRz eLoop
		ADD R3, R3, R3
		ADD R4, R4, #-1
		BRnzp sLoop
		
eLoop
		LD R4, Eight		; Counter
mLoop
		BRnz emLoop
		AND R5, R2, R0
		BRz skipped
addBit
		ADD R1, R3, R1
skipped
		ADD R2, R2, R2
		ADD R3, R3, R3
		ADD R4, R4, #-1
		BRnzp mLoop
emLoop
		ST R1,Result         ; store result
            RET
;--------------------------------------------------------------------------
           .END
