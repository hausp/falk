
#ifndef SMA_LIST_HPP
#define SMA_LIST_HPP

#include "ast/node.hpp"

// Semantical Abstractions
namespace sma {
    template<typename Analyser>
    class list {
        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:
        list():
          object{new ast::empty_node<Analyser>{}} { }

        template<typename T>
        list(const T& data):
          object{new ast::model<Analyser, T>{data}} { }

        void push(node_ptr);

        operator node_ptr() {
            return object;
        }

     private:
     	node_ptr object;
    };
}

#include "list.ipp"

#endif /* SMA_LIST_HPP */
