    ;consts
    LEFT_OPERAND_BASE equ 2000h
    RIGHT_OPERAND_BASE equ 3000h
    RESULT_BASE equ 4000h

    ; setup
    mov a, 0
    
    ; add first byte
    mov dptr, #LEFT_OPERAND_BASE
    movx a, @dptr
    mov r0, a
    mov dptr, #RIGHT_OPERAND_BASE
    movx a, @dptr
    addc a, r0
    mov dptr, #RESULT_BASE
    movx @dptr, a

    ; add second byte
    mov dptr, #LEFT_OPERAND_BASE + 1
    movx a, @dptr
    mov r0, a
    mov dptr, #RIGHT_OPERAND_BASE + 1
    movx a, @dptr
    addc a, r0
    mov dptr, #RESULT_BASE + 1
    movx @dptr, a

    ; add third byte
    mov dptr, #LEFT_OPERAND_BASE + 2
    movx a, @dptr
    mov r0, a
    mov dptr, #RIGHT_OPERAND_BASE + 2
    movx a, @dptr
    addc a, r0
    mov dptr, #RESULT_BASE + 2
    movx @dptr, a

    ; add fourth byte
    mov dptr, #LEFT_OPERAND_BASE + 3
    movx a, @dptr
    mov r0, a
    mov dptr, #RIGHT_OPERAND_BASE + 3
    movx a, @dptr
    addc a, r0
    mov dptr, #RESULT_BASE + 3
    movx @dptr, a
END
