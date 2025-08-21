bits 32
global start

import printf msvcrt.dll
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
extern printf, exit, scanf, fopen, fclose, fprintf

;extern minimul

segment data use32
    file_name db "min.txt", 0
    access_mode db "w", 0
    file_descriptor db -1
    
    format_display1 db "%d", 0
    format_display2 db "%x", 0
    format_read1 db "%d", 0
    format_read2 db "%c", 0
    list db 100
    text db "Ana are multe mere", 0

segment code use32 public code
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
    
start:
    mov esi, 0
    Repeta:
        lea edi, [list + esi]
        push dword edi
        push dword format_read1
        call [scanf]
        add esp, 4 * 2
        inc esi
        
        lea edi, [list + esi]
        push dword edi
        push dword format_read2
        call [scanf]
        add esp, 4 * 2

        mov bl, [list + esi]
        cmp bl, 10
        jz Sfarsit
        
        inc esi
        jmp Repeta
    
    Sfarsit:
    
    mov ebx, 0
    push dword list
    call minimul   ; merge
    
    push dword access_mode     
    push dword file_name
    call [fopen]
    add esp, 4*2
    
    mov [file_descriptor], eax
    
    cmp eax, 0
    je finalul
        ; write the text to file using fprintf()
        ; fprintf(file_descriptor, text)
        push dword ebx
        push dword format_display2
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

    finalul:
    
	push 0
	call [exit]
