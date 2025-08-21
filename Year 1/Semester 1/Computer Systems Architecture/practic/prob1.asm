bits 32
global start

extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    file_name db "prob1.txt", 0
    access_mode db "r", 0
    
    file_descriptor dd -1
    len equ 100
    text times len db 0
    sir times len db 0
    format db "%s", 0
    
segment code use32 class=code
start:
    push dword access_mode
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    mov [file_descriptor], eax
    cmp eax, 0
    je final
    
    push dword [file_descriptor]
    push dword len
    push dword 1
    push dword text
    call [fread]
    add esp, 4 * 4
    
    mov esi, 0
    mov edi, 0
    mov dl, [text]
    Repeta:
        mov bl, [text + esi]
        
        cmp bl, 0
        je final_sir
            cmp bl, 32
            je final_nr
                cmp bl, dl
                ja mai_mare
                    mov dl, bl
                
                mai_mare:
            
            final_nr:
        
            cmp bl, 32
            jne not_new_word
                mov [sir + edi], dl
                inc edi
                mov [sir + edi], byte 32
                inc edi
                mov dl, [text + esi + 1]
                
            not_new_word:
            
        inc esi
        jmp Repeta
        
    final_sir:
    
    mov [sir + edi], dl
                
    push dword sir
    push dword format
    call [printf]
    add esp, 4 * 2
    
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    final:
    
    push dword 0
    call [exit]
    
