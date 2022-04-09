bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Signed representation
    a db 4
    b dw 300
    c dd 50
    d dq 70

; our code starts here
segment code use32 class=code
    start:
        ; a-b-(c-d)+d
        mov EAX, [c]
        cdq
        clc
        sub EAX, [d + 0]
        sbb EDX, [d + 4] ; now EDX:EAX stores c - d
        
        mov EBX, EAX
        mov ECX, EDX
        
        mov AL, [a]
        cbw
        cwde
        cdq
        clc
        sub EAX, EBX
        sbb EDX, ECX ; EDX:EAX now stores a - (c - d) = 4 + 20
        
        add EAX, [d + 0]
        add EDX, [d + 4] ; EDX:EAX now stores a - (c - d) + d = 94
        
        mov BX, [b]
        mov CX, 0 ;CX:BX stores b
        push CX
        push BX
        pop EBX
        mov ECX, 0
        clc
        sub EAX, EBX
        sbb EDX, ECX ; EDX:EAX stores the final result 94 - 300 = -206
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
