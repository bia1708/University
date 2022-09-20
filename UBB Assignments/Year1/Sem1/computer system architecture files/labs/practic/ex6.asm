bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fread, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import fread msvcrt.dll 
import printf msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    access_mode db "r", 0
    file_name db "sir.txt", 0
    file_descriptor dd -1
    len equ 100
    sir resb 0
    poz equ 8
    
    

; our code starts here
segment code use32 class=code
    start:
        push access_mode
        push file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        cmp eax, 0
        je ending
        
        push dword [file_descriptor]
        push len
        push 1
        push sir
        call [fread]
        add esp, 4 * 4
        
        mov [sir + poz], byte "7"
        
        push sir
        call [printf]
        add esp, 4
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        ending:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
