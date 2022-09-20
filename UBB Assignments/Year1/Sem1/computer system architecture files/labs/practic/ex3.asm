bits 32 ; assembling for the 32 bits architecture

global start        


extern exit, scanf, fopen, fclose               
import exit msvcrt.dll 
import scanf msvcrt.dll 
import fopen msvcrt.dll
import fclose msvcrt.dll     

segment data use32 class=data
    file_name_format db "%s%n", 0
    len dd 0
    acces_mode db "a", 0 
    file_name db 0
    file_descriptor dd -1
    new_file_name resb 0

segment code use32 class=code
    start:
        push len
        push file_name
        push file_name_format
        call [scanf]
        add esp, 4 * 3
        
        push dword acces_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je ending
        
        mov eax, file_name
        
        find_end:
            cmp eax, 0
            je finish
            inc dword eax
        finish:
        dec dword eax
        
        mov esi, file_name
        mov ebx, [len]
        mov ecx, 0
        start_loop1:
            mov al, [esi]
            cmp al, 0
            je start_loop2
            
            cmp AL, 'A'
            jl not_capital
            
            cmp AL, 'Z' ; we skip letters > Z
            jg not_capital
            
            not_capital:
                inc esi
                jmp start_loop1
            
            mov [new_file_name + ecx], BL ; if it's a capital letter we store it in new_file_name
            inc esi
            dec dword ebx
            inc ecx
            jmp start_loop1
            
        start_loop2:
        ending:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
