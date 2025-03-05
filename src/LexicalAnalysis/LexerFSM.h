#ifndef LexerFSMFlag 
#define LexerFSMFlag
#include <unordered_map>
#include "Token.h"

struct CurrentState
{
    /* data */
    State state;
    char cur_char;
    CurrentState(State s, char c) : state(s), cur_char(c) {}

     // Required for unordered_map keys: equality check
    bool operator==(const CurrentState& other) const {
        return state == other.state && cur_char == other.cur_char;
    }
};


// Specialize std::hash for CurrentState
namespace std {
    template<>
    struct hash<CurrentState> {
        size_t operator()(const CurrentState& cs) const noexcept {
            // Combine hashes of state and cur_char
            size_t h1 = hash<State>{}(cs.state);
            size_t h2 = hash<char>{}(cs.cur_char);  // Use cur_char (your member name)
            return h1 ^ (h2 << 1);
        }
    };
}


class LexerFSM
{

    public:
    LexerFSM();

    State get(State, char);

    private:



    std::unordered_map<CurrentState, State> _stateMap;

};


#endif