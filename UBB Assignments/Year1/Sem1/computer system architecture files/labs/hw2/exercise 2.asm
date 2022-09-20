bits 32 
; problem 6

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ; a, b, c, d - byte
    a db 5
    b db 4
    c db 2
    d db 7


segment code use32 class=code
    start:
        ; (a+b)-(a+d)+(c-a)
        
        mov AH, [a]
        add AH, [b] ; AH now has a + b = 5 + 4 = 9
        
        mov BH, [a]
        add BH, [d] ; BH now has a + d = 5 + 7 = 12
        
        mov CL, [c]
        sub CL, [a] ; CL now has c - a = 2 - 5 = -3
        
        sub AH, BH ; AH now has (a+b)-(a+d) = 9 - 12 = -3
        add AH, CL ; AH now has the final result, -3 + (-3) = -6
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program