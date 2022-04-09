bits 32 
; problem 6

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ;a, b, c - byte; d - word
    
    a db 5 
    b db 7
    c db 10
    d dw 130

segment code use32 class=code
    start:
        ; [2*(a+b)-5*c]*(d-3)
        
        mov AL, [a]
        add AL, [b] ; AL: a + b = 5 + 7 = 12
        
        mov BL, 2
        mul BL ; AX: 2 * (a + b) = 2 * 12 = 24
        
        mov CX, AX ; CX : 24
        
        mov AL, [c]
        mov BL, 5
        mul BL ; AX : 5 * c = 5 * 10 = 50
        
        sub CX, AX ; CX : 24 - 50 = -26
        
        mov AX, [d]
        sub AX, 3 ; AX = 130 - 3 = 127
        mul CX ; AX : 127 * (-26) = -3302
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program