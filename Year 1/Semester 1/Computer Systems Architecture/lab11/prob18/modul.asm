bits 32                         
segment code use32 public code

global minimul

minimul:
    mov eax, [esp + 4]
    mov ecx, 0
    
    mov bl, [eax + ecx]
    mov dl, [eax + ecx + 1]
    cmp dl, 10
    jz final
    
    add ecx, 2
    
    Repeta2:
        mov dl, [eax + ecx]
        cmp bl, dl
        jb mai_mic
            mov bl, dl
        
        mai_mic:
        
        mov dl, [eax + ecx + 1]
        cmp dl, 10
        jz final
        
        add ecx, 2
        jmp Repeta2
        
    final:
    ret