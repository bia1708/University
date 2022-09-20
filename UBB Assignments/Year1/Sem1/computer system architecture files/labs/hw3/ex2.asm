bits 32 ; assembling for the 32 bits architecture

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
        ; (a+c)-b+a+(d-c)
        mov EBX, [d + 0]
        mov ECX, [d + 4]
        
        mov EAX, [c]
        mov EDX, 0
        
        clc
        sub EBX, EAX ; 
        ;ECX:EBX: 11 22 33 44 55 66 77 88h
        sbb ECX, EDX ; result is in ECX:EBX = d - c = 1111 1111 1111 10CB
        
        movzx AX, [a]
        mov DX, 0
        clc
        add AX, [c + 0]
        adc DX, [c + 2] ; result of a + c is in DX:AX = 74
        
        push DX
        push AX
        pop EAX
        mov EDX, 0
        
        clc
        add EBX, EAX
        adc ECX, EDX ; result of (a + c) + (d - c) is in ECX:EBX = 1111 1111 1111 1115
        
        movzx AX, [a]
        sub AX, [b]
        mov DX, 0 ; DX:AX stores the result of b - a = -296
        push DX
        push AX
        pop EAX
        mov EDX, 0
        
        clc
        add EBX, EAX
        adc ECX, EDX ; ECX:EBX now stores the final result = 1111 1111 1112 0FEDbits 32
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
