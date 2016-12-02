
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
        value():
          object{new ast::empty_node<Analyser>{}} { }

        value(node_ptr node):
          object{std::move(node)} { }

        template<typename T>
        value(const T& data):
          object{new ast::model<Analyser, T>{data}} { }

        bool empty() const {
            return object->empty();
        }

        operator node_ptr() {
            return object;
        }

        val& operator+=(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::arithmetic,
                         Operation::arithmetic::ADD, 2, true>()
            );
            return *this;
        }

        val& operator-=(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::arithmetic,
                         Operation::arithmetic::SUB, 2, true>()
            );
            return *this;
        }

        val& operator*=(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::arithmetic,
                         Operation::arithmetic::MULT, 2, true>()
            );
            return *this;
        }

        val& operator/=(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::arithmetic,
                         Operation::arithmetic::DIV, 2, true>()
            );
            return *this;
        }

        val& operator%=(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::arithmetic,
                         Operation::arithmetic::MOD, 2, true>()
            );
            return *this;
        }

        val& operator&=(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::logic,
                         Operation::logic::AND, 2, true>()
            );
            return *this;
        }

        val& operator|=(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::logic,
                         Operation::logic::OR, 2, true>()
            );
            return *this;
        }

        val operator!() {
            return op(typename Operation::template
                callback<typename Operation::logic,
                         Operation::logic::OR, 2, true>()
                );
        }

        val& pow(val& rhs) {
            op_assign(
                rhs,
                typename Operation::template
                callback<typename Operation::arithmetic,
                         Operation::arithmetic::POW, 2, true>()
            );
            return *this;
        }

        static val pow(val& lhs, val& rhs) {
            return lhs.op(
                rhs,
                typename Operation::template
                callback<typename Operation::arithmetic,
                         Operation::arithmetic::POW, 2>()
            );
        }

        template<typename T>
        void op_assign(val& rhs, const T& op) {
            if (rhs.object->empty()) {
                object = std::move(rhs.object);
            } else if (!object->empty()) {
                auto n = std::make_shared<ast::model<Analyser, T>>(op);
                n->add_subnode(std::move(object));
                n->add_subnode(std::move(rhs.object));
                object = n;
            } else {
                rhs.object.reset(new ast::empty_node<Analyser>);
            }
        }

        template<typename T>
        val op(val& rhs, const T& op) {
            if (rhs.object->empty()) {
                object.reset(new ast::empty_node<Analyser>);
                auto value = val{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }
            
            if(object->empty()) {
                rhs.object.reset(new ast::empty_node<Analyser>);
                auto value = val{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }
            
            auto v = val{op};
            v.object->add_subnode(std::move(object));
            v.object->add_subnode(std::move(rhs.object));
            return v;
        }

        template<typename T>
        val op(const T& op) {
            if(object->empty()) {
                object.reset(new ast::empty_node<Analyser>);
                auto value = val{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }

            auto v = val{op};
            v.object->add_subnode(std::move(object));
            return v;
        }

        void traverse(Analyser& analyser) {
            object->traverse(analyser);
        }

     private:
        node_ptr object;
    };

    template<typename A, typename O>
    value<A, O> operator+(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::ADD, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator-(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs, typename O::template
            callback<typename O::arithmetic, O::arithmetic::SUB, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator-(value<A, O>& rhs) {
        return rhs.op(
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::SUB, 1>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator*(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::MULT, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator/(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::DIV, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator%(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::arithmetic, O::arithmetic::MOD, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator<(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::LT, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator>(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::GT, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator<=(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::LE, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator>=(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::GE, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator==(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::EQ, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator!=(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::comparison, O::comparison::NE, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator&&(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::logic, O::logic::NE, 2>()
        );
    }

    template<typename A, typename O>
    value<A, O> operator||(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(
            rhs,
            typename O::template
            callback<typename O::logic, O::logic::NE, 2>()
        );
    }
}

#endif /* SMA_VALUE_HPP */
