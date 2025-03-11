#ifndef REDUCTION_RULES_H
#define REDUCTION_RULES_H

#include "Ast.h"
#include "ParserSLR.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include <memory>

class ReductionRules {
public:
    ReductionRules();
    std::unique_ptr<node> applyRule(reduction_rule rule, std::vector<std::unique_ptr<node>>& children);

private:
    std::unordered_map<reduction_rule, std::function<std::unique_ptr<node>(std::vector<std::unique_ptr<node>>& children)>> _rules;
    
    // Reduction rule functions
    static std::unique_ptr<node> reduceR1(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR2(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR3(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR4(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR5(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR6(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR7(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR8(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR9(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR10(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR11(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR12(std::vector<std::unique_ptr<node>>& children);
    static std::unique_ptr<node> reduceR13(std::vector<std::unique_ptr<node>>& children);
};

#endif
