
#ifndef AST_LVALUE_HPP
#define AST_LVALUE_HPP

#include "base/actions.hpp"
#include "rvalue.hpp"

namespace ast {
    template<typename Analyser>
    class lvalue {
        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:
        lvalue();
        template<typename T>
        lvalue(const T&);

        bool empty() const;

        void traverse(Analyser&);

        void set_index(node_ptr, node_ptr);

        lvalue<Analyser>& pow(rvalue<Analyser>&);
        lvalue<Analyser>& operator+=(rvalue<Analyser>&);
        lvalue<Analyser>& operator-=(rvalue<Analyser>&);
        lvalue<Analyser>& operator*=(rvalue<Analyser>&);
        lvalue<Analyser>& operator/=(rvalue<Analyser>&);
        lvalue<Analyser>& operator%=(rvalue<Analyser>&);
        lvalue<Analyser>& operator&=(rvalue<Analyser>&);
        lvalue<Analyser>& operator|=(rvalue<Analyser>&);

        lvalue<Analyser>& operator=(rvalue<Analyser>&);

        operator rvalue<Analyser>();
     private:
        node_ptr object;

        template<typename T>
        void op_assign(rvalue<Analyser>&, const T&);
    };
}

#include "lvalue.ipp"

#endif /* AST_LVALUE_HPP */
