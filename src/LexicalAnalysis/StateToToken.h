#ifndef StateToTokenFlag 
#define StateToTokenFlag
#include <unordered_map>
#include "Token.h"
#include <string>


token_type identifier_to_token(std::string value)
{
    std::unordered_map<std::string, token_type> identifier_to_token_map = {
        {"input", token_type::INPUT},
        {"output", token_type::OUTPUT},
        {"goto", token_type::GOTO},
        {"if", token_type::IF},
        {"then", token_type::THEN},
        
    };

    return ((bool)identifier_to_token_map[value]) ? identifier_to_token_map[value] : token_type::IDENT;
    
}

std::unordered_map<std::string, token_type> symbol_to_token_map = {
    {"=", token_type::SET},
    {"+", token_type::PLUS},
    {"<", token_type::LESS_THAN},
    {"==", token_type::EQUAL}
    
};
token_type symbol_to_token(std::string value)
{
    

    return symbol_to_token_map[value];
    
}



token_type state_to_token(State s , std::string value)
{
    if (s == State::IDENT) return identifier_to_token(value);
    if (s == State::SYMBOL) return symbol_to_token(value);

    
    std::unordered_map<State, token_type> state_to_token_map = {
        {State::LABEL, token_type::LABEL},
        {State::NUMBER, token_type::INT},
        {State::START, token_type::INVALID}
    };

    return state_to_token_map[s];
}


#endif