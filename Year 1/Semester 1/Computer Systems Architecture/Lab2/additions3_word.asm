; (b+b+d)-(c+a)
; (300+300+500)-(400+200)=1100-600=500

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a dw 200
    b dw 300
    c dw 400
    d dw 500
    
segment  code use32 class=code ; code segment
start: 
	mov ax, [b] ; ax = b
    add ax, [b] ; ax = ax + b
    add ax, [d] ; ax = ax + d
    
    mov bx, [c] ; bx = c
    add bx, [a] ; bx = bx + a
    
    sub ax, bx ; ax = ax - bx
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
