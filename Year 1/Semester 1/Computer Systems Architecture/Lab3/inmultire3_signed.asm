; (8-a*b*100+c)/d+x; a,b,d-byte; c-doubleword; x-qword
; (8-2*-3*100+10)/(-2)+12 = (8+600+10)/(-2)+12=618/(-2)+12=-309+12=-297

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 2
    b db -3
    c dd 10
    d db -2
    x dq 12
    
segment  code use32 class=code ; code segment
start: 
    mov al, [a]
    imul byte [b]
    mov bl, 100
    imul bl ; ax = a*b*100
    cwd ; dx:ax = a*b*100
    
    mov bx, 8
    mov cx, 0
    
    clc
    sub bx, ax
    sbb cx, dx
    
    mov ax, word [c]
    mov dx, word [c+2]
    
    clc
    add ax, bx
    adc dx, cx ; (8-a*b*100+c)
    
    mov bx, ax
    mov cx, dx
    
    mov al, [d]
    cbw
    
    mov dx, ax
    mov ax, bx
    mov bx, dx
    mov dx, cx
    
    idiv bx ; (8-a*b*100+c)/d

    cwde
    cdq
    
    mov ebx, dword [x]
    mov ecx, dword [x+4]
    
    clc
    add eax, ebx
    adc edx, ecx     ; (8-a*b*100+c)/d+x
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program