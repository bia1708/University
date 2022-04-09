bits 32 ; assembling for the 32 bits architecture

global start        

extern exit, fopen, scanf, fprintf, fclose               
import exit msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    file_name db "numbers3.txt", 0
    access_mode db "a", 0
    file_descriptor dd -1
    
    number dd 0
    input_format db "%d", 0
    sum dd 0
    output_format db "%d - %d ", 0

segment code use32 class=code
    start:
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je ending
        
        reading_loop:
            push dword number
            push dword input_format
            call [scanf]
            add esp, 4 * 2
            
            mov eax, [number]
            cmp eax, 0
            je ending
            
            add [sum], eax
            
            push dword [sum]
            push dword [number]
            push dword output_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4 * 4
            
            jmp reading_loop
        
    
        ending:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
