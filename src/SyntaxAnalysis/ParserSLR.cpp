#include "ParserSLR.h"
#include <iostream>

ParserSLR::ParserSLR() {
    initializeActionTable();
    initializeGotoTable();
}

void ParserSLR::initializeActionTable() {
    // State 0 actions - Entry point
    _actionTable[std::make_tuple(0, token_type::IDENT)] = ParserAction(3);  // s3
    _actionTable[std::make_tuple(0, token_type::IF)] = ParserAction(4);  // s4
    _actionTable[std::make_tuple(0, token_type::LABEL)] = ParserAction(5);  // s5
    _actionTable[std::make_tuple(0, token_type::GOTO)] = ParserAction(6);  // s6
    _actionTable[std::make_tuple(0, token_type::OUTPUT)] = ParserAction(7);  // s7
    
    // State 1 actions
    _actionTable[std::make_tuple(1, token_type::IDENT)] = ParserAction(3);  // s3
    _actionTable[std::make_tuple(1, token_type::IF)] = ParserAction(4);  // s4
    _actionTable[std::make_tuple(1, token_type::LABEL)] = ParserAction(5);  // s5
    _actionTable[std::make_tuple(1, token_type::GOTO)] = ParserAction(6);  // s6
    _actionTable[std::make_tuple(1, token_type::OUTPUT)] = ParserAction(7);  // s7
    _actionTable[std::make_tuple(1, token_type::END)] = ParserAction();   // accept
    
    // State 2 actions
    _actionTable[std::make_tuple(2, token_type::IDENT)] = ParserAction(reduction_rule::R2);  // r2
    _actionTable[std::make_tuple(2, token_type::IF)] = ParserAction(reduction_rule::R2);  // r2
    _actionTable[std::make_tuple(2, token_type::LABEL)] = ParserAction(reduction_rule::R2);  // r2
    _actionTable[std::make_tuple(2, token_type::GOTO)] = ParserAction(reduction_rule::R2);  // r2
    _actionTable[std::make_tuple(2, token_type::OUTPUT)] = ParserAction(reduction_rule::R2);  // r2
    _actionTable[std::make_tuple(2, token_type::END)] = ParserAction(reduction_rule::R2);  // r2
    
    // State 3 actions
    _actionTable[std::make_tuple(3, token_type::SET)] = ParserAction(9);  // s9
    
    // State 4 actions
    _actionTable[std::make_tuple(4, token_type::IDENT)] = ParserAction(13);  // s13
    _actionTable[std::make_tuple(4, token_type::INPUT)] = ParserAction(12);  // s12
    _actionTable[std::make_tuple(4, token_type::INT)] = ParserAction(14);  // s14
    
    // State 5 actions
    _actionTable[std::make_tuple(5, token_type::IDENT)] = ParserAction(reduction_rule::R5);  // r5
    _actionTable[std::make_tuple(5, token_type::IF)] = ParserAction(reduction_rule::R5);  // r5
    _actionTable[std::make_tuple(5, token_type::LABEL)] = ParserAction(reduction_rule::R5);  // r5
    _actionTable[std::make_tuple(5, token_type::GOTO)] = ParserAction(reduction_rule::R5);  // r5
    _actionTable[std::make_tuple(5, token_type::OUTPUT)] = ParserAction(reduction_rule::R5);  // r5
    _actionTable[std::make_tuple(5, token_type::END)] = ParserAction(reduction_rule::R5);  // r5
    
    // State 6 actions
    _actionTable[std::make_tuple(6, token_type::LABEL)] = ParserAction(15);  // s15
    
    // State 7 actions
    _actionTable[std::make_tuple(7, token_type::IDENT)] = ParserAction(13);  // s13
    _actionTable[std::make_tuple(7, token_type::INPUT)] = ParserAction(12);  // s12
    _actionTable[std::make_tuple(7, token_type::INT)] = ParserAction(14);  // s14
    
    // State 8 actions
    _actionTable[std::make_tuple(8, token_type::IDENT)] = ParserAction(reduction_rule::R1);  // r1
    _actionTable[std::make_tuple(8, token_type::IF)] = ParserAction(reduction_rule::R1);  // r1
    _actionTable[std::make_tuple(8, token_type::LABEL)] = ParserAction(reduction_rule::R1);  // r1
    _actionTable[std::make_tuple(8, token_type::GOTO)] = ParserAction(reduction_rule::R1);  // r1
    _actionTable[std::make_tuple(8, token_type::OUTPUT)] = ParserAction(reduction_rule::R1);  // r1
    _actionTable[std::make_tuple(8, token_type::END)] = ParserAction(reduction_rule::R1);  // r1
    
    // State 9 actions
    _actionTable[std::make_tuple(9, token_type::IDENT)] = ParserAction(13);  // s13
    _actionTable[std::make_tuple(9, token_type::INPUT)] = ParserAction(12);  // s12
    _actionTable[std::make_tuple(9, token_type::INT)] = ParserAction(14);  // s14
    
    // State 10 actions
    _actionTable[std::make_tuple(10, token_type::THEN)] = ParserAction(19);  // S19
    
    // State 11 actions
    _actionTable[std::make_tuple(11, token_type::LESS_THAN)] = ParserAction(20);  // r10

    
    // State 12 
    _actionTable[std::make_tuple(12, token_type::IDENT)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::IF)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::THEN)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::LABEL)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::GOTO)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::OUTPUT)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::LESS_THAN)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::PLUS)] = ParserAction(reduction_rule::R11);  // r11
    _actionTable[std::make_tuple(12, token_type::END)] = ParserAction(reduction_rule::R11);  // r11
    
    // State 13 
    _actionTable[std::make_tuple(13, token_type::IDENT)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::IF)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::THEN)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::LABEL)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::GOTO)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::OUTPUT)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::LESS_THAN)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::PLUS)] = ParserAction(reduction_rule::R12);  // r12
    _actionTable[std::make_tuple(13, token_type::END)] = ParserAction(reduction_rule::R12); //r12


    // State 14 actions
    _actionTable[std::make_tuple(14, token_type::IDENT)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::IF)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::THEN)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::LABEL)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::GOTO)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::OUTPUT)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::LESS_THAN)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::PLUS)] = ParserAction(reduction_rule::R13);  // R13
    _actionTable[std::make_tuple(14, token_type::END)] = ParserAction(reduction_rule::R13); // R13
    
    // State 15 actions 
    _actionTable[std::make_tuple(15, token_type::IDENT)] = ParserAction(reduction_rule::R6);  // R6
    _actionTable[std::make_tuple(15, token_type::END)] = ParserAction(reduction_rule::R6);  // R6
    _actionTable[std::make_tuple(15, token_type::IF)] = ParserAction(reduction_rule::R6);  // R6
    _actionTable[std::make_tuple(15, token_type::LABEL)] = ParserAction(reduction_rule::R6);  // R6
    _actionTable[std::make_tuple(15, token_type::GOTO)] = ParserAction(reduction_rule::R6);  // R6
    _actionTable[std::make_tuple(15, token_type::OUTPUT)] = ParserAction(reduction_rule::R6);  // R6
    
    // State 16 actions 
    _actionTable[std::make_tuple(16, token_type::IDENT)] = ParserAction(reduction_rule::R7);  // r7
    _actionTable[std::make_tuple(16, token_type::END)] = ParserAction(reduction_rule::R7);  // r7
    _actionTable[std::make_tuple(16, token_type::IF)] = ParserAction(reduction_rule::R7);  // r7
    _actionTable[std::make_tuple(16, token_type::LABEL)] = ParserAction(reduction_rule::R7);  // r7
    _actionTable[std::make_tuple(16, token_type::GOTO)] = ParserAction(reduction_rule::R7);  // r7
    _actionTable[std::make_tuple(16, token_type::OUTPUT)] = ParserAction(reduction_rule::R7);  // r7
    
    // State 17 actions 
    _actionTable[std::make_tuple(17, token_type::IDENT)] = ParserAction(reduction_rule::R3);  // r3
    _actionTable[std::make_tuple(17, token_type::END)] = ParserAction(reduction_rule::R3);  // r3
    _actionTable[std::make_tuple(17, token_type::IF)] = ParserAction(reduction_rule::R3);  // r3
    _actionTable[std::make_tuple(17, token_type::LABEL)] = ParserAction(reduction_rule::R3);  // r3
    _actionTable[std::make_tuple(17, token_type::GOTO)] = ParserAction(reduction_rule::R3);  // r3
    _actionTable[std::make_tuple(17, token_type::OUTPUT)] = ParserAction(reduction_rule::R3);  // r3
    
    // State 18 actions 
    _actionTable[std::make_tuple(18, token_type::IDENT)] = ParserAction(reduction_rule::R9);  // r9
    _actionTable[std::make_tuple(18, token_type::END)] = ParserAction(reduction_rule::R9);  // r9
    _actionTable[std::make_tuple(18, token_type::IF)] = ParserAction(reduction_rule::R9);  // r9
    _actionTable[std::make_tuple(18, token_type::LABEL)] = ParserAction(reduction_rule::R9);  // r9
    _actionTable[std::make_tuple(18, token_type::GOTO)] = ParserAction(reduction_rule::R9);  // r9
    _actionTable[std::make_tuple(18, token_type::OUTPUT)] = ParserAction(reduction_rule::R9);  // r9
    _actionTable[std::make_tuple(18, token_type::PLUS)] = ParserAction(21);  // s21
    
    
    // State 19 actions
    _actionTable[std::make_tuple(19, token_type::IDENT)] = ParserAction(3);  // s3
    _actionTable[std::make_tuple(19, token_type::IF)] = ParserAction(4);  // s4
    _actionTable[std::make_tuple(19, token_type::LABEL)] = ParserAction(5);  // s5
    _actionTable[std::make_tuple(19, token_type::GOTO)] = ParserAction(6);  // s6
    _actionTable[std::make_tuple(19, token_type::OUTPUT)] = ParserAction(7);  // s7
    
    // State 20 actions
    _actionTable[std::make_tuple(20, token_type::IDENT)] = ParserAction(13);  // s13
    _actionTable[std::make_tuple(20, token_type::INPUT)] = ParserAction(12);  // s12
    _actionTable[std::make_tuple(20, token_type::INT)] = ParserAction(14);  // s14
    
    // State 21 actions
    _actionTable[std::make_tuple(21, token_type::IDENT)] = ParserAction(13);  // s13
    _actionTable[std::make_tuple(21, token_type::INPUT)] = ParserAction(12);  // s12
    _actionTable[std::make_tuple(21, token_type::INT)] = ParserAction(14);  // s14
    
    // State 22 actions
    _actionTable[std::make_tuple(22, token_type::IDENT)] = ParserAction(reduction_rule::R4);  // r4
    _actionTable[std::make_tuple(22, token_type::END)] = ParserAction(reduction_rule::R4);  // r4
    _actionTable[std::make_tuple(22, token_type::IF)] = ParserAction(reduction_rule::R4);  // r4
    _actionTable[std::make_tuple(22, token_type::LABEL)] = ParserAction(reduction_rule::R4);  // r4
    _actionTable[std::make_tuple(22, token_type::GOTO)] = ParserAction(reduction_rule::R4);  // r4
    _actionTable[std::make_tuple(22, token_type::OUTPUT)] = ParserAction(reduction_rule::R4);  // r4
    
    // State 23 actions
    _actionTable[std::make_tuple(23, token_type::THEN)] = ParserAction(reduction_rule::R8);  // r8
    
    // State 24 actions
    _actionTable[std::make_tuple(24, token_type::IDENT)] = ParserAction(reduction_rule::R10);  // r10
    _actionTable[std::make_tuple(24, token_type::END)] = ParserAction(reduction_rule::R10);  // r10
    _actionTable[std::make_tuple(24, token_type::IF)] = ParserAction(reduction_rule::R10);  // r10
    _actionTable[std::make_tuple(24, token_type::LABEL)] = ParserAction(reduction_rule::R10);  // r10
    _actionTable[std::make_tuple(24, token_type::GOTO)] = ParserAction(reduction_rule::R10);  // r10
    _actionTable[std::make_tuple(24, token_type::OUTPUT)] = ParserAction(reduction_rule::R10);  // r10
}

void ParserSLR::initializeGotoTable() {
    // Set up the GOTO part of the table
    _gotoTable[std::make_tuple(0, objects::instractions)] = 1;
    _gotoTable[std::make_tuple(0, objects::instr)] = 2;
    _gotoTable[std::make_tuple(1, objects::instr)] = 8;
    _gotoTable[std::make_tuple(4, objects::rel)] = 10;
    _gotoTable[std::make_tuple(4, objects::term)] = 11;
    _gotoTable[std::make_tuple(7, objects::term)] = 16;
    _gotoTable[std::make_tuple(9, objects::expr)] = 17;
    _gotoTable[std::make_tuple(9, objects::term)] = 18;
    _gotoTable[std::make_tuple(19, objects::instr)] = 22;
    _gotoTable[std::make_tuple(20, objects::term)] = 23;
    _gotoTable[std::make_tuple(21, objects::term)] = 24;
}

ParserAction ParserSLR::getAction(int state, token_type token) {
    auto key = std::make_tuple(state, token);
    if (_actionTable.find(key) != _actionTable.end()) {
        return _actionTable[key];
    }
    // Return error action if not found
    return ParserAction(stack_instruction::ERROR, -1, reduction_rule::R1);
}

int ParserSLR::getGoto(int state, objects non_terminal) {
    auto key = std::make_tuple(state, non_terminal);
    if (_gotoTable.find(key) != _gotoTable.end()) {
        return _gotoTable[key];
    }
    return -1; // Error
}

