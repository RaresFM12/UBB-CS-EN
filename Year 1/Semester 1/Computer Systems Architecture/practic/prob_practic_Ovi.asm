bits 32
global start

extern exit, fopen, fread, fclose, printf, fprintf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    file_descriptor dd -1
    format db "%s", 0
    
    cifre resb 50
    impare db "13579", 0
    nr resb 50
    output db "ovi.txt", 0
    access_mode db "w", 0
    
segment code use32 class=code
start:
    push dword cifre
    push dword format
    call [scanf]
    add esp, 4 * 2
    
    push dword access_mode   
    push dword output
    call [fopen]
    add esp, 4*2
    
    mov [file_descriptor], eax
    cmp eax, 0
    je gata
    
    mov esi, 0 ; merge prin impare
    mov edi, 0 ; merge prin cifre
    mov ebx, 0 ; cnt nr
    
    Repeta1:
        mov dl, [impare + esi]
        
        Repeta2:
            mov cl, [cifre + edi]
            
            cmp cl, 0
            je aici
            
            cmp cl, dl
            jne nu_imp
                mov [nr + ebx], cl
                inc ebx
                
            nu_imp:
            
            inc edi
            jmp Repeta2
        
        aici:
        inc esi
        mov edi, 0
        
        cmp esi, 5
        je final
            jmp Repeta1
       
    final:
    
    push dword nr
    push dword [file_descriptor]
    call [fprintf]
    add esp, 4*2
            
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    gata:
    
    push dword 0
    call [exit]
    
