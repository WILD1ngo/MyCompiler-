#include "CodeGen.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "../Libs/print_int.h"
#include "../Libs/read_int.h"
#include "../Libs/end.h"
void CodeGen::generate_code()
{
    std::unordered_map<std::string, int> var_map;
    for (auto& node : _ast) {
        if (node->getVarDec() != "") {
            var_map[node->getVarDec()] = 1;
        }
    }
    
    Code +=R"(global _start 
    
section .bss
    buffer resb 100       ; Input buffer
    outbuffer resb 20     ; Output buffer for multi-digit numbers
)";
    for (auto& var : var_map) 
        Code += "    " + var.first + " resq 1\n";
    Code += R"(
section .data
    newline db 10         ; Newline character

section .text 
_start: )" ;

    for (auto& node : _ast) {
        Code += node->printCode() + "\n";
    }
    Code += end_program;
    Code += read_int;
    Code += print_int;
}


