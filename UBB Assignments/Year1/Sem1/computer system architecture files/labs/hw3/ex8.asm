bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll   

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a-word; b-byte; e-doubleword; x-qword SIGNED
    a dw 5
    b db 2
    e dw 10
    x dq 100
    r resw 1

; our code starts here
segment code use32 class=code
    start:
        ; x-b+8+(2*a-b)/(b*b)+e;
        mov AL, [b]
        imul AL ; AX stores b * b = 4
        mov [r], AX
        
        mov AX, [a]
        mov BX, 2
        imul BX ; DX:AX stores a * 2 = 10
       
        mov BL, [b]
        mov BH, 0
        mov CX, 0 ; CX:BX
        
        clc
        sub AX, BX
        sbb DX, CX ; DX:AX stores a * 2 - b = 10 - 2 = 8
        
        mov BX, [r]
        idiv BX ; AX stores (2*a-b)/(b*b) = 2
        
        add AX, [e]
        add AX, 8 ; AX stores (2*a-b)/(b*b) + e + 8 = 20
        
        mov BL, [b]
        mov BH, 0
        sub AX, BX ; AX stores (2*a-b)/(b*b) + e + 8 - b = 18
        cwde
        mov EDX, 0
        
        add EAX, [x + 0]
        add EDX, [x + 4] ; final result is in EDX:EAX = 118
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
