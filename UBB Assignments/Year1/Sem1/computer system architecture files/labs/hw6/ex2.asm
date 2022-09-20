bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    ; sir DW 12345, 20778, 4596 
    s dw 12345, 20778, 4596 
    l equ ($-s) / 2
    nl db 0
    d times l * 2 db 0 

; our code starts here
segment code use32 class=code
    start:
        ; Being given a string of words, obtain the string (of bytes) of the digits in base 10 of each word from this string.
        
        mov esi, s
        mov edi, 0
        cld
        mov ecx, l
        loop_words:
            lodsw ; ax stores each word
            mov [nl], byte 0 ; this variable will keep the length of each number(the number of digits)
            digit_parsing:
                mov dx, 0 ; I want to divide DX:AX so that my digits will be ready to be pushed on the stack
                mov bx, 10
                div bx ; dx has the digit, ax has the quotient(the remaining number)
                push dx ; we push all the digits on the stack to pop them in the right order
                add [nl], byte 1
                cmp ax, 0 ; we check to see if we have any digits left
                jz next_step 	
            jmp digit_parsing
            next_step:
            
            digit_arrangement:
                pop dx ; this would be the first digit of the number, of type word
                mov [d + edi], dl ; I'm only interested in dl because that's where my digit will be, so I move that in the destination string
                inc edi
                sub [nl], byte 1
                cmp [nl], byte 0
                jz ending
            jmp digit_arrangement
            ending:
        loop loop_words
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
