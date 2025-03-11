#include "Utils/FileHandeler.h"
#include "LexicalAnalysis/Lexer.h"
#include "SyntaxAnalysis/Parser.h"
#include "CodeGeneration/CodeGen.h"
#include <iostream>
#include <string>

int main() {

    
    std::string input = read_input();
    std::cout << "Compiling ... The Code " << std::endl;
    //std::cout << input << std::endl;
    Lexer lexer(input);
    std::cout << "Tokens: " << std::endl;
    //lexer.print_tokens();
    Parser parser(lexer.get_tokens());
    CodeGen codegen(parser.getAst());
    
}