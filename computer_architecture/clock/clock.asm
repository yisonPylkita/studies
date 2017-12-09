HOURS EQU 07Ch 
MINUTES EQU 07Dh 
SECONDS EQU 07Eh 
TICKS EQU 07Fh

HOURS_MEM EQU 2002h 
MINUTES_MEM EQU 2001h 
SECONDS_MEM EQU 2000h

;CRYSTAL EQU 11059200 ;The crystal speed 
TMRCYCLE EQU 12 ;The number of crystal cycles per timer increment 
;TMR_SEC EQU 921600 ;The # of timer increments per second
F20TH_OF_SECOND EQU 46080
RESET_VALUE EQU 19456

    ORG 0000h
    LJMP MAIN

ORG 001Bh ;This is where Timer 1 Interrupt Routine starts 
    PUSH ACC ;We'll use the accumulator, so we need to protect it 
    PUSH PSW ;We may modify PSW flags, so we need to protect it 
    CLR TR1 ;Turn off timer 1 as we reset the value 
    MOV TH1,#HIGH RESET_VALUE ;Set the high byte of the reset value 
    MOV TL1,#LOW RESET_VALUE ;Set the low byte of the reset value 
    SETB TR1 ;Restart timer 1 now that it has been initialized

    DJNZ TICKS,EXIT_RTC ;Decrement TICKS, if not yet zero we exit immediately
    MOV TICKS,#20 ;Reset the ticks variable 

    INC SECONDS ;Increment the second varaiable
    MOV A,SECONDS ;Move the seconds variable into the accumulator 
    MOV DPTR,#SECONDS_MEM
    MOVX @DPTR,A
    CJNE A,#60,EXIT_RTC ;If we haven't counted 60 seconds, we're done.
    MOV SECONDS,#0 ;Reset the seconds varaible 
    MOV A,SECONDS
    MOVX @DPTR,A

    INC MINUTES ;Increment the number of minutes 
    MOV A,MINUTES ;Move the minutes variable into the accumulator 
    MOV DPTR,#MINUTES_MEM
    MOVX @DPTR,A
    CJNE A,#60,EXIT_RTC ;If we haven't counted 60 minutes, we're done 
    MOV MINUTES,#0 ;Reset the minutes variable 
    MOV A,MINUTES
    MOVX @DPTR,A

    INC HOURS ;Increment the hour variable
    MOV A,HOURS ;Move the hours variable into the accumulator 
    MOV DPTR,#HOURS_MEM
    MOVX @DPTR,A
    CJNE A,#24,EXIT_RTC ;If we haven't counted 24 hours, we're done 
    MOV HOURS,#0 ;Reset the hours variable 
    MOV A,HOURS
    MOVX @DPTR,A

EXIT_RTC: 
    POP PSW ;Restore the PSW register 
    POP ACC ;Restore the accumulator 
    RETI ;Exit the interrupt routine

MAIN: 
    MOV TH1,#HIGH RESET_VALUE ;Initialize timer high-byte 
    MOV TL1,#LOW RESET_VALUE ;Initialize timer low-byte 
    MOV TMOD,#10h ;Set timer 1 to 16-bit mode 
    SETB TR1 ;Start timer 1 running 
    MOV HOURS,#00 ;Initialize to 0 hours 
    MOV MINUTES,#00 ;Initialize to 0 minutes 
    MOV SECONDS,#00 ;Initialize to 0 seconds 
    MOV TICKS,#20 ;Initialize countdown tick counter to 20 
    SETB EA ;Initialize interrupts 
    SETB ET1 ;Initialize Timer 1 interrupt

LOOP:
    LJMP LOOP

END
