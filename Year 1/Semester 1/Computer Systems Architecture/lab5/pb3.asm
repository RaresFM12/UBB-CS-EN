; S1: 1, 2, 3, 4
; S2: 5, 6, 7
; D: 1, 2, 3, 4, 7, 6, 5

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	s1 db 1, 2, 3, 4 
    l1 equ $-s1
    s2 db 5, 6, 7
    l2 equ $-s2
    d times (l1 + l2) db 0 
    
segment  code use32 class=code ; code segment
start: 
    mov ecx, l1
    mov esi, 0
    
    jecxz Sfarsit1
    Repeta1:
        mov al, [s1 + esi]
        mov [d + esi], al
        inc esi
    loop Repeta1
    Sfarsit1:
    
    mov ecx, l2
    mov esi, l2 - 1
    mov ebx, 0
    
    jecxz Sfarsit2
    Repeta2:
        mov al, [s2 + esi]
        mov [d + l1 + ebx], al
        inc ebx
        dec esi
    loop Repeta2
    Sfarsit2:
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program