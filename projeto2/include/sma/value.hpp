
#ifndef SMA_VALUE_HPP
#define SMA_VALUE_HPP

#include "ast/node.hpp"
#include "sma/list.hpp"

// Semantical Abstractions
namespace sma {
    // Abstraction for lvalues and rvalues.
    template<typename Analyser, typename Operation>
    class value {
        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
        using val = value<Analyser, Operation>;
     public:
        value();
        value(node_ptr);
        template<typename T>
        value(const T&);

        bool empty() const;

        template<typename T>
        val op(val&, const T&);
        template<typename T>
        val op(const T&);
        template<typename T>
        void op_assign(val&, const T&);

        void traverse(Analyser&);

        static val pow(val&, val&);
        val& pow(val&);
        val& operator+=(val&);
        val& operator-=(val&);
        val& operator*=(val&);
        val& operator/=(val&);
        val& operator%=(val&);
        val& operator&=(val&);
        val& operator|=(val&);
        val operator!();
        operator node_ptr();
     private:
        node_ptr object;
    };
}

#include "value.ipp"

#endif /* SMA_VALUE_HPP */
