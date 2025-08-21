bits 32
global start

import printf msvcrt.dll
import exit msvcrt.dll
import scanf msvcrt.dll
extern printf, exit, scanf

extern cifre

segment data use32
    s1 db "Ana are 12 mere si 15 pere", 0
    s2 db "Mara are 44 de ani si conduce de 20 de ani", 0 
    format_string2 db "%s", 10, 0
    nr1 resb 100
    nr2 resb 100

segment code use32 public code
start:
    ; nr 1
	push dword s1
    push dword nr1
    call cifre
    
    lea eax, [nr1 + edx]
    push dword s2
    push dword eax
    call cifre
    
    push dword nr1
    push dword format_string2
    call [printf]
    add esp, 4 * 2
    
    ; nr 2
    push dword s2
    push dword nr2
    call cifre
    
    lea eax, [nr2 + edx]
    push dword s1
    push dword eax
    call cifre
    
    push dword nr2
    push dword format_string2
    call [printf]
    add esp, 4 * 2
    
	push 0
	call [exit]
