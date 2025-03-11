#ifndef LexerFlag 
#define LexerFlag
#include "LexerFSM.h"
#include "Token.h"
#include <string>
#include <vector>






class Lexer
{
    public:
    Lexer(std::string);
    void print_tokens();
    std::vector<Token> get_tokens() { return _tokens; }
    private:
    void insert_token(std::string, token_type);

    LexerFSM _fsm;
    std::vector<Token> _tokens;
};


#endif