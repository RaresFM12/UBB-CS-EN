; d-(a+b)+c
; 7-(5+2)+1=7-7+1=1

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 5
    b db 2
    c db 1
    d db 7
    
segment  code use32 class=code ; code segment
start: 
	mov al, [d] ; al = d
    mov ah, [a] ; ah = a
    add ah, [b] ; ah = ah + b
    sub al, ah ; al = al - ah
    add al, [c] ; al = al + c
	
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
