bits 32 ; assembling for the 32 bits architecture

global start, s1, s2, s3        

extern exit, read_string, printf             
import exit msvcrt.dll   
import printf msvcrt.dll    

segment data use32 class=data
    format db "%s", 0
    s1 dd 0
    s2 dd 0
    s3 dd 0
    final_string times 4 dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Three strings (of characters) are read from the keyboard. Identify and display the result of their concatenation.
        call read_string
        
        mov eax, [s1]
        mov [final_string + 0], eax
        mov eax, [s2]
        mov [final_string + 4], eax
        mov eax, [s3]
        mov [final_string + 8], eax
        
        push dword final_string
        push dword format
        call [printf]
        add esp, 4 * 2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
