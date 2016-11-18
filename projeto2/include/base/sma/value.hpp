
#ifndef FALK_SMA_VALUE_HPP
#define FALK_SMA_VALUE_HPP

#include "ast/node.hpp"

namespace falk {
    // Semantical Abstractions
    namespace sma {
        // Abstraction for lvalues and rvalues.
        template<typename Analyser>
        class value {
            using node = ast::node<Analyser>;
            using node_ptr = std::unique_ptr<node>;
         public:
            template<typename T>
            value(T data):
              object{new ast::model<Analyser, T>{std::move(data)}} { }
    
            node* get_node() { return object.get(); }
            // create operators here;
         private:
            node_ptr object;
        };
    }
}

#endif /* FALK_SMA_VALUE_HPP */
