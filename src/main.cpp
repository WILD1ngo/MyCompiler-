#include "Utils/FileHandeler.h"
#include "LexicalAnalysis/Lexer.h"
#include "SyntaxAnalysis/Parser.h"
#include "CodeGeneration/CodeGen.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    
    std::string input = read_input(argc, argv);
    std::cout << "Compiling ... The Code " << std::endl;
    std::cout << input ;
    Lexer lexer(input);
    std::cout << "Tokens: " << std::endl;
    lexer.print_tokens();
    Parser parser(lexer.get_tokens());
    CodeGen codegen(parser.getAst());
    write_output(codegen.getCode(), "output.asm");

}