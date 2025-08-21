; (d-b)-a-(b-c)
; (-180+200)+4-(-200+80)=20+4-(-120)=24+120=144

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a db -4
    b dw -200
    c dd -80
    d dq -180
    
segment  code use32 class=code ; code segment
start: 
    mov ebx, dword [d]
    mov ecx, dword [d+4] 
    
    mov ax, [b]
    cwde
    cdq
    
    clc
    sub ebx, eax
    sbb ecx, edx ; (d-b)
    
    mov al, [a]
    cbw
    cwde
    cdq
    
    clc
    sub ebx, eax
    sbb ecx, edx ; (d-b)-a
    
    mov ax, [b]
    cwde
    sub eax, [c] ; (b-c)
    cdq
    
    clc
    sub ebx, eax
    sbb ecx, edx ; (d-b)-a-(b-c)
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of
;the program