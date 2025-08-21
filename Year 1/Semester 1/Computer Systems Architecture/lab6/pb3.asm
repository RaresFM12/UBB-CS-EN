; 0702090Ah, 0B0C0304h, 05060108h    
; 72h, 9Ah, 0BCh,  34h, 56h, 18h
; 9Ah, 0BCh, 18h, 34h, 56h, 72h

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	s dd 0702090Ah, 0B0C0304h, 05060108h
    len equ ($-s) / 4
    a times (len * 2) db 0
    fin times (len * 2) db 0
    
segment  code use32 class=code ; code segment
start: 
    mov ecx, len
    mov esi, s
    mov ebx, 0
    cld
    
    jecxz Sfarsit1
        Repeta:
            lodsd
            ror eax, 16
            or [a + ebx], al
            ror eax, 4
            or [a + ebx], al
            
            inc ebx
            ror eax, 12
            or [a + ebx], al
            ror eax, 4
            or [a + ebx], al
            
            inc ebx
        loop Repeta
    Sfarsit1:
    
    mov ebx, 0
    Repeta1:
        cmp ebx, (len * 2)
        jz fin_sir1
        
        mov eax, ebx
        inc eax
        
        Repeta2:
            cmp eax, (len * 2)
            jz fin_sir2
            
            mov dl, [a + ebx]
            mov cl, [a + eax]
            cmp dl, cl
            jle mic_egal
                mov [a + ebx], cl
                mov [a + eax], dl
            mic_egal:
        
            inc eax
            jmp Repeta2
            
        fin_sir2:
        inc ebx
        jmp Repeta1
        
    fin_sir1:
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program