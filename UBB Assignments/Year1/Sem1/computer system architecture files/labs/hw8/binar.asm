bits 32 ; assembling for the 32 bits architecture

global start        

extern exit, fopen, fclose, printf, fread               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll   
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import printf msvcrt.dll    
import fread msvcrt.dll    


segment data use32 class=data
    file_name db "fisier.txt", 0
    access_mode db "a+", 0
    file_descriptor dd -1
    len equ 2
    
    string times 8 db 0
    number dd 0
    

segment code use32 class=code
    start:
        ;string times 8 db 0 
        ;40 / 2 = 20 r 0
        ;mov [string + 0], rest
        ;20 / 2 = 10 r 0
        ;mov [string + 1], rest
        ;10 / 2 = 5 r 0
        ;5 / 2 = 2 r 1
        ;2 / 2 = 1 r 0
        ;1 / 2 = 0 r 1
        ;nr:0 1 0 1 0 0 0 
        ;string: 000101 0 
        
        push access_mode
        push file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je ending
        
        push dword [file_descriptor]
        push len
        push dword 1
        push number
        call [fread]
        add esp, 4 * 4

        
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        ending:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
