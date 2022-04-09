bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 145 ; a is 1001 0001
    b dw 0
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Given the word A, obtain the integer number n represented on the bits 0-2 of A. Then obtain the word B by rotating A n positions to the right. Compute the doubleword C:
        ;the bits 8-15 of C have the value 0
        ;the bits 16-23 of C are the same as the bits of 2-9 of B
        ;the bits 24-31 of C are the same as the bits of 7-14 of A
        ;the bits 0-7 of C have the value 1
        mov BX, 0 ; this is where b will be constructed
        
        mov AX, [a]
        and AX, 0000_0000_0000_0111b ; The bits 0-2 are right at the beginning so I don't need to shift the number
        
        mov CL, 0 ; CL will hold the number n
        add BX, AX ; BX now holds the bits 0-2 of A
        mov CL, BL
        
        mov BX, [a]
        ror BX, CL
        mov [b], BX ; B is now 0000 0000 0100 1000
        
        mov DX, [b] ; DX will hold bits 16-31 of C
        and DX, 0000_0011_1111_1100b ; now DX has bits 2-9 of B
        shr DX, 2 ; now bits 16-23 of C are the same as bits 2-9 of B
        
        mov BX, [a] ;
        and BX, 0111_1111_1000_0000b ; BX has bits 7-14 of A
        shl BX, 1
        add DX, BX 
        mov [c + 4], DX
        
        mov AX, [c + 0]
        or AX, 0000_0000_1111_1111b ; bits 8-15 of C were already 0 and now bits 0-7 of C will be 1
        mov [c + 0], AX
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
