bits 32
global start

extern exit, fopen, fclose, printf, fprintf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    file_descriptor dd -1
    format db "%s", 0
    
    text resb 105
    mesaj resb 105
    output db "mesaj.txt", 0
    access_mode db "w", 0
    
segment code use32 class=code
start:
    push dword text
    push dword format
    call [scanf]
    add esp, 4 * 2
    
    mov esi, 0
    Repeta:
        mov dl, [text + esi]
        
        cmp dl, 0
        je afara
        
        cmp dl, '0'
        jb mai_mic3
            cmp dl, '9'
            ja mai_mare3
                mov bl, '0'
                mov cl, dl
                sub cl, bl
                mov [text + esi], cl
                
            mai_mare3:
            
        mai_mic3:
        
        cmp dl, 'A'
        jb mai_mic1
            cmp dl, 'F'
            ja mai_mare1
                mov bl, 'A'
                mov cl, dl
                sub cl, bl
                add cl, 10
                mov [text + esi], cl
                
            mai_mare1:
            
        mai_mic1:
            
        cmp dl, 'a'
        jb mai_mic2
            cmp dl, 'f'
            ja mai_mare2
                mov bl, 'a'
                mov cl, dl
                sub cl, bl
                add cl, 10
                mov [text + esi], cl
                
            mai_mare2:
            
        mai_mic2:
        
        inc esi
        jmp Repeta
        
    afara:
    
    mov edi, 0
    mov esi, 0
    Repeta2:
        mov dl, [text + esi]
        
        cmp dl, 0
        je afara2
            
        mov al, dl
        mov bl, 16
        mul bl
            
        inc esi
        cmp dl, 0
        je afara2
        
        mov dl, [text + esi]
        mov dh, 0
        add ax, dx
        
        mov cl, al
        mov [mesaj + edi], cl
        inc edi
        
        inc esi
        jmp Repeta2
        
    afara2:
    
    push dword access_mode   
    push dword output
    call [fopen]
    add esp, 4*2
    
    mov [file_descriptor], eax
    cmp eax, 0
    je gata
    
    push dword mesaj
    push dword [file_descriptor]
    call [fprintf]
    add esp, 4*2
    
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    gata:
    
    push dword 0
    call [exit]
    
