; (c+d)-(a+d)+b
; (5+7)-(3+7)+4=12-10+4=6

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 3
    b db 4
    c db 5
    d db 7
    
segment  code use32 class=code ; code segment
start: 
	mov al, [c] ; ax = c
    add al, [d] ; ax = ax + d
    mov ah, [a] ; ah = a
    add ah, [d] ; ah = ah + d
    
    sub al, ah ; al = al - ah
    add al, [b] ; al = al + b
	
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
