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
    file_name db "prob_Cristi.txt", 0
    access_mode db "r", 0
    file_descriptor dd -1
    
    text db "abcdefghij", 0
    len equ 10
    nr times len db 0
    sir times (len + 1) db 0
    output db "output-i.txt", 0
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
        push dword nr
        call [fread]
        add esp, 4 * 4
        
        mov bl, [nr]
        sub bl, '0'
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        mov al, 0
        mov edx, 0
        mov edi, 9
        Repeta:
            mov esi, 0
            Repeta_out:
                mov ah, [output + esi]
                cmp ah, 'i'
                jne not_i
                    mov ah, '0'
                    add ah, al
                    mov [output + esi], ah
                    jmp aici
                    
                not_i:
                inc esi
                jmp Repeta_out
                
            aici:
            pushad
            
            push dword access_mode_out    
            push dword output
            call [fopen]
            add esp, 4*2
            
            popad
              
            mov cl, [text + edi]
            mov [sir + edx], cl
            inc edx
            dec edi
            
            pushad
                
            push dword sir
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4*2
            
            push dword [file_descriptor]
            call [fclose]
            add esp, 4
            
            popad
            
            mov ah, 'i'
            mov [output + esi], ah
            
            cmp al, bl
            je final
            
            inc al
            jmp Repeta
            
    
    final:
    
    push dword 0
    call [exit]
    
