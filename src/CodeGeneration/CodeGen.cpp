#include "CodeGen.h"
#include <iostream>
#include <fstream>
#include "../Libs/print_int.h"
#include "../Libs/read_int.h"
#include "../Libs/end.h"
void CodeGen::generate_code()
{
    std::cout <<R"(global _start 
    
section .bss
    buffer resb 100       ; Input buffer
    outbuffer resb 20     ; Output buffer for multi-digit numbers
    n resq 1              ; 64-bit integer for input
    i resq 1              ; 64-bit integer for counter

section .data
    newline db 10         ; Newline character

section .text 
_start: )" << std::endl;
    for (auto& node : _ast) {
        std::cout << node->printCode() << std::endl;
    }
    std::cout << end_program;
    std::cout << read_int;
    std::cout << print_int;
}
