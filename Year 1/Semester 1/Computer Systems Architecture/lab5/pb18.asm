; A: 2, 1, 3, -3
; B: 4, 5, -5, 7
; R: 1, 3, 5, 7

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 2, 1, 3, -3
    l1 equ $-a
    b db 4, 5, -5, 7
    l2 equ $-b
    d times (l1 + l2) db 0 
    
segment  code use32 class=code ; code segment
start: 
    mov ecx, l1
    mov esi, 0
    mov ebx, 0
    
    jecxz Sfarsit1
    Repeta1:
        mov al, [a + esi]
        
        cmp al, 0    
        jle neg1
            test al, 1
            jz even1
                mov [d + ebx], al
                inc ebx
            even1:
        neg1:
        
        inc esi
    loop Repeta1
    Sfarsit1:
    
    mov ecx, l2
    mov esi, 0
    
    jecxz Sfarsit2
    Repeta2:
        mov al, [b + esi]
        
        cmp al, 0
        jle neg2
            test al, 1
            jz even2
                mov [d + ebx], al
                inc ebx
            even2:
        neg2:
        
        inc esi
    loop Repeta2
    Sfarsit2:
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program