; 3) Given the words A and B, compute the doubleword C as follows:
; - the bits 0-2 of C are the same as the bits 12-14 of A
; - the bits 3-8 of C are the same as the bits 0-5 of B
; - the bits 9-15 of C are the same as the bits 3-9 of A
; - the bits 16-31 of C are the same as the bits of A

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a dw 1100101000101110b
    b dw 1010011001011100b
    c dd 0
    
segment  code use32 class=code ; code segment
start: 
    mov ebx, 0 ; we compute the result in bx
    
    ; the bits 0-2 of C are the same as the bits 12-14 of A
    mov ax, [a] 
    and ax, 0111000000000000b
    mov cl, 12
    ror ax, cl 
    or bx, ax ; we put the bits into the result
    
    ; the bits 3-8 of C are the same as the bits 0-5 of B
    mov ax, [b]
    and ax, 0000000000111111b
    mov cl, 3
    rol ax, cl
    or bx, ax
    
    ; the bits 9-15 of C are the same as the bits 3-9 of A
    mov ax, [a]
    and ax, 0000001111111000b
    mov cl, 6
    rol ax, cl
    or bx, ax
    
    ; the bits 16-31 of C are the same as the bits of A
    mov edx, 0
    mov dx, [a]
    mov cl, 16
    rol edx, cl
    or ebx, edx
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program