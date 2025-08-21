; (d+d)-a-b-c
; (180 +180) - 4 - 200 - 80 = 360 - 4 - 200 - 80 = 76

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 4
    b dw 200
    c dd 80
    d dq 180
    
segment  code use32 class=code ; code segment
start: 
	mov eax, dword [d] 
    mov edx, dword [d+4] ; edx:eax = d
    
    mov ebx, dword [d]
    mov ecx, dword [d+4] ; ecx:ebx = d
    
    clc
    add eax, ebx
    adc edx, ecx ; edx:eax = d + d
    
    mov bl, [a]
    mov bh, 0 ; transformam a in dw
    mov cx, 0 ; transformam a in dd
    
    push cx
    push bx
    pop ebx
    mov ecx, 0 ; transformam a in dq
    
    clc
    sub eax, ebx
    sbb edx, ecx ; (d+d)-a
    
    mov bx, [b]
    mov cx, 0 ; b -> dd
    
    push cx
    push bx
    pop ebx
    mov ecx, 0 ; b -> dq
    
    clc
    sub eax, ebx
    sbb edx, ecx ; (d+d)-a-b
    
    mov ebx, [c]
    mov ecx, 0 ; c -> dq
    
    clc
    sub eax, ebx
    sbb edx, ecx ; (d+d)-a-b-c
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program