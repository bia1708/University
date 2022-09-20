bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword - Signed representation
    a db 4
    b dw 300
    c dd 70
    d dq 1111111111111111h

; our code starts here
segment code use32 class=code
    start:
        ; c-(d+a)+(b+c)
        mov AL, [a]
        cbw
        cwde
        cdq
        clc
        add EAX, [d + 0]
        add EDX, [d + 4] ; EDX:EAX stores a + d = 74
        
        mov EBX, EAX
        mov ECX, EDX ; ECX:EBX now stores a + d = 74
        
        mov AX, [b]
        cwde 
        add EAX, [c] ; EAX stores b + c = 370
        mov EDX, 0
        clc
        sub EAX, EBX
        sbb EDX, ECX 
        
        
        mov EBX, [c]
        mov ECX, 0
        clc
        add EBX, EAX
        adc ECX, EDX ; c - (d + a) + (b + c)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
