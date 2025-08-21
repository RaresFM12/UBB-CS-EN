; (a+b*c+2/c)/(2+a)+e+x; a,b-byte; c-word; e-doubleword; x-qword
; (-1+2*-2+2/-2)/(2-1)+5+7 = (-1-4-1)/1+5+7=-6+5+7=6

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db -1
    b db 2
    c dw -2
    e dd 5
    x dq 7
    
segment  code use32 class=code ; code segment
start: 
    mov al, [b]
    cbw 
    imul word [c]
    
    mov bx, ax
    mov cx, dx ; cx:bx = b*c
    
    mov ax, 2
    mov dx, 0
    idiv word [c]
    cwd
    
    clc
    add bx, ax
    adc cx, dx
    
    mov al, [a]
    cbw
    cwd
    
    clc
    add bx, ax
    adc cx, dx ; (a+b*c+2/c)
    
    mov al, [a]
    cbw
    add ax, 2
    
    mov dx, ax
    mov ax, bx
    mov bx, dx
    mov dx, cx
    
    idiv bx ; (a+b*c+2/c)/(2+a)
    cwde
    
    mov ebx, [e]
    add eax, ebx
    
    cdq
    mov ebx, dword [x]
    mov ecx, dword [x+4]
    
    clc
    add eax, ebx
    adc edx, ecx ; (a+b*c+2/c)/(2+a)+e+x
    
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program