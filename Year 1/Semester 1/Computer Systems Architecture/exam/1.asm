bits 32
global start

extern exit
import exit msvcrt.dll

extern fopen, fprintf, fclose
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    n db 11, 2, 3 
    c db 12, 43, 32, 22
    
segment code use32 class=code
start:
    mov dh, 200
    mov ch, 62h
    sub dh, ch
    
    push dword 0
    call [exit]
    

