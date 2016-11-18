
#ifndef SMA_VALUE_HPP
#define SMA_VALUE_HPP

#include "ast/node.hpp"
#include "base/operators.hpp"

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
    
        value<Analyser>& operator+=(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::ADD_ASSIGN);
            return *this;
        }

        value<Analyser>& operator-=(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::SUB_ASSIGN);
            return *this;
        }

        value<Analyser>& operator*=(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::MULT_ASSIGN);
            return *this;
        }

        value<Analyser>& operator/=(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::DIV_ASSIGN);
            return *this;
        }

        value<Analyser>& operator&=(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::AND_ASSIGN);
            return *this;
        }

        value<Analyser>& operator|=(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::OR_ASSIGN);
            return *this;
        }

        value<Analyser> operator!() {
            return op(*this, Analyser::NOT);
        }

        value<Analyser> pow(value<Analyser>& rhs) {
            return op(*this, rhs, Analyser::POW);
        }

     private:
        node_ptr object;

        void op_assign(value<Analyser>& rhs, typename Analyser::binary_operation op) {
            auto n = std::make_unique<node>(op);
            n.add_subnode(std::move(object));
            n.add_subnode(std::move(rhs.object));
            object = n;
        }

        value<Analyser> op(value<Analyser>& lhs,
                           value<Analyser>& rhs,
                           typename Analyser::binary_operation op) {
            auto n = std::make_unique<node>(op);
            n.add_subnode(std::move(object));
            n.add_subnode(std::move(rhs.object));
            return n;
        }

        value<Analyser> op(value<Analyser>& lhs, typename Analyser::unary_operation op) {
            auto n = std::make_unique<node>(op);
            n.add_subnode(std::move(object));
            return n;
        }
    };

    template<typename Analyser>
    value<Analyser> operator+(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::ADD);
    }

    template<typename Analyser>
    value<Analyser> operator-(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::SUB);   
    }

    template<typename Analyser>
    value<Analyser> operator*(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::MULT);
    }

    template<typename Analyser>
    value<Analyser> operator/(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::DIV);
    }

    template<typename Analyser>
    value<Analyser> operator&&(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::AND);
    }

    template<typename Analyser>
    value<Analyser> operator||(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::OR);
    }
}

#endif /* SMA_VALUE_HPP */
