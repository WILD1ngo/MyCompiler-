#include "LexerFSM.h"

LexerFSM::LexerFSM()
{


    for (char c : {(char)13 , '\n' , ' '}) {
        _stateMap[CurrentState(State::START, c)] = State::START;
        _stateMap[CurrentState(State::IDENT, c)] = State::START;
        _stateMap[CurrentState(State::NUMBER, c)] = State::START;
        _stateMap[CurrentState(State::SYMBOL, c)] = State::START;
        _stateMap[CurrentState(State::LABEL, c)] = State::START;
    }

    
    // Identifier transitions
    for (char c = 'a'; c <= 'z'; ++c) {
        _stateMap[CurrentState(State::START, c)] = State::IDENT;
        _stateMap[CurrentState(State::IDENT, c)] = State::IDENT;
    }

    // Number transitions
    for (char c = '0'; c <= '9'; ++c) {
        _stateMap[CurrentState(State::START, c)] = State::NUMBER;
        _stateMap[CurrentState(State::NUMBER, c)] = State::NUMBER;
        _stateMap[CurrentState(State::IDENT, c)] = State::IDENT;
        
    }

      // Symbol transitions
      _stateMap[CurrentState(State::START, '=')] = State::SYMBOL;
      _stateMap[CurrentState(State::START, '+')] = State::SYMBOL;
      _stateMap[CurrentState(State::START, '<')] = State::SYMBOL;
      _stateMap[CurrentState(State::SYMBOL, '=')] = State::SYMBOL;



      // Label transitions
      _stateMap[CurrentState(State::IDENT, ':')] = State::LABEL;



}

State LexerFSM::get(State s, char cur)
{
    return _stateMap[CurrentState(s, cur)];
}
