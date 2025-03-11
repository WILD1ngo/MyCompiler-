#ifndef TOKEN_FLAG
#define TOKEN_FLAG
#include <string>
#include <iostream>


enum class State {
    INVALID,
    START,
    IDENT,
    NUMBER,
    SYMBOL,
    LABEL
};


enum class token_type
 {
    IDENT,
    LABEL,
    INT,
    INPUT,
    OUTPUT,
    GOTO,
    IF,
    THEN,
    EQUAL,
    SET,
    PLUS,
    LESS_THAN,
    INVALID,
    END
};


struct Token
{
    std::string value;
    token_type type;
    Token(std::string v, token_type t) : value(v), type(t) {}
};
#endif