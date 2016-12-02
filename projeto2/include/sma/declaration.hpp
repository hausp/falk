
#ifndef SMA_DECLARATION_HPP
#define SMA_DECLARATION_HPP

#include "ast/node.hpp"

namespace sma {
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

#endif /* SMA_DECLARATION_HPP */
