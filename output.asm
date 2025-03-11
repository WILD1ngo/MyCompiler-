global _start 
    
section .bss
    buffer resb 100       ; Input buffer
    outbuffer resb 20     ; Output buffer for multi-digit numbers
    next resq 1
    cur resq 1
    temp resq 1
    index resq 1
    indexto resq 1

section .data
    newline db 10         ; Newline character

section .text 
_start: ; Read input 
call read_int


mov [indexto] , rax

mov rax, 1
mov [index] , rax

mov rax, 0
mov [cur] , rax

mov rax, 1
mov [next] , rax

loop:
mov rax , [cur]
call print_int_ln

mov rax , [next]
push rax
mov rax , [cur]
pop rbx
add rax, rbx
mov [temp] , rax

mov rax , [next]
mov [cur] , rax

mov rax , [temp]
mov [next] , rax

mov rax, 1
push rax
mov rax , [index]
pop rbx
add rax, rbx
mov [index] , rax

mov rax , [index]
push rax
mov rax , [indexto]
pop rbx
cmp rax, rbx

jge iflabel0

jmp end
iflabel0:
jmp loop
end:
 
    ; Exit
    mov rax, 60           ; sys_exit
    xor rdi, rdi          ; status 0
    syscall

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

