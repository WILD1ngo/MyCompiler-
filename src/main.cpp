#include "Utils/FileHandeler.h"
#include "LexicalAnalysis/Lexer.h"
#include <iostream>
#include <string>

int main() {

    std::string input = read_input();
    std::cout << input << std::endl;
    Lexer lexer(input);
    std::cout << "Tokens: " << std::endl;
    lexer.print_tokens();
}