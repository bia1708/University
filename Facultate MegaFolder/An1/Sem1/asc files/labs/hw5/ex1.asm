bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    S db 1, 2, 3, 4, 5, 6, 7, 8
    l equ $-S
    D times l db 0
    
; our code starts here
segment code use32 class=code
    start:
        ; A byte string S is given. Obtain the string D by concatenating the elements found on the even positions of S and then the elements found on the odd positions of S.
        ; S: 1, 2, 3, 4, 5, 6, 7, 8
        ; D: 1, 3, 5, 7, 2, 4, 6, 8
        mov ECX, l
        mov esi, 0
        mov edi, 0
        jecxz ending1
        start_loop1: 
            mov AL, [S + esi]
            mov [D + edi], AL
            add edi, 1
            add esi, 2
            sub ECX, 1
        loop start_loop1
        ending1:
        
        mov ECX, l
        mov esi, 1
        jecxz ending2
        start_loop2:
            mov AL, [S + esi]
            mov [D + edi], AL
            add edi, 1
            add esi, 2
            sub ECX, 1
        loop start_loop2
        ending2:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
