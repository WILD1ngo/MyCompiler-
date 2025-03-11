#ifndef VEC2_H
#define VEC2_H
#include <iostream>
#include <functional>  // For std::hash

//simple 2d vector
template<typename T,typename F>
struct vec2
{
    T x;
    F y;
    //constructors
    vec2() : x(T()), y(F()) {}
    vec2(T x_, F y_) : x(x_), y(y_) {}


};



// Hash specialization for vec2
namespace std {
    template<typename T, typename F>
    struct hash<vec2<T, F>> {
        size_t operator()(const vec2<T, F>& vec) const {
            // Combine hashes of x and y using standard hash combination technique
            size_t seed = 0;
            
            // Hash each component using std::hash
            hash<T> hasherT;
            hash<F> hasherF;
            
            // Boost-like hash combine (prevents trivial collisions)
            seed ^= hasherT(vec.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hasherF(vec.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            
            return seed;
        }
    };
}
#endif
