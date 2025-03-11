#ifndef STACK_H
#define STACK_H
#include <stack>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<T> stackToVector(std::stack<T> s) {
    std::vector<T> vec;
    // Pop elements from the stack and store them in the vector.
    while (!s.empty()) {
        vec.push_back(s.top());
        s.pop();
    }
    // Reverse the vector to restore the original order.
    std::reverse(vec.begin(), vec.end());
    return vec;
}

#endif