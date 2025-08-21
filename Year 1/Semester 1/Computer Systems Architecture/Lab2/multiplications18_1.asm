; 200-[3*(c+b-d/a)-300]
; 200-[3*(24+176-300/3)-300]=200-(3*100-300)=200

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 3
    b db 176
    c db 24
    d dw 300
    
segment  code use32 class=code ; code segment
start: 
	mov ax, [d] ; ax = d
    div byte [a] ; al = ax / a
    
    mov bl, [c] ; bl = c
    add bl, [b] ; bl = bx + b
    sub bl, al ; bl = bl - al
    
    mov ax, 3 ; ax = 3
    mul bl ; ax = ax * bl
    sub ax, 300 ; ax = ax - 300
    
    mov bx, 200 ; bx = 200
    sub bx, ax ; bx = bx - ax
    
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
