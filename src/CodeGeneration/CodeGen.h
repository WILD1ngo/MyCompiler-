#ifndef CodeGenFlag
#define CodeGenFlag
#include <vector>
#include <memory>
#include "../SyntaxAnalysis/Ast.h"

class CodeGen
{
public:
    CodeGen(std::vector<std::unique_ptr<node>> ast) : _ast(std::move(ast)) { generate_code(); }
    

    

private:
    void generate_code();
    std::vector<std::unique_ptr<node>> _ast;
    std::string Include(char* file);
};

#endif