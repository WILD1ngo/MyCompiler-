#ifndef CodeGenFlag
#define CodeGenFlag
#include <vector>
#include <memory>
#include "../SyntaxAnalysis/Ast.h"

class CodeGen
{
public:
    CodeGen(std::vector<std::unique_ptr<node>> ast) : _ast(std::move(ast)) { generate_code(); }
    

    std::string getCode() { return Code; }

private:
    void generate_code();
    std::string Code;
    std::vector<std::unique_ptr<node>> _ast;
    
};

#endif