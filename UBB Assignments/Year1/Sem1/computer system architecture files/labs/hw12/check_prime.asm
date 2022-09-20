bits 32 

global _check_prime        

segment data public data use32 ;class=data
    is_prime dw 1

segment code public code use32 ;class=code
    _check_prime:
        push ebp
        mov ebp, esp 
        sub esp, 4*2
        pushad
        
        mov ecx, [ebp + 8] ; this will be the number passed as a parameter = the number we want to check if it's a prime
        
        mov ebx, 2
        
        .start_loop:
            cmp ecx, ebx
            je .end_of_algorithm
            
            mov eax, ecx
            cdq
            idiv ebx
            cmp edx, 0
            je .not_prime
            
            inc ebx
            jmp .start_loop
            
        .not_prime:
            mov [is_prime], dword 0
         
         
        .end_of_algorithm:        
        popad
        mov eax, [is_prime] 
        mov [is_prime], dword 1
        mov esp, ebp
        pop ebp 
           
        ret