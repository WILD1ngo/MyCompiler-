section .text
global _start

_start:
    ; Exit the program with status 0.
    mov     rax, 60       ; syscall number for exit
    mov     rdi, 69       ; exit status      
    syscall
