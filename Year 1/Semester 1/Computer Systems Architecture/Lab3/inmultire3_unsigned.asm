; (8-a*b*100+c)/d+x; a,b,d-byte; c-doubleword; x-qword
; (8-2*3*100+1000)/2+12 = (8-600+1000)/2+12=408/2+12=204+12=216

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 2
    b db 3
    c dd 1000
    d db 2
    x dq 12
    
segment  code use32 class=code ; code segment
start: 
    mov al, [a] ; al = a
    mul byte [b]
    mov bl, 100
    mul bl
    
    mov dx, 0
    mov bx, 8
    mov cx, 0
    
    clc
    sub bx, ax
    sbb cx, dx
    
    mov ax, word [c]
    mov dx, word [c+2]
    
    clc
    add ax, bx
    adc dx, cx
    
    mov bl, [d]
    mov bh, 0
    div bx
    
    mov dx, 0
    push dx
    push ax
    pop eax
    mov edx, 0
    
    mov ebx, dword [x]
    mov ecx, dword [x+4]
    
    clc
    add eax, ebx
    add edx, ecx
    
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program