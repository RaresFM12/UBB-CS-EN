bits 32
global start

extern exit
import exit msvcrt.dll

extern printf
import printf msvcrt.dll

segment data use32 class=data
    sir dq 1122334455667788h, 5332413244444444h
    len equ ($ - sir) / 8
    sir2 resd len
    nr_cuv db 0
    
    cnt db 0
    voc db "aeiouAEIOU", 0
    format db "%d", 0

segment code use32 class=code
vocale:
    mov ebx, [esp + 4]
    mov edi, 0        ; cu edi merg prin voc  
    mov cl, 0
    
    .Repeta1:
        lodsd         ; luam fiecare dublu-cuvant
        mov edi, 0
        
        .Repeta2:
            mov bl, [voc + edi]
            
            cmp ah, bl
            jne .nu_e_voc
                inc byte [cnt]
                jmp .gasit
            
            .nu_e_voc:
            
            inc edi
            cmp edi, 10    ; nu mai am vocale
            je .nu_am_gasit
            
            jmp .Repeta2
    
        .gasit:
        .nu_am_gasit:
        
        inc cl
        cmp cl, byte [nr_cuv]
        je .afara
        
        jmp .Repeta1
        
    .afara:
        
    mov eax, 0
    mov al, [cnt]
        
    ret
    
start:
    mov esi, sir
    mov edi, sir2
    mov ecx, 0
    Repeta:
        mov bx, 0
        
        lodsd          ; descarcam partea low de dublucuvant
        lodsd          ; iau dublu-cuvantul high
        mov bx, ax     ; iau cuvantul low in bx
        ror eax, 16    ; mut cuvantul high in ax
        
        cmp ax, bx     ; compar cuvant high cu cel low din dublu-cuvant
        jng mai_mic
            ; daca este mai mare in interpretarea cu semn ajunge aici
            ror eax, 16   ; aducem valoarea din eax in pozitia initiala
            stosd
            inc byte [nr_cuv]
        
        mai_mic:
        
        inc ecx        ; contorul de numere din sir
        cmp ecx, len   ; daca contorul are lungimea sirului nu mai avem elemente in sir
        je afara 
        
        jmp Repeta
        
    afara:
    
    push dword sir2
    call vocale
    
    push dword eax
    push dword format
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]