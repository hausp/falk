
#ifndef SMA_OPERATION_HPP
#define SMA_OPERATION_HPP

#include "ast/node.hpp"
#include "base/operators.hpp"

// Semantical Abstractions
namespace sma {
    // Abstraction for lvalues and rvalues.
    template<typename Analyser, size_t Arity = 2>
    class operation {
        using node = ast::node<Analyser>;
        using node_ptr = std::unique_ptr<node>;
     public:
        template<typename T>
        value(T data):
          object{new ast::model<Analyser, T>{std::move(data)}} { }
        
        constexpr size_t arity() { return Arity; }

     private:
        node_ptr object;
    };
}

#endif /* SMA_OPERATION_HPP */
