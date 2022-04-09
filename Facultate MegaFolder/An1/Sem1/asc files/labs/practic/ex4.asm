bits 32

global start        

extern exit, fopen, fclose, fread, fprintf, scanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    file_open times 100 db 0
    access_open db "r", 0
    descriptor_open dd -1
    
    file_close db "out.txt", 0
    access_close db "w", 0
    descriptor_close dd -1
    
    n dd 0
    k dd 0
    c times 1 db 0
    
    string times 100 db 0
    
    len equ 100
    
    read_msg db "Enter file name to open: ", 0
    read_char db "Enter character: ", 0
    read_num db "Enter number: ", 0
    
    format_read_s db "%s", 0
    format_read_d db "%d", 0
    
    format_good db "The number of occurrences of the character %c is equal to the read number %d.", 0
    format_bad db "The number of occurrences of the character %c is not equal to the read number %d.", 0

segment code use32 class=code
    start:
        mov eax, 0
        mov ebx, 0
        mov ecx, 0
        mov edx, 0
        
        push dword access_close
        push dword file_close
        call [fopen]
        add esp, 4 * 2
        
        mov [descriptor_close], eax
        
        cmp eax, 0
        je .final_last
        
        push dword read_msg
        call [printf]
        add esp, 4
        
        push dword file_open
        push dword format_read_s
        call [scanf]
        add esp, 4 * 2
        
        
        push dword read_char
        call [printf]
        add esp, 4
        
        push dword c
        push dword format_read_s
        call [scanf]
        add esp, 4 * 2
        
        
        push dword read_num
        call [printf]
        add esp, 4
        
        push dword n
        push dword format_read_d
        call [scanf]
        add esp, 4 * 2
        
        
        push dword access_open
        push dword file_open
        call [fopen]
        add esp, 4 * 2
        
        mov [descriptor_open], eax
        
        cmp eax, 0
        je .final_last
        
        push dword [descriptor_open]
        push dword len
        push dword 1
        push dword string
        call [fread]
        add esp, 4 * 4
        
        mov ecx, eax
        mov esi, string
        
        .loop:
            mov al, [esi]
            cmp al, [c]
            je .good
            jmp .next
            
            .good:
                inc byte [k]
                jmp .next
            
        .next:
            inc esi
            loop .loop
    
        .final:
            mov al, [k]
            mov cl, [n]
            cmp al, [n]
            je .equal
            jmp .not_equal
            
            .equal:
                mov eax, 0
                mov al, [c]
                
                mov ebx, 0
                mov bl, [n]
                
                push ebx
                push eax
                push dword format_good
                push dword [descriptor_close]
                call [fprintf]
                add esp, 4 * 4
                
                jmp .end
                
            .not_equal:
                mov eax, 0
                mov al, [c]
                
                mov ebx, 0
                mov bl, [n]
                
                push ebx
                push eax
                push dword format_bad
                push dword [descriptor_close]
                call [fprintf]
                add esp, 4 * 4
                
                jmp .end
        
            .end:
                push dword [descriptor_open]
                call [fclose]
                add esp, 4
                
                push dword [descriptor_close]
                call [fclose]
                add esp, 4
                
                jmp .final_last
            
                .final_last:
                    push dword 0
                    call [exit]