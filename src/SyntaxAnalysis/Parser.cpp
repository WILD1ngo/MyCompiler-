#include "Parser.h"
#include "../LexicalAnalysis/Token.h"
#include <stack>

#include <stack>
#include <memory>
#include <iostream>
#include <algorithm>

objects reduce(reduction_rule rule, std::stack<std::unique_ptr<node>>* ast_stack)
{
    switch (rule) {
        case reduction_rule::R1:
            return objects::instractions;
        case reduction_rule::R2:
            return objects::instractions;
        case reduction_rule::R3: {
            if (ast_stack->size() < 3) return objects::null;
            
            // Pop the top three nodes from the stack
            std::unique_ptr<node> value = std::move(ast_stack->top());
            ast_stack->pop();
            
            std::unique_ptr<node> mid_node = std::move(ast_stack->top());
            ast_stack->pop();
            
            std::unique_ptr<node> source = std::move(ast_stack->top());
            ast_stack->pop();
            
            // Cast the nodes to their specific types
            auto* mid_ptr = dynamic_cast<assign_node*>(mid_node.release());
            if (!mid_ptr) return objects::null; // Safety check
            std::unique_ptr<assign_node> mid(mid_ptr);
            
            auto* src_ptr = dynamic_cast<var_node*>(source.release());
            if (!src_ptr) return objects::null; // Safety check
            std::unique_ptr<var_node> src(src_ptr);
            
            auto* val_ptr = dynamic_cast<expression_node*>(value.release());
            if (!val_ptr) return objects::null; // Safety check
            std::unique_ptr<expression_node> val(val_ptr);
            
            // Set source and value for the assignment node
            mid->set_source(std::move(src));
            mid->set_value(std::move(val));
            
            // Push the completed assignment node back onto the stack
            ast_stack->push(std::move(mid));
            return objects::instr;
        }
        case reduction_rule::R4:{
            if (ast_stack->size() < 4) return objects::null;
            
            // Pop the top three nodes from the stack
            std::unique_ptr<node> instr = std::move(ast_stack->top());
            ast_stack->pop();
            ast_stack->pop();
            
            std::unique_ptr<node> condi = std::move(ast_stack->top());
            ast_stack->pop();
            
            std::unique_ptr<node> ifptr = std::move(ast_stack->top());
            ast_stack->pop();
            
            // Cast the nodes to their specific types
            auto* temp = dynamic_cast<if_node*>(ifptr.release());
            if (!temp) return objects::null; // Safety check
            std::unique_ptr<if_node> ifNode(temp);
            
            auto* src_ptr = dynamic_cast<condition_node*>(condi.release());
            if (!src_ptr) return objects::null; // Safety check
            std::unique_ptr<condition_node> conditionNode(src_ptr);
            
            auto* val_ptr = dynamic_cast<instraction_node*>(instr.release());
            if (!val_ptr) return objects::null; // Safety check
            std::unique_ptr<instraction_node> val(val_ptr);
            
            // Set source and value for the assignment node
            ifNode->set_condition(std::move(conditionNode));
            ifNode->set_then(std::move(val));
            
            // Push the completed assignment node back onto the stack
            ast_stack->push(std::move(ifNode));
            return objects::instr;
        }

        case reduction_rule::R5:
            return objects::instr;
        case reduction_rule::R6:{
            if (ast_stack->size() < 2) return objects::null;
            
            // Pop the top three nodes from the stack
            std::unique_ptr<node> label = std::move(ast_stack->top());
            ast_stack->pop();
            
            std::unique_ptr<node> gotonode = std::move(ast_stack->top());
            ast_stack->pop();
            
            
            // Cast the nodes to their specific types
            auto* _gotoNode = dynamic_cast<goto_node*>(gotonode.release());
            if (!_gotoNode) return objects::null; // Safety check
            std::unique_ptr<goto_node> GOTO_node(_gotoNode);
            
            
            auto* label_ptr = dynamic_cast<label_node*>(label.release());
            if (!label_ptr) return objects::null; // Safety check
            std::unique_ptr<label_node> val(label_ptr);
            
            // Set source and value for the binary expression node
            GOTO_node->set_label(std::move(val));
            
            // Push the completed binary expression node back onto the stack
            ast_stack->push(std::move(GOTO_node));
            
            return objects::instr;
        }
        case reduction_rule::R7: {
            if (ast_stack->size() < 2) return objects::null;
            
            // Pop the top three nodes from the stack
            std::unique_ptr<node> term = std::move(ast_stack->top());
            ast_stack->pop();
            
            std::unique_ptr<node> output = std::move(ast_stack->top());
            ast_stack->pop();
            
            
            // Cast the nodes to their specific types
            auto* outputPTR = dynamic_cast<output_node*>(output.release());
            if (!outputPTR) return objects::null; // Safety check
            std::unique_ptr<output_node> outputNode(outputPTR);
            
            
            auto* val_ptr = dynamic_cast<term_node*>(term.release());
            if (!val_ptr) return objects::null; // Safety check
            std::unique_ptr<term_node> val(val_ptr);
            
            // Set source and value for the binary expression node
            outputNode->set_value(std::move(val));
            
            // Push the completed binary expression node back onto the stack
            ast_stack->push(std::move(outputNode));
            return objects::instr;
        }

        case reduction_rule::R8:{
            if (ast_stack->size() < 3) return objects::null;
                
                // Pop the top three nodes from the stack
                std::unique_ptr<node> var1 = std::move(ast_stack->top());
                ast_stack->pop();
                
                std::unique_ptr<node> cond = std::move(ast_stack->top());
                ast_stack->pop();
                
                std::unique_ptr<node> var2 = std::move(ast_stack->top());
                ast_stack->pop();
                
                // Cast the nodes to their specific types
                auto* cond_ptr = dynamic_cast<binary_expression_node*>(cond.release());
                if (!cond_ptr) return objects::null; // Safety check
                std::unique_ptr<binary_expression_node> cond_node(cond_ptr);
                
                auto* var1_ptr = dynamic_cast<term_node*>(var1.release());
                if (!var1_ptr) return objects::null; // Safety check
                std::unique_ptr<term_node> var1_node(var1_ptr);
                
                auto* var2_ptr = dynamic_cast<term_node*>(var2.release());
                if (!var2_ptr) return objects::null; // Safety check
                std::unique_ptr<term_node> var2_node(var2_ptr);
                
                // Set source and value for the assignment node
                cond_node->set_left(std::move(var1_node));
                cond_node->set_right(std::move(var2_node));
    
                std::unique_ptr<condition_node> conditionNode = std::make_unique<condition_node>(std::move(cond_node));
                // Push the completed assignment node back onto the stack
                ast_stack->push(std::move(conditionNode));
                return objects::rel;
        }
        case reduction_rule::R9:
            return objects::expr;
        case reduction_rule::R10:{
        if (ast_stack->size() < 3) return objects::null;
            
            // Pop the top three nodes from the stack
            std::unique_ptr<node> var1 = std::move(ast_stack->top());
            ast_stack->pop();
            
            std::unique_ptr<node> add_node = std::move(ast_stack->top());
            ast_stack->pop();
            
            std::unique_ptr<node> var2 = std::move(ast_stack->top());
            ast_stack->pop();
            
            // Cast the nodes to their specific types
            auto* add_ptr = dynamic_cast<binary_expression_node*>(add_node.release());
            if (!add_ptr) return objects::null; // Safety check
            std::unique_ptr<binary_expression_node> add(add_ptr);
            
            auto* var1_ptr = dynamic_cast<term_node*>(var1.release());
            if (!var1_ptr) return objects::null; // Safety check
            std::unique_ptr<term_node> var1_node(var1_ptr);
            
            auto* var2_ptr = dynamic_cast<term_node*>(var2.release());
            if (!var2_ptr) return objects::null; // Safety check
            std::unique_ptr<term_node> var2_node(var2_ptr);
            
            // Set source and value for the assignment node
            add->set_left(std::move(var1_node));
            add->set_right(std::move(var2_node));

            
            // Push the completed assignment node back onto the stack
            ast_stack->push(std::move(add));
            return objects::expr;
        }
        case reduction_rule::R11:
            return objects::term;
        case reduction_rule::R12:
            return objects::term;
        case reduction_rule::R13:
            return objects::term;
        default:
            return objects::null;
    }
}
void print_Stack(std::stack<std::unique_ptr<node>>& ast_stack) {
    std::stack<std::unique_ptr<node>> temp;
    std::cout << "stack :  ";
    // Print and move elements to temporary stack
    while (!ast_stack.empty()) {
        
        std::cout << ast_stack.top()->getTypeName() << " ";
        temp.push(std::move(ast_stack.top()));
        ast_stack.pop();
    }

    // Restore original stack
    while (!temp.empty()) {
        ast_stack.push(std::move(temp.top()));
        temp.pop();
    }

    std::cout << "\n";
}
void Parser::build_ast()
{
    std::stack<int> state_stack; // Stack to keep track of parser states
    state_stack.push(0); // Start state
    size_t index = 0;
    while (state_stack.size() > 0) {
        int current_state = state_stack.top();
        token_type current_token = _tokens[index].type;
        //std::cout << current_state << " " << (int)current_token << std::endl;
        ParserAction action = _slr.getAction(current_state, current_token);
        //std::cout << "action : " << (int)action.action << std::endl;

        switch (action.action) {
            case stack_instruction::SHIFT:
                std::cout << "SHIFT" << action.next_state << std::endl;
                
                state_stack.push(action.next_state);
                ast_stack.push(AllocateAST(_tokens[index])); // Create a leaf node
                //print_Stack(ast_stack);
                index++;
                break;
                
            case stack_instruction::REDUCE: {
                std::cout  << "REDUCE" << ((int)action.rule + 1) <<  std::endl;
                
                // Apply reduction rule: pop required number of elements and create a new AST node
                int pop_count = getReductionSize(action.rule); // Function to determine number of elements to pop
                //std::vector<std::unique_ptr<node>> children;
                objects new_obj = reduce(action.rule, &ast_stack);
                for (int i = 0; i < pop_count; ++i) {
                    
                    state_stack.pop();
                }
                
                
                // Create parent node for the reduction rule
                //std::unique_ptr<node> new_node = std::make_unique<node>(action.rule, std::move(children));
                
                // Get the goto state
                int new_state = _slr.getGoto(state_stack.top(), new_obj);
                state_stack.push(new_state);
                //ast_stack.push(std::move(new_node));
                //print_Stack(ast_stack);
                
                break;
            }
                
            case stack_instruction::ACCEPT:
                std::cout << "ACCEPT" << std::endl;
                //_ast.push_back(std::move(ast_stack.top()));
                return;
                
            case stack_instruction::ERROR:
                throw std::runtime_error("Parsing error at token " + std::to_string(index));
        }
    }
    
}

std::vector<std::unique_ptr<node>> Parser::getAst()
{
    std::vector<std::unique_ptr<node>> result;
    while (!ast_stack.empty()) {
        result.push_back(std::move(ast_stack.top()));
        ast_stack.pop();
    }
    std::reverse(result.begin(),result.end() );
    return result;
}

int Parser::getReductionSize(reduction_rule rule) {
    switch (rule) {
        case reduction_rule::R1: return 2;
        case reduction_rule::R3: return 3;
        case reduction_rule::R4: return 4;
        case reduction_rule::R6: return 2;
        case reduction_rule::R7: return 2;
        case reduction_rule::R8: return 3;
        case reduction_rule::R10: return 3;
        default: return 1;
    }
}

std::unique_ptr<node> Parser::AllocateAST(Token tok)
{
    switch (tok.type)
    {
    case token_type::IDENT:
        return std::unique_ptr<node>(new var_node(tok.value));
    case token_type::IF:
        return std::unique_ptr<node>(new if_node());
    case token_type::LABEL:
        return std::unique_ptr<node>(new label_node(tok.value));
    case token_type::GOTO:
        return std::unique_ptr<node>(new goto_node());
    case token_type::OUTPUT:
        return std::unique_ptr<node>(new output_node());
    case token_type::SET:
        return std::unique_ptr<node>(new assign_node());
    case token_type::LESS_THAN:
        return std::unique_ptr<node>(new binary_expression_node(binary_operator::LESS_THAN));
    case token_type::PLUS:
        return std::unique_ptr<node>(new binary_expression_node(binary_operator::PLUS));
    case token_type::INPUT:
        return std::unique_ptr<node>(new input_node());
    case token_type::INT:
        return std::unique_ptr<node>(new int_node(tok.value));
    case token_type::THEN:
        return std::unique_ptr<node>(new then_node());
    default:
        // Handle unexpected tokens, e.g., return nullptr or throw
        return nullptr;
    }
}



