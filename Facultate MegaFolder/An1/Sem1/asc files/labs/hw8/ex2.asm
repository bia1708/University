bits 32 ; assembling for the 32 bits architecture

global start        

extern exit, fopen, fread, fclose, printf               
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll    

segment data use32 class=data
    file_name db "numbers.txt", 0
    access_mode db "r", 0 
    file_descriptor dd -1 
    
    len equ 100         
    len_numbers dw 0
    numbers times (len+1) db 0
    digits db '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0
    max_freq db 0
    max_digit db 0
    count db 0
    format db "The digit with the highest frequency(%d) is %c", 0 

segment code use32 class=code
    start:
        ; A text file is given. Read the content of the file, determine the digit with the highest frequency and display the digit along with its frequency on the screen. The name of text file is defined in the data segment.
        
        ; first we have to open the file
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2  

        mov [file_descriptor], eax
        cmp eax, 0 ; we check to see if the file was opened correctly
        je ending
        
        ; now we read the numbers from the file
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword numbers       
        call [fread]
        add esp, 4*4
        mov [len_numbers], word eax
        inc word[len_numbers]
        
        ; in numbers we have the array of chars
        mov esi, digits
        cld 
        ;mov ebx, 0
        loop1:
            mov edi, numbers
            lodsb
            cmp  al, 0
            je ending2
            
            mov ecx, [len_numbers]
            mov byte[count], 0
            
            loop2:
            scasb
            jne not_found
                inc byte [count]
            not_found:
            dec ecx
            jnz loop2
            
            mov dl, [count]
            mov bl, [max_freq]
            cmp dl, bl
            jl not_greater
                mov [max_freq], byte dl
                mov [max_digit], byte al 
            not_greater:
        jmp loop1
        ending2:
        
        ;here we print the message
        movzx eax, byte [max_freq]
        movzx ebx, byte [max_digit]
        push dword ebx
        push dword eax
        push dword format
        call [printf]
        add esp, 4 * 4
        
        ; now we close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        ending:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
