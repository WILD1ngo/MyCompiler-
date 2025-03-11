#ifndef PRINT_INT_H
#define PRINT_INT_H

const char* print_int = R"(
; -------------------------------
; print_int - Prints a 64-bit integer to stdout
; Input: RAX = the integer to print
; Output: None
; Clobbers: RAX, RCX, RDX, RSI, RDI
; -------------------------------
print_int:
    ; Save used registers
    push rax
    push rbx
    
    ; Convert integer to string for printing
    mov rcx, outbuffer    ; RCX points to output buffer
    mov rbx, 10           ; Base 10 for division
    
    ; Special case for zero
    test rax, rax
    jnz .convert_loop
    mov byte [rcx], '0'   ; Just store '0'
    inc rcx
    jmp .print_num
    
.convert_loop:
    xor rdx, rdx          ; Clear RDX for division
    div rbx               ; Divide RAX by 10, remainder in RDX
    add dl, '0'           ; Convert remainder to ASCII
    mov [rcx], dl         ; Store digit
    inc rcx               ; Move to next position
    
    test rax, rax         ; Check if quotient is zero
    jnz .convert_loop     ; If not, continue
    
    ; Calculate length of string
    mov rdx, rcx
    sub rdx, outbuffer    ; RDX = length of string
    
.print_num:
    ; Print the number
    mov rax, 1            ; sys_write
    mov rdi, 1            ; stdout
    mov rsi, outbuffer    ; buffer
    syscall
    
    ; Restore registers
    pop rbx
    pop rax
    ret

; -------------------------------
; print_int_ln - Prints a 64-bit integer followed by newline
; Input: RAX = the integer to print
; Output: None
; Clobbers: RAX, RCX, RDX, RSI, RDI
; -------------------------------
print_int_ln:
    ; Save registers
    push rax
    
    ; Print the integer
    call print_int
    
    ; Print newline
    mov rax, 1            ; sys_write
    mov rdi, 1            ; stdout
    mov rsi, newline      ; newline character
    mov rdx, 1            ; length
    syscall
    
    ; Restore registers
    pop rax
    ret

)";

#endif