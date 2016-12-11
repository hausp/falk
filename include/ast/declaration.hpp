
#ifndef AST_DECLARATION_HPP
#define AST_DECLARATION_HPP

#include "node.hpp"

namespace ast {
    // Captures behavior of declarations.
    // Basically, constructs a node with any data and
    // add other node as subnode.
    // Does not allow operations and provides a explicit
    // method to extract the node.
    template<typename Analyser>
    class declaration {
        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
        using empty = ast::empty_node<Analyser>;
     public:
        declaration();

        template<typename T>
        declaration(const T&, node_ptr = std::make_shared<empty>());
        node_ptr extract();

     private:
        node_ptr object;
    };
}

#include "declaration.ipp"

#endif /* AST_DECLARATION_HPP */
