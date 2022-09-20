bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll   

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b,d-byte; c-word; e-doubleword; x-qword - SIGNED
    a db 2
    b db 4
    d db 5
    c dw 10
    e dd 100
    x dq 200

; our code starts here
segment code use32 class=code
    start:
        ; x+a/b+c*d-b/c+e; 
        mov AL, [a]
        cbw
        idiv byte [b]
         
        mov BL, AL ; now BL stores a / b = 2 / 4 = 0
        mov BH, 0 ; now BX stores a / b
        mov CX, 0 ; CX:BX stores a / b
        
        mov AL, [d]
        cbw
        mov DX, [c]
        imul DX ; DX:AX now stores c * d = 5 * 10 = 50
        
        clc
        add BX, AX
        adc CX, DX ; CX:BX stores a / b + c * d
        
        mov AL, [b]
        cbw
        cwde
        mov EDX, 0
        idiv word [c] ; AX stores b / c = 0
        mov DX, 0 ; DX:AX stores b / c
        
        clc
        sub BX, AX
        sbb CX, DX
        
        add BX, [e + 0]
        add CX, [e + 2]
        push CX
        push BX
        pop EBX
        mov ECX, 0
        
        add EBX, [x + 0]
        add ECX, [x + 4]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
