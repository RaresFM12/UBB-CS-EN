; (c+d)-(a+d)+b
; (80 + 180) - (4+180)+300=260 - 184 + 300 = 76 + 300 = 376

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 4
    b dw 300
    c dd 80
    d dq 180
    
segment  code use32 class=code ; code segment
start: 
	mov eax, [c] ; eax = c
    mov edx, 0 ; transformam c in dq
    
    clc
    add eax, dword [d] 
    adc edx, dword [d+4] ; edx:eax = c + d
    
    mov bl, [a] ; bl = a
    mov bh, 0 ; transformam a in dw
    mov cx, 0 ; transformam a in dd
    
    push cx
    push bx
    pop ebx
    mov ecx, 0 ; transformam a in dq
    
    clc
    add ebx, dword [d] 
    adc ecx, dword [d+4] ; ecx:ebx = a + d
    
    clc
    sub eax, ebx 
    sbb edx, ecx ; edx:eax = (c+d)-(a+d)
    
    mov bx, [b]
    mov cx, 0 ; transformam b in dd
    
    push cx
    push bx
    pop ebx
    mov ecx, 0 ; transformam b in dq
    
    clc
    add eax, ebx
    adc edx, ecx ; edx:eax = (c+d)-(a+d)+b
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program