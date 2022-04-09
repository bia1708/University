bits 32 ; assembling for the 32 bits architecture

global start        

extern exit, printf               
import exit msvcrt.dll    
import printf msvcrt.dll 

segment data use32 class=data
    format db "%d / %d = %d", 0
    a dd 200
    b dd 5

segment code use32 class=code
    start:
        ; Two natural numbers a and b (a: dword, b: dword, defined in the data segment) are given. Calculate a/b and display the quotient in the       following format: "<a>/<b> = <quotient>". Example: for a = 200, b = 5 it will display: "200/5 = 40".
        ;The values will be displayed in decimal format (base 10) with sign.
        
        mov eax, [a]
        mov edx, 0
        mov ebx, [b] 
        idiv ebx ; now the quotient is in eax
       
        mov ecx, eax ; we save the quotient in ecx 
        mov eax, [a]
        
        push dword ecx
        push dword ebx
        push dword eax
        push dword format
        call [printf]
        add esp, 4 * 4
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
