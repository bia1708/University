bits 32 
; problem 20

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ; a, b, c, d - byte
    a db 3
    b db 1
    c db 10
    d db 4


segment code use32 class=code
    start:
        ; (a+a)-(c+b+d)
        
        mov AH, [a]
        add AH, AH ; AH now has the value of a + a = 3 + 3 = 6
        
        mov BH, [b]
        add BH, [c]
        add BH, [d] ; now BH has the value of c + b + d = 1 + 10 + 4 = 15
        
        sub AH, BH ; AH now has the final value: 6 - 15 = -9
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program