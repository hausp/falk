
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
        declaration():
          object{new empty} { }

        template<typename T>
        declaration(const T& data, node_ptr value = std::make_shared<empty>()):
          object{new ast::model<Analyser, T>{data}} {
            object->add_subnode(value);
        }

        node_ptr extract() { return object; }

     private:
        node_ptr object;
    };
}

#endif /* SMA_DECLARATION_HPP */
