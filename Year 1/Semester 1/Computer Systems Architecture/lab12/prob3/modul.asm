bits 32                         

global _cifre

segment code use32 public
_cifre:
    push ebp
    mov ebp, esp
        
    mov eax, [ebp + 8]
    mov ebx, [ebp + 12]
    
    mov esi, 0
    mov edx, 0
    Repeta:
        mov cl, [eax + esi]
        
        cmp cl, 0
        jz Sfarsit
            cmp cl, '0'
            jl not_dig1
                cmp cl, '9'
                jg not_dig2
                    mov [ebx + edx], byte cl
                    inc edx
                
            not_dig2:
        not_dig1:
        
        inc esi
        jmp Repeta
        
    Sfarsit:
    
    mov [ebx + edx], byte 0
    mov eax, ebx
    mov esp, ebp
    pop ebp 
    
	ret 