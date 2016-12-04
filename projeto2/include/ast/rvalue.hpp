
#ifndef SMA_VALUE_HPP
#define SMA_VALUE_HPP

#include "base/operators.hpp"
#include "node.hpp"

namespace ast {
    template<typename>
    class lvalue;

    // Abstraction for lvalues and rvalues.
    template<typename Analyser>
    class rvalue {
        friend class lvalue<Analyser>;

        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:
        rvalue();
        rvalue(node_ptr);
        template<typename T>
        rvalue(const T&);
        template<typename T>
        rvalue(const T&, node_ptr);

        bool empty() const;

        void visit(Analyser&);

        template<typename T>
        rvalue<Analyser> op(rvalue<Analyser>&, const T&);
        template<typename T>
        rvalue<Analyser> op(const T&);
        static rvalue<Analyser> pow(rvalue<Analyser>&, rvalue<Analyser>&);
        rvalue<Analyser> operator!();

        operator node_ptr();
        node_ptr extract();
     private:
        node_ptr object;
    };
}

#include "rvalue.ipp"

#endif /* SMA_VALUE_HPP */
