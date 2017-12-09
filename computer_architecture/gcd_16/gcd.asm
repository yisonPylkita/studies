LEFT_OPERAND_BASE    equ 2000h
RIGHT_OPERAND_BASE   equ 3000h
RESULT_BASE          equ 4000h

    ORG 0000H
    LJMP START

DIV16_16:
    CLR C
    MOV R4, #00H
    MOV R5, #00H
    MOV B, #00H

DIV1:
    INC B
    MOV A, R2
    RLC A
    MOV R2, A
    MOV A, R3
    RLC A
    MOV R3, A
    JNC DIV1

DIV2:
    MOV A, R3
    RRC A
    MOV R3, A
    MOV A, R2
    RRC A
    MOV R2, A
    CLR C
    MOV 07H, R1
    MOV 06H, R0
    MOV A, R0
    SUBB A, R2
    MOV R0, A
    MOV A, R1
    SUBB A, R3
    MOV R1, A
    JNC DIV3
    MOV R1, 07H
    MOV R0, 06H

DIV3:
    CPL C
    MOV A, R4
    RLC A
    MOV R4, A
    MOV A, R5
    RLC A
    MOV R5, A
    DJNZ B, DIV2
    MOV R3, 05H
    MOV R2, 04H
    RET

swp:
    mov r7, a
    mov a, b
    mov b, r7
    call dummy

dummy:
    div ab
    mov a, r1
    mov r0, a
    mov r1, b
    cjne r1, #0h, gcd
    call exit

gcd:
    cjne R0, #0, gcd_1
    cjne R1, #0, gcd_1
    mov A, R2
    mov R4, A
    mov A, R3
    mov R5, A
    RET
gcd_1:
    cjne R2, #0, gcd_2
    cjne R3, #0, gcd_2
    mov A, R0
    mov R4, A
    mov A, R1
    mov R5, A
    RET
gcd_2:
    mov A, R2
    PUSH ACC
    mov A, R3
    PUSH ACC
    call DIV16_16
    mov A, R0
    mov R2, A
    mov A, R1
    mov R3, A
    POP 07
    MOV A, R7
    MOV R1, A
    POP 06
    MOV A, R6
    MOV R0, A
    jmp gcd

start:
    ; load dividend
    MOV DPTR, #LEFT_OPERAND_BASE
    MOVX A, @DPTR
    mov R0, A
    INC DPTR
    movx A, @DPTR
    mov R1, A
    ; load divisor
    mov DPTR, #RIGHT_OPERAND_BASE
    movx A, @DPTR
    mov R2, A
    INC DPTR
    movx A, @DPTR
    mov R3, A

    call gcd

exit:
    mov A, R4
    mov DPTR, #RESULT_BASE
    movx @DPTR, A
    INC DPTR
    MOV A, R5
    movx @DPTR, A

END
