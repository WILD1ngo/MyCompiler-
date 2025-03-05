#ifndef LexerFlag 
#define LexerFlag
#include "LexerFSM.h"
#include "Token.h"
#include <string>
#include <vector>


struct Token
{
    std::string value;
    token_type type;
    Token(std::string v, token_type t) : value(v), type(t) {}
};



class Lexer
{
    public:
    Lexer(std::string);
    void print_tokens();
    private:
    void insert_token(std::string, token_type);

    LexerFSM _fsm;
    std::vector<Token> _tokens;
};


#endif