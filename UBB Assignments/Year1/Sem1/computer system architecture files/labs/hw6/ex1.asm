bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    ; s: -22, 145, -48, 127 <=> 1111_1111_1110_1010, 0000_0000_1001_0001, 1111_1111_1101_0000, 0000_0000_0111_1111
    s dw -22, 145, -48, 127
    ls equ ($-s) / 2
    d times ls dw 0 ; should be : 3, 3, 5, 7

segment code use32 class=code
    start:
        ; A word string s is given. Build the byte string d such that each element d[i] contains:
            ;- the count of zeros in the word s[i], if s[i] is a negative number
            ;- the count of ones in the word s[i], if s[i] is a positive number
        mov esi, s
        mov edi, 0
        cld
        mov ecx, ls
        loop1:
            lodsw
            push ECX ; I will need ECX for this loop so I'll just push it on the stack and then use it at the end
            mov ECX, 16
            mov BX, 0 ; this will hold number of 1s
            cmp AX, 0
            jg count_of_zeroes ;  this will be executed for numbers lower than 0
                loop2:
                    clc
                    mov DX, AX
                    shr DX, 1
                    adc BX, 0 ; this will add all the 1s obtained in the CF by doing the shr
                loop loop2
                mov DX, 16
                sub DX, BX ; this will get me the number of 0s
                mov [d + edi], BX
                inc edi
            count_of_zeroes:
            mov ECX, 16
            ; this next part gets executed for positive numbers
            jl count_of_ones
                loop3:
                    clc
                    mov DX, AX
                    shr DX, 1
                    adc BX, 0 ; this will add all the 1s obtained in the CF by doing the shr
                loop loop3
                mov [d + edi], BX
                inc edi
            count_of_ones:
            pop ECX ; I'm getting back ECX
        loop loop1
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
