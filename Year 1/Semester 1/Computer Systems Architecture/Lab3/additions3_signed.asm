; (b+b+d)-(c+a)
; (-200-200-180)-(-80-4)=(-400-180)-(-84)=-580+84=-496

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db -4
    b dw -200
    c dd -80
    d dq -180
    
segment  code use32 class=code ; code segment
start: 
	mov ax, [b]
    mov bx, [b]
    
    add ax, bx ; b + b
    cwde
    cdq
    
    clc
    add eax, dword [d]
    adc edx, dword [d+4] ; b + b + d
    
    mov ebx, eax
    mov ecx, edx ; salvam b+b+d in ecx:ebx
    
    mov al, [a]
    cbw
    cwde
    add eax, [c] ; c+a
    cdq
    
    clc
    sub ebx, eax
    sbb ecx, edx ; (b+b+d)-(c+a)
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program