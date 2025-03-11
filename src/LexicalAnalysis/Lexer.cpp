#include "Lexer.h"
#include "statetotoken.h"
#include <iostream>
Lexer::Lexer(std::string untokenized_string)
{
    State _current_state = State::START;
    token_type _current_token_type = token_type::INVALID;
    std::string _current_token = "";
    int line_number = 1;
    for (char c : untokenized_string) {
        if (c == '\n') line_number++;
        const State next_state = _fsm.get(_current_state, c);
        if(next_state == State::INVALID) { 
            std::cerr << "Invalid character: " << (int)c << " ; At Line: " << line_number<< std::endl;
            exit(1);
        }
        if (end_of_token(_current_state, next_state)) {
            _current_token_type = state_to_token(_current_state, _current_token);
            
            insert_token(_current_token, _current_token_type);
            _current_token = "";
            
        }
        _current_state = next_state;
        if (_current_state != State::START) _current_token += c;
    }
    insert_token("-1", token_type::END);
}

bool end_of_token(State _current_state ,State next_state)
{
    return (next_state == State::START &&_current_state != State::START )
    || (next_state == State::SYMBOL && _current_state == State::NUMBER)
    || (next_state == State::NUMBER && _current_state == State::SYMBOL)
    || (next_state == State::SYMBOL && _current_state == State::IDENT)
     || (next_state == State::IDENT && _current_state == State::SYMBOL);
}
void Lexer::print_tokens()
{
    for (Token t : _tokens) {
        std::cout << t.value << ' ' << (int)t.type << std::endl;
    }
}

void Lexer::insert_token(std::string value, token_type type)
{
    _tokens.emplace_back(value, type);
}
