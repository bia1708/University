bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a dw 123
    b dw 200
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Given the words A and B, compute the doubleword C as follows:
        ;the bits 0-5 of C are the same as the bits 3-8 of A
        ;the bits 6-8 of C are the same as the bits 2-4 of B
        ;the bits 9-15 of C are the same as the bits 6-12 of A
        ;the bits 16-31 of C have the value 0
        
        ;the bits 0-5 of C are the same as the bits 3-8 of A
        mov AX, [a]
        and AX, 0000_0001_1111_1000b ; AX has bits 3-8 of A
        shr AX, 3 
        
        ;the bits 6-8 of C are the same as the bits 2-4 of B
        mov BX, [b]
        and BX, 0000_0000_0001_1100b ; BX has bits 2-4 of B
        shl BX, 3
        or AX, BX
        
        ;the bits 9-15 of C are the same as the bits 6-12 of A
        mov BX, [a]
        and BX, 0001_1111_1100_0000b ; BX has the bits 6-12 of A
        shl BX, 3
        or AX, BX
        
        ;the bits 16-31 of C have the value 0
        mov [c + 0], AX
        mov DX, 0
        mov [c + 4], DX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
