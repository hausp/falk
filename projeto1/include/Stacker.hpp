#ifndef TYPES_HPP
#define TYPES_HPP

#include <stack>
#include "SyntaxTree.hpp"
#include "utils.hpp"

template<typename T>
class Stacker {
 public:
    void push(const T&);
    const T& top() const;

 private:
    std::stack<T> stack;
};

using Types = Stacker<Type>;
using MagicEntity = Stacker<polska::Node>;

#include "Stacker.ipp"

#endif /* TYPES_HPP */
