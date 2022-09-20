bits 32 
; problems 6 & 20

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    ; a, b, c - byte; g - word
    a db 2
    b db 3
    c db 5
    g dw 200


segment code use32 class=code
    start:
        ; [(a+b+c)*2]*3/g
        
        mov AL, [a]
        add AL, [b]
        add AL, [c] ; AL : 2 + 3 + 5 = 10
        
        mov BL, 90h
        mul BL ; AX : 90 * 10 = 900
        
        mov BX, 3
        mul BX ; DX:AX : 20 * 3 = 60
        
        mov BX, [g]
        div BX ; DX : 60,  AX : 0
        
        add 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program