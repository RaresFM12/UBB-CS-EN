; Two natural numbers a and b (a, b: dword, defined in the data segment) are given. 
; Calculate their sum and display the result in the following format: "<a> + <b> = <result>". Example: "1 + 2 = 3"
; The values will be displayed in decimal format (base 10) with sign.

bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
	a dd 0
    b dd 0
    text db "%d", 0
    message1 db "a = ", 0
    message2 db "b = ", 0
    formatd db "%d", 0
    formath db "%x", 0
    
    
segment code use32 class=code
    start:
       push dword message1
       call [printf]
       add esp, 4
       
       push dword a
       push dword formatd
       call [scanf]
       add esp, 4 * 2
       
       push dword message2
       call [printf]
       add esp, 4
        
       push dword b
       push dword formath
       call [scanf]
       add esp, 4 * 2
       
       mov eax, 0
       add eax, [a]
       add eax, [b]
       
       mov ecx, 0
       cmp eax, 0
       je sfarsit1
           Repeta:
               test eax, 1
               jz even
                   inc ecx
               
               even:
           
               shr eax, 1
               cmp eax, 0
               jz sfarsit2
               jmp Repeta
               
       sfarsit1:
       sfarsit2:
       
       push dword ecx
       push dword text
       call [printf]
       add esp, 4 * 2
       
       ; exit(0)
       push dword 0      ; place on stack parameter for exit
       call [exit]       ; call exit to terminate the program