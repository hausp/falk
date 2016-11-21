
#ifndef SMA_LIST_HPP
#define SMA_LIST_HPP

#include "sma/list.hpp"

// Semantical Abstractions
namespace sma {
    template<typename Analyser>
    class list {
        friend class empty<Analyser>;

        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:

     private:

    };
}

#endif /* SMA_LIST_HPP */
