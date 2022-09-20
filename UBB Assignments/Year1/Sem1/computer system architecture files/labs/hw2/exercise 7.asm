bits 32 
; problem 20

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ; a,b,c - byte, d - word
    a db 10
    b db 9
    c db 22
    d dw 156


segment code use32 class=code
    start:
        ; (50-b-c)*2+a*a+d
        
        mov AL, 50
        sub AL, [b]
        sub AL, [c] ; AL : 50 - b - c = 50 - 9 - 22 = 19
        
        mov BL, 2
        mul BL ; AX : 19 * 2 = 38
        
        mov DX, AX ; DX : 38
        
        mov AL, [a]
        mul AL ; AX : a * a = 10 * 10 = 100
        
        add AX, DX ; AX : 100 + 38 = 138
        add AX, [d] ; AX = 138 + 156 = 294
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program