#ifndef ParseFSMFlag
#define ParseFSMFlag
#include <unordered_map>
#include "../LexicalAnalysis/Token.h"
#include <tuple>
#include <functional>
#include <stack>
#include "Ast.h"

enum class stack_instruction
{
    SHIFT,    // Push token onto stack and go to next state
    REDUCE,   // Apply reduction rule
    ACCEPT,   // Accept the input
    ERROR     // Error state
};

struct TupleHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::tuple<T1, T2>& tup) const {
        auto h1 = std::hash<T1>{}(std::get<0>(tup));
        auto h2 = std::hash<T2>{}(std::get<1>(tup));
        return h1 ^ (h2 << 1);
    }
};



// Reduction rule identification
enum class reduction_rule {
    R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13
};

// Reduction rule identification
enum class objects {
    instractions, instr, rel, expr, term , null
};

// Action for parser state machine
struct ParserAction {
    stack_instruction action;
    int next_state;
    reduction_rule rule;  // Only used if action is REDUCE
    
    // Constructor for SHIFT actions
    ParserAction(int state) : action(stack_instruction::SHIFT), next_state(state), rule(reduction_rule::R1) {}
    
    // Constructor for REDUCE actions
    ParserAction(reduction_rule r) : action(stack_instruction::REDUCE), next_state(-1), rule(r) {}
    
    // Constructor for ACCEPT action
    ParserAction() : action(stack_instruction::ACCEPT), next_state(-1), rule(reduction_rule::R1) {}
    
    // Constructor for ERROR action
    ParserAction(stack_instruction a, int state, reduction_rule r) : action(a), next_state(state), rule(r) {}
};

class ParserSLR
{
public:
    ParserSLR();
    
    // Get action for current state and token
    ParserAction getAction(int state, token_type token);
    
    // Get goto state after reduction
    int getGoto(int state, objects non_terminal);
    
    

private:
    // Map from (state, token) to action
    std::unordered_map<std::tuple<int, token_type>, ParserAction, TupleHash> _actionTable;
    
    // Map from (state, non-terminal) to next state
    std::unordered_map<std::tuple<int, objects>, int, TupleHash> _gotoTable;
    
    // Initialize the action table based on LSR table
    void initializeActionTable();
    
    // Initialize the goto table based on LSR table
    void initializeGotoTable();
};
#endif