bits 32 
; problem 20

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ; a, b, c - word
    a dw 5
    b dw 6
    c dw 100


segment code use32 class=code
    start:
        ; b-(b+c)+a
        
        mov AX, [b] ; AX has the value of b = 6
        
        mov BX, [b]
        add BX, [c] ; BX has the value of b + c = 6 + 100 = 106
        
        sub AX, BX ; now AX has the value of b - (b + c) = 6 - 106 = -100
        add AX, [a] ; now AX has the final value of -100 + 5 = -95
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program