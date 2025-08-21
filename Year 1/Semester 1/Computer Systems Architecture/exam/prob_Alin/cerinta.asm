bits 32

extern printf
import printf msvcrt.dll

global cerinta
segment data use32 
    a db "aici", 0
    frm db "%s", 0
    frm2 db "%x", 10, 0
    eleven dw 11
    cnt db 0
    aux dd 0
    
segment code use32 public code
cerinta:
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov esi, 0
    mov edx, 0
    
    Repeta1:
        mov edi, 0
        
        
        Repeta2:
            cmp esi, edi
            je nup
                mov eax, 0
                mov edx, 0
                mov ah, [ebx + esi]
                mov al, [ebx + edi]
                
                test ax, 1
                jz par
                    mov dword [aux], eax
                    div word [eleven]
                    
                    cmp dx, 0
                    jnz nu_rest
                        inc byte [cnt]
                        
                    nu_rest:
                
                par:
            
            nup:
            
            inc edi
            cmp edi, ecx
            jz afara
            
            jmp Repeta2
        
        afara:
        
        inc esi
        cmp esi, ecx
        jz final
        
        jmp Repeta1
        
    final:
    mov eax, 0
    mov al, [cnt]
    
    ret