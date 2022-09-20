bits 32

extern scanf, s1, s2, s3
global read_string
import scanf msvcrt.dll

segment data use32 class=data   
    format db "%s", 0


segment code use32 class=code
read_string:
    push dword s1
    push dword format
    call [scanf]
    add esp, 4 * 2
    
    push dword s2
    push dword format
    call [scanf]
    add esp, 4 * 2
    
    push dword s3
    push dword format
    call [scanf]
    add esp, 4 * 2
    
    ret
    
    