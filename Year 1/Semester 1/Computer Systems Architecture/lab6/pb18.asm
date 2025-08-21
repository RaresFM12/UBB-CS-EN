; 12AB5678h, 1256ABCDh, 12344344h 
; 12345678h, 1256ABCDh, 12AB4344h.

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	sir dd 12AB5678h, 1256ABCDh, 12344344h 
    len equ ($-sir) / 4
    hw times len dw 0
    
segment  code use32 class=code ; code segment
start: 
    mov esi, sir
    mov ecx, len
    mov ebx, 0
    cld
    
    jecxz sf
        Repeta:
            lodsd
            ror eax, 16
            
            mov [hw + ebx], ax
            add ebx, 2
            
        loop Repeta
    sf:
    
    mov ebx, 0
    Repeta1:
        cmp ebx, len
        jz fin_sir1
        
        mov eax, ebx
        inc eax
        
        Repeta2:
            cmp eax, len
            jz fin_sir2
            
            mov dx, [hw + ebx * 2]
            mov cx, [hw + eax * 2]
            cmp dx, cx
            jle mic_egal
                mov [hw + ebx * 2], cx
                mov [hw + eax* 2], dx
            mic_egal:
        
            inc eax
            jmp Repeta2
            
        fin_sir2:
        inc ebx
        jmp Repeta1
        
    fin_sir1:
    
    mov ebx, 0
    mov esi, sir
    mov ecx, len
    cld
    
    jecxz Sfarsit
        Repeta3:
            lodsd
            ror eax, 16
            and ax, 0000h
            or ax, [hw + ebx * 2]
            ror eax, 16
            
            mov [sir + ebx * 4], eax
            inc ebx
        loop Repeta3
    Sfarsit:
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program