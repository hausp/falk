
#ifndef SMA_VALUE_HPP
#define SMA_VALUE_HPP

#include "base/operators.hpp"
#include "node.hpp"

namespace ast {
    // Abstraction for lvalues and rvalues.
    template<typename Analyser>
    class value {
        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:
        value();
        value(node_ptr);
        template<typename T>
        value(const T&);

        bool empty() const;

        template<typename T>
        value<Analyser> op(value<Analyser>&, const T&);
        template<typename T>
        value<Analyser> op(const T&);
        template<typename T>
        void op_assign(value<Analyser>&, const T&);

        void traverse(Analyser&);

        static value<Analyser> pow(value<Analyser>&, value<Analyser>&);
        value<Analyser>& pow(value<Analyser>&);
        value<Analyser>& operator+=(value<Analyser>&);
        value<Analyser>& operator-=(value<Analyser>&);
        value<Analyser>& operator*=(value<Analyser>&);
        value<Analyser>& operator/=(value<Analyser>&);
        value<Analyser>& operator%=(value<Analyser>&);
        value<Analyser>& operator&=(value<Analyser>&);
        value<Analyser>& operator|=(value<Analyser>&);
        value<Analyser> operator!();
        operator node_ptr();
     private:
        node_ptr object;
    };
}

#include "value.ipp"

#endif /* SMA_VALUE_HPP */
