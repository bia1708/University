;Se da in data segment un sir de exact 8 de caractere si numele unui fisier.
;Fisierul dat contine un numar de la 0 la 7. Sa se citeasca acel numar (fie n numarul citit).
;Sa se creeze n fisiere, fiecare avand numele output-i.txt, unde i=0,n. Sa se scrie in fiecare fisier primele (i+1) caractere din sirul dat.

bits 32

global start        
 
extern exit, fopen, fclose, fprintf, fread
import exit msvcrt.dll 
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir db "12345678", 0                ;sirul dat in data segment
    n resd 1
    pozitie_inserare equ 7              ;pozitia la care se afla i, numarul fisierului
    fisier_input db "input.txt", 0      ;numele fisierului de intrare dat in data segment
    fisier_output db "output-i.txt", 0
    descriptor_fis resd 1
    descriptor_fis_creat resd 1
    mod_acces_citire db "r", 0
    mod_acces_scriere db "w", 0
    format_citire db "%d", 0
    
segment code use32 class=code
    start: 
        ; deschidem fisierul
        push dword mod_acces_citire
        push dword fisier_input
        call [fopen]
        add ESP, 4*2
 
        mov [descriptor_fis], EAX
        cmp EAX, 0
        je Finish
        
        ; citim din fisier
        push dword [descriptor_fis]
        push dword 1
        push dword 1
        push dword n
        call [fread]
        add ESP, 4*4
        
        mov ECX, [n]
        sub ECX, '0'
        inc ECX
        mov [sir+ECX], byte 0    ; facem ultimul caracter NULL
        dec ECX
        
        ; creem fisierul "output-i.txt", unde i = ECX
        Repeating:
            mov EAX, ECX
            add EAX, '0'
            mov [fisier_output+pozitie_inserare], AL
            
            pushad  ; salvam valorile din registri
            ; creem fisierul cu indicele i
            push dword mod_acces_scriere
            push dword fisier_output
            call [fopen]
            add ESP, 4*2
     
            mov [descriptor_fis_creat], EAX
            cmp EAX, 0
            je Finish
            
            ; scriem sirul in fisierul creat
            push dword sir
            push dword [descriptor_fis_creat]
            call [fprintf]
            add ESP, 4*2
            
            ; inchidem fisierul cu indicele i
            push dword [descriptor_fis_creat]
            call [fclose]
            add ESP, 4
            
            popad   ; restauram valorile din registri
            mov [sir+ECX], byte 0    ; facem ultimul caracter NULL
            
        loop Repeating
        
        ; cazul i = 0 il facem separat
        
        mov EAX, ECX
        add EAX, '0'
        mov [fisier_output+pozitie_inserare], AL
        
        ; creem fisierul cu indicele 0
        push dword mod_acces_scriere
        push dword fisier_output
        call [fopen]
        add ESP, 4*2
 
        mov [descriptor_fis_creat], EAX
        cmp EAX, 0
        je Finish
        
        ; scriem sirul in fisierul creat
        push dword sir
        push dword [descriptor_fis_creat]
        call [fprintf]
        add ESP, 4*2
        
        ; inchidem fisierul cu indicele 0
        push dword [descriptor_fis_creat]
        call [fclose]
        add ESP, 4
        
        ; inchidem fisierul
        push dword [descriptor_fis]
        call [fclose]
        add ESP, 4
        
        Finish:
        push    dword 0
        call    [exit]