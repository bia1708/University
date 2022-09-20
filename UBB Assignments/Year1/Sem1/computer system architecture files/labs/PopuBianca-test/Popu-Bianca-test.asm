;Se citesc dintr-un fisier caractere, pana la intalnirea caracterului #. Sa se afiseze la consola numarul literelor mici, urmat de numarul literelor mari citite.
bits 32 


global start        


extern exit, fopen, fclose, fread, printf               
import exit msvcrt.dll    
import fopen msvcrt.dll 
import fclose msvcrt.dll 
import fread msvcrt.dll 
import printf msvcrt.dll  

segment data use32 class=data
capital_letters dd 0
    small_letters dd 0 
    format db "The number of small letters is %d, and the number of capital letters is %d.", 0
    access_mode db "r", 0 ; we only read from the file so the access mode will be r
    file_name db "input.txt", 0
    file_descriptor dd -1
    character resb 0
    
    

segment code use32 class=code
    start:
    ; first, we open the file
        push access_mode
        push file_name
        call [fopen]
        add esp, 4 * 2
        
        ; we check to see if the file opened correctly
        mov [file_descriptor], eax
        cmp eax, 0
        je ending
        
        start_loop:
            ; first we read a character from the file
            push dword [file_descriptor]
            push dword 1
            push dword 1
            push dword character
            call [fread]
            add esp, 4 * 4
            
            ; then we check to see if the character we last read is #. If it is, we exit the loop
            cmp [character], byte "#"
            je end_loop
            
            ; then i checked to see if it's a small letter
            cmp [character], byte "a"
            jl not_small
            
            cmp [character], byte "z"
            jg not_small
            
            inc dword [small_letters]
            jmp start_loop
            
            ; if it's not a small letter, I check to see if it's a capital letter
            not_small:
                cmp [character], byte "A"
                jl not_capital
                
                cmp [character], byte "Z"
                jg not_capital
                
                inc dword [capital_letters]
                jmp start_loop
            
            not_capital:
            jmp start_loop
        
        end_loop:
        
        ; now we print the results in the console
        push dword [capital_letters]
        push dword [small_letters]
        push format
        call [printf]
        add esp, 4 * 3
    
        ; we close the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        ending:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
