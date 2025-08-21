bits 32
global start

extern exit, fopen, fread, fclose, printf, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    file_name db "prob_Comsa.txt", 0
    access_mode db "r", 0
    file_descriptor dd -1
    format db "%s", 0
    
    text resb 200
    len equ 200
    nr times len db 0
    sir times (len + 1) db 0
    output resb 50
    access_mode_out db "w", 0
    
segment code use32 class=code
start:
    push dword access_mode
    push dword file_name
    call [fopen]
    
    mov [file_descriptor], eax
    cmp eax, 0
    je final
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        mov edi, 1 ; sa vad daca sunt pe o linie para/impara
        mov esi, 0 ; merg prin text
        mov ecx, 0 ; linia pe care o scriu
        mov dh, 0  ; cuv nou
        mov ebx, 0
        Repeta:
            mov dl, [text + esi] ; caracterul curent
            
            cmp dl, 10
            jnz nu_e_rand_nou
                test edi, 1
                jnz impar
                    mov [sir + ecx], byte 0
                    
                    pushad
                    
                    push dword access_mode_out
                    push dword output
                    call [fopen]
                    add esp, 4 * 2
                    
                    push dword sir
                    push dword [file_descriptor]
                    call [fprintf]
                    add esp, 4 * 2
            
                    push dword [file_descriptor]
                    call [fclose]
                    add esp, 4
                    
                    popad
                    
                impar:
            
                inc edi
                mov dh, 0
                
                test edi, 1
                jnz impar1
                    mov ecx, 0
                
                impar1:
                
                test edi, 1
                jz par1
                    mov ebx, 0
                    
                par1:
                
                inc esi
                jmp Repeta
                
            nu_e_rand_nou:
            
            test edi, 1
            jnz impar2
                mov [sir + ecx], dl
                inc ecx
                
            impar2:
            
            test edi, 1
            jz par2
                cmp dl, ' '
                jnz nu_e_cuv_nou1
                    inc dh
                    cmp dh, 1
                    jnz nu_txt
                        mov [output + ebx], byte '.'
                        mov [output + ebx + 1], byte 't'
                        mov [output + ebx + 2], byte 'x'
                        mov [output + ebx + 3], byte 't'
                        mov [output + ebx + 4], byte 0
                        
                    nu_txt:
                    
                nu_e_cuv_nou1:
                
                cmp dh, 0
                jnz cuv_nou
                    mov [output + ebx], dl
                    inc ebx
                    
                cuv_nou:
             
            par2:
                        
            inc esi
            jmp Repeta
            
    
    final:
    
    push dword 0
    call [exit]
    
