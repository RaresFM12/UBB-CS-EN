; f+(c-2)*(3+a)/(d-4)
; 350+(7-2)*(3+12)/(19-4)=350+5*15/15=355


bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db 12
    b db 176
    c db 7
    d db 19
    e dw 300
    f dw 350
    g dw 400
    h dw 100
    
segment  code use32 class=code ; code segment
start: 
	mov al, [c] ; al = c
    sub al, 2 ; al = al - 2
    
    mov bl, 3 ; bl = 3
    add bl, [a] ; bl = bl + a
    mul bl ; ax = al * bl
    
    mov bl, [d] ; bl = d
    sub bl, 4 ; bl = bl - 4
    div bl ; ax = ax / bl
    
    mov bx, [f] ; bx = f
    add bx, ax ; bx = bx + ax
       
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program
