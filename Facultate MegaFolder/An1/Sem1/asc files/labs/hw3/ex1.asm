bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit               
import exit msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Unsigned representation
    a db 4
    b dw 300
    c dd 70
    d dq 1111111111111111h

; our code starts here
segment code use32 class=code
    start:
        ; (a+b)-(a+d)+(c-a)
        
        mov AX, word [c + 0]
        mov DX, word [c + 2] ; DX:AX stores the doubleword c
        movzx BX, [a] ;
        mov CX, 0 ; CX:BX stores a
        clc
        sub AX, BX
        sbb DX, CX ; result of c - a is in DX:AX
        
        mov BL, [a]
        mov BH, 0 ; unsigned conversion from BL to BX
        add BX, [b] ; BX: a + b = 4 + 300 = 304
        mov CX, 0 ; CX:BX stores a + b
        
        clc
        add AX, BX
        adc DX, CX ; in DX:AX we have (a + b) + (c - a)
        
        push DX
        push AX
        pop EAX ; EAX now stores (a + b) + (c - a)
        mov EDX, 0 ; EDX:EAX now stores (a + b) + (c - a)
        
        movzx BX, [a] ; BX stores a    
        ;mov BH, 0
        ;mov BL, [a]
        mov CX, 0
        push CX
        push BX
        pop EBX
        mov ECX, 0 ; ECX:EBX stores a
        
        ; result will be in EDX:EAX = 1111 1111 1111 1115
        add EBX, dword [d + 0]
        add ECX, dword [d + 4]
        
        clc
        sub EAX, EBX
        sbb EDX, ECX ; final result will be in EDX:EAX = EEEE EEEE EEEE F05D
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
