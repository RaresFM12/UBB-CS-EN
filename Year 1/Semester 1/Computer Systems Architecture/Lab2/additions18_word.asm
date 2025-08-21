; (a-b-c)+(a-c-d-d)
; (600-200-100)+(600-100-300-300)=300-100=200

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a dw 600
    b dw 200
    c dw 100
    d dw 300
    
segment  code use32 class=code ; code segment
start: 
	mov ax, [a] ; ax = a
    sub ax, [b] ; ax = ax - b
    sub ax, [c] ; ax = ax - c
    
    mov bx, [a] ; bx = a
    sub bx, [c] ; bx = bx - c
    sub bx, [d] ; bx = bx - d
    sub bx, [d] ; bx = bx - d
    
    add ax, bx ; ax = ax + bx
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
