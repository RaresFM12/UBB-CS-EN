; 18) Given the word A, compute the doubleword B as follows:
; - the bits 0-3 of B have the value 0;
; - the bits 4-7 of B are the same as the bits 8-11 of A
; - the bits 8-9 and 10-11 of B are the invert of the bits 0-1 of A (so 2 times) ;
; - the bits 12-15 of B have the value 1
; - the bits 16-31 of B are the same as the bits 0-15 of B.

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a dw 1100101000101110b
    b dd 0
    
segment  code use32 class=code ; code segment
start:     
    ; the bits 0-3 of B have the value 0;
    mov ebx, 0 ; we compute the result in bx
    
    ; the bits 4-7 of B are the same as the bits 8-11 of A
    mov ax, [a]
    and ax, 0000111100000000b
    mov cl, 4
    ror ax, cl
    or bx, ax
    
    ; the bits 8-9 and 10-11 of B are the invert of the bits 0-1 of A (so 2 times) ;
    mov ax, [a]
    not ax
    and ax, 0000000000000011b
    mov cl, 8
    rol ax, cl
    or bx, ax
    mov cl, 2
    rol ax, cl
    or bx, ax
    
    ; the bits 12-15 of B have the value 1
    or bx, 1111000000000000b
    
    ; the bits 16-31 of B are the same as the bits 0-15 of B.
    mov edx, 0
    mov dx, bx
    mov cl, 16
    rol ebx, cl
    or ebx, edx
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program