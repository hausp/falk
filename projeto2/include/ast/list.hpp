
#ifndef AST_LIST_HPP
#define AST_LIST_HPP

#include "node.hpp"

namespace ast {
    template<typename Analyser>
    class list {
        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:
        list();
        template<typename T>
        list(const T&);
        list(node_ptr);

        size_t size() const;

        list<Analyser>& operator+=(node_ptr);
        operator node_ptr();
        node_ptr extract();
     private:
     	node_ptr object;
    };
}

#include "list.ipp"

#endif /* AST_LIST_HPP */
