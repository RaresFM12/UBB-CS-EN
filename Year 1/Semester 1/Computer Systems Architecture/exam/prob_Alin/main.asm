bits 32
global start

extern cerinta
extern exit
import exit msvcrt.dll
extern printf
import printf msvcrt.dll

segment data use32
    sir db 2Fh, 15h, 13h, 61h, 0CDh, 26h
    len db $ - sir
    
    format db "%x", 0
    
segment code use32 public code
start:
    mov ecx, 0
    mov cl, [len]
    push dword ecx
    push dword sir
    call cerinta
    add esp, 4 * 2
    
    push dword eax
    push dword format
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]