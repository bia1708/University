bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               
import exit msvcrt.dll    

; our data is declared here 
segment data use32 class=data
    A db 2, 1, -3, 3, -4, 2, 6
    la equ $-A
    B db 4, 5, 7, 6, 2, 1
    lb equ $-B
    R times la+lb db 0

; our code starts here
segment code use32 class=code
    start:
        ; Two byte strings A and B are given. Obtain the string R by concatenating the elements of B in reverse order and the negative elements of A.
        ;Example:
        ;A: 2, 1, -3, 3, -4, 2, 6
        ;B: 4, 5, 7, 6, 2, 1
        ;R: 1, 2, 6, 7, 5, 4, -3, -4
        mov ECX, lb
        mov esi, 0
        jecxz ending
        start_loop1:
            mov AL, [B + ECX - 1]
            mov [R + esi], AL
            inc esi
        loop start_loop1
        ending:
        
        mov ECX, la
        mov edi, 0
        jecxz ending2
        start_loop2:
            mov AL, [A + edi]
            cmp AL, 0
            jge lower_than_zero
                mov [R + esi], AL
                inc esi
            lower_than_zero:
            inc edi
        loop start_loop2
        ending2:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
