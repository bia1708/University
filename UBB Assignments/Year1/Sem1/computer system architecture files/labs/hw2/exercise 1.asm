bits 32 
; problems 6 & 20

global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    a dd 256
    b dd 1
    
    c db 13
    d db 3
    

segment code use32 class=code
    start:
        ; ...
        
        mov AX, [a]
        mov DX, [b]
        mul DX
        
        mov AX, 0
        mov AL, [c]
        div byte[d]
        
        ;mov BL, [d]
        ;div BL
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
