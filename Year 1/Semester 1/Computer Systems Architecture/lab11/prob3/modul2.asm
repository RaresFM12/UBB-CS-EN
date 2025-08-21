bits 32                         
segment code use32 public code

global cifre

cifre:
    mov eax, [esp + 8]
    mov ebx, [esp + 4]
    
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
	ret 