#ifndef STACKER_HPP
#define STACKER_HPP

#include <stack>
#include "SyntaxTree.hpp"
#include "utils.hpp"

template<typename T>
class Stacker {
 public:
    static void push(const T&);
    static const T& top();
    static void clear();

 private:
    static std::stack<T> stack;
};

using Types = Stacker<Type>;
using MagicEntity = Stacker<polska::Node>;

#include "Stacker.ipp"

#endif /* STACKER_HPP */
