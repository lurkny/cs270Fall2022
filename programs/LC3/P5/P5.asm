; P5 Assignment
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine          (option 0)
                .FILL IntSub         ; Address of IntSub routine          (option 1)
                .FILL IntMul         ; Address of IntMul routine          (option 2)
                .FILL BinaryOr       ; Address of BinaryOr routine        (option 3)
                .FILL BinaryXOr      ; Address of BinaryXOr routine       (option 4)
                .FILL LeftShift      ; Address of LeftShift routine       (option 5)
                .FILL RightArithShift; Address of RightArithShift routine (option 6)

Main            LEA R0,Functions     ; The main routine calls one of the 
                LD  R1,Option        ; subroutines below based on the value of
                ADD R0,R0,R1         ; the Option parameter.
                LDR R0,R0,0          ;
                JSRR R0              ;
EndProg         HALT                 ;

; Parameters and return values for all functions
; Try changing the .BLKW 1 to .FILL xNNNN where N is a hexadecimal value or #NNNN
; where N is a decimal value, this can save you time by not having to set these 
; values in the simulator every time you run your code. This is the only change 
; you should make to this section.
Option          .FILL #0             ; Which function to call
Param1          .BLKW 1              ; Space to specify first parameter
Param2          .BLKW 1              ; Space to specify second parameter
Result          .BLKW 1              ; Space to store result
One             .FILL #1
counter         .BLKW 1
MAX             .FILL #16
MSB             .FILL x8000
; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.

;------------------------------------------------------------------------------
IntAdd         LD R1, PARAM1
               LD R0, PARAM2
               ADD R4, R1, R0
               ST R4, RESULT 
                                  ; Result is Param1 + Param2
                                     ; Your code goes here (~4 lines)
               RET
;------------------------------------------------------------------------------
IntSub      LD R1, PARAM1
            LD R0, PARAM2
            NOT R0, R0
            ADD R0, R0, 1
            ADD R4, R1, R0
            ST R4, RESULT                               ; Result is Param1 - Param2
                                     ; Your code goes here (~6 lines)
                RET
;------------------------------------------------------------------------------
IntMul                               ; Result is Param1 * Param2
            LD R1, PARAM1
            LD R3, PARAM1
            LD R2, PARAM2
            BRp SLOOP
            BRz bad
sLoop
            BRnz ELOOP
            ADD R4,R4,R3
            ADD R2, R2, #-1
            BRnzp SLOOP
eLoop
            ST R4, RESULT
            RET
bad
            AND R4, R4, #0
            ST R4, RESULT
            RET

                                     ; Your code goes here (~9 lines)

;------------------------------------------------------------------------------
BinaryOr
            LD R1, PARAM1
            LD R0, PARAM2
            NOT R1,R1
            NOT R0,R0
            AND R4, R1, R0
            NOT R4, R4
            ST R4, RESULT 
                             ; Result is Param1 | Param2
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
BinaryXOr
            LD R1, PARAM1            ;Demorgans law - xor is [R1 and NOT R0] or [Not R1 and R0]
            LD R0, PARAM2             ; R2 will be not R1, R3 will be NOT R2 - R
            NOT R2, R1                ; NOT R1
            NOT R3, R0                ; NOt R2
            AND R1, R1, R3            ; A AND NOT B
            AND R0, R2, R0            ; NOT A AND B
            NOT R1,R1                 ; This and line below are NOTing the values in the 2 lines above, and then we can do demorgans law to get logical OR
            NOT R0, R0
            AND R0, R0, R1
            NOT R0, R0
            ST R0, RESULT


            
            
                                     ; Your code goes here
                RET
;------------------------------------------------------------------------------
LeftShift   
            LD R1, PARAM1
            LD R0, PARAM2
xLoop
            ADD R1, R1, R1
            ADD R0, R0, #-1
            BRz EXLOOP
exLoop
            ST R1, RESULT                         ; Result is Param1 << Param2
                                     ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~7 lines)
                RET
;------------------------------------------------------------------------------
RightArithShift
                LD R1, PARAM1 ;Value
                LD R0, PARAM2 ;How many times to shift it over
                AND R4,R4,#0 ; RESULT
                LD R2, ONE ; Source Mask
                LD R3, ONE ; Destination mask

maskLoop        BRnz EMASKLOOP
                ADD R2,R2,R2
                ADD R0,R0,#-1
                BRnzp MASKLOOP
eMaskLoop
                AND R0,R0,#0 ;Buffer that stores both the bit comparison and the loop counter.
compareLoop
                AND R0, R1, R2
                BRz incrMask
                ADD R4, R3, R4

INCRMASK
                ADD R3,R3,R3
                ADD R2,R2,R2
                BRz EXTENDM
                BRp COMPARELOOP
extendM
                LD R2, MSB ;Loads R2 with the MSB
                AND R0, R2, R1 ;Checks if MSB is set
                BRz finish ;IF not, we good
                ADD R4, R3, R4 ;If it is, set it and icrement
                ADD R3,R3,R3 ;Breaking shit for somereas
                BRnp EXTENDM

finish
                ST R4, RESULT
                                      ; Result is Param1 >> Param2 with sign extension
                                     ; Your code goes here (~23 lines)
                RET
;------------------------------------------------------------------------------
                .END
