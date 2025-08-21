; [-1+d-2*(b+1)]/a
; [-1+301-2*(99+1)]/50=(300-200)/50=100/50=2

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 50
    b db 99
    c db 40
    d dw 301
    
segment  code use32 class=code ; code segment
start: 
	mov ax, 2 ; ax = 2
    
    mov bl, [b] ; bl = b
    add bl, 1 ; bl = bl + 1
    ; mul -> inmulteste numerele mereu in ax
    mul bl
    
    mov bx, -1 ; bx = -1
    add bx, [d] ; bx = bx + d
    
    sub bx, ax ; bx = bx - ax
    
    mov ax, bx ; ax = bx
    ; div -> impartirea mereu in ax
    div byte [a] ; ax = ax / a
    
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
