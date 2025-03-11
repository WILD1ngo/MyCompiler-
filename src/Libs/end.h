#ifndef END_H
#define END_H


const char* end_program = R"( 
    ; Exit
    mov rax, 60           ; sys_exit
    xor rdi, rdi          ; status 0
    syscall
)"; 
#endif