#ifndef READ_INT_H
#define READ_INT_H


// read_int - Reads a 64-bit integer from stdin
// Input: None
// Output: RAX = the integer read
// Clobbers: RCX, RDX, RSI, RDI
// -------------------------------
char* read_int = R"(
; -------------------------------
; read_int - Reads a 64-bit integer from stdin
; Input: None
; Output: RAX = the integer read
; Clobbers: RCX, RDX, RSI, RDI
; -------------------------------
read_int:
    ; Save used registers
    push rbx
    
    ; Read input from stdin
    mov rax, 0            ; sys_read
    mov rdi, 0            ; stdin
    mov rsi, buffer       ; buffer
    mov rdx, 100          ; max length
    syscall

    ; Parse input to 64-bit integer
    mov rcx, 0            ; Set counter to 0 (for buffer index)
    mov rax, 0            ; Clear RAX for result

.parse_loop:
    movzx rdx, byte [buffer + rcx]  ; Get current character
    cmp rdx, 10           ; Check for newline
    je .parse_done        ; If newline, parsing is done
    cmp rdx, 0            ; Check for null terminator
    je .parse_done        ; If null, parsing is done
    cmp rdx, ' '          ; Check for space
    je .parse_done        ; If space, parsing is done
    
    sub rdx, '0'          ; Convert ASCII to number
    imul rax, 10          ; Multiply current result by 10
    add rax, rdx          ; Add new digit
    
    inc rcx               ; Move to next character
    jmp .parse_loop       ; Continue parsing
    
.parse_done:
    ; Restore registers
    pop rbx
    ret
)";

#endif