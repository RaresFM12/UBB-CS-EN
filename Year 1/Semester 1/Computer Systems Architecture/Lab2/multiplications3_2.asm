; (e+f)*g
; (300+350)*400=260.000


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
    d db 300
    e dw 300
    f dw 350
    g dw 400
    h dw 100
    
segment  code use32 class=code ; code segment
start: 
	mov ax, [g] ; ax = g
    mov bx, [e] ; bx = e
    add bx, [f] ; bx = bx + f
    
    mul bx
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
