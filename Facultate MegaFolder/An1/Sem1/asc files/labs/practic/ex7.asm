bits 32 


global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    sir db '1','2','3','4','5','6','7','8', 0
    l equ $-sir
    dest times l db 0

segment code use32 class=code
    start:
        mov esi, sir + l - 1
        mov edi, dest
        mov ecx, l
        start_loop:
            std
            lodsb 
            cld
            stosb 
            loop start_loop
        
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
