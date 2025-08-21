; (a+b*c+2/c)/(2+a)+e+x; a,b-byte; c-word; e-doubleword; x-qword
; (2+3*1+2/1)/(2+2)+5+7= 7/4+5+7=1+12=13

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 2
    b db 3
    c dw 1
    e dd 5
    x dq 7
    
segment  code use32 class=code ; code segment
start: 
    mov al, [b]
    mov ah, 0
    mov bx, [c]
    mul bx
    
    mov bx, ax
    mov cx, dx
    
    mov ax, 2
    mov dx, 0
    div word [c]
    mov dx, 0
    
    clc
    add ax, bx
    adc dx, cx
    
    mov bl, [a]
    mov bh, 0
    mov cx, 0
    
    clc
    add ax, bx
    adc dx, cx
    
    mov bl, [a]
    mov bh, 0
    add bx, 2
    div bx
    
    mov dx, 0
    mov bx, word [e]
    mov cx, word [e+2]
    
    clc
    add ax, bx
    adc dx, cx
    
    push dx
    push ax
    pop eax
    mov edx, 0
    
    mov ebx, dword [x]
    mov ecx, dword [x+4]
    
    clc
    add eax, ebx
    adc edx, ecx
    
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program