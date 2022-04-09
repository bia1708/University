bits 32 
; problem 6 

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ; a, b, c, d - word
    a dw 8
    b dw 20
    c dw 13
    d dw 15


segment code use32 class=code
    start:
        ; c-(d+a)+(b+c)
        
        mov AX, [c] ; AX now has the value of c = 13
        
        mov BX, [d]
        add BX, [a] ; BX now has the value of d + a = 15 + 8 = 23
        
        mov CX, [b]
        add CX, [c] ; CX now has the value of b + c = 20 + 13 = 33
        
        sub AX, BX ; AX now has the value 13 - 23 = -10
        add AX, CX ; AX now has the final value: -10 + 33 = 23
        
        ;div BL
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program