bits 32 
; problem 6

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ; a, b, c - byte
    a db 5
    b db 3
    c db 2


segment code use32 class=code
    start:
        ; (a*b)/c
        
        mov AL, [a]
        mov BL, [b]
        mul BL ; AX : a * b = 5 * 3 = 15
        
        mov BL, [c]
        div BL ; AL : 7,   AH : 1 
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program