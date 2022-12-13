; Recitation MoreLC3
; Author: Brody Larson
; Date:   10/5/22
; Email: larsonbm@colostate.edu
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

            .ORIG x3000

            JSR mirror               ; call function
            HALT

; Parameter and return value
Param           .BLKW 1              ; space to specify parameter
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
            LD R1, PARAM         ; Copys R0 into R1 - The result
            LD R2, MASK          ; Loads bitmask into R2
            AND R1, R1, R2       ; AND the mask with the result to clear bits
            LD R2, ONE
            LD R3, ONE
            LD R4, EIGHT      
            ST R1,Result         ; store result
            RET
;--------------------------------------------------------------------------
           .END
