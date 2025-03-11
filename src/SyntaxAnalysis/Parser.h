#ifndef ParserFlag
#define ParserFlag
#include "Ast.h"
#include <vector>
#include "ParserSLR.h"
#include "../LexicalAnalysis/Token.h"

class Parser 
{
public:
    Parser(std::vector<Token> tokens) : _tokens(tokens) { build_ast(); }
    
    void build_ast();
    
    // Get the final AST
    std::vector<std::unique_ptr<node>> getAst();
    
private:

    int getReductionSize(reduction_rule rule);
    std::unique_ptr<node> AllocateAST(Token tok);
    std::vector<Token> _tokens;
    std::stack<std::unique_ptr<node>> ast_stack;
    ParserSLR _slr;
    
    
};
#endif