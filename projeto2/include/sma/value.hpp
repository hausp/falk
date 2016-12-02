
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
            op_assign(rhs, typename Operation::ADD_ASSIGN());
            return *this;
        }

        val& operator-=(val& rhs) {
            op_assign(rhs, typename Operation::SUB_ASSIGN());
            return *this;
        }

        val& operator*=(val& rhs) {
            op_assign(rhs, typename Operation::MULT_ASSIGN());
            return *this;
        }

        val& operator/=(val& rhs) {
            op_assign(rhs, typename Operation::DIV_ASSIGN());
            return *this;
        }

        val& operator%=(val& rhs) {
            op_assign(rhs, typename Operation::MOD_ASSIGN());
            return *this;
        }

        val& operator&=(val& rhs) {
            op_assign(rhs, typename Operation::AND_ASSIGN());
            return *this;
        }

        val& operator|=(val& rhs) {
            op_assign(rhs, typename Operation::OR_ASSIGN());
            return *this;
        }

        val operator!() {
            return op(typename Operation::NOT());
        }

        val& pow(val& rhs) {
            op_assign(rhs, typename Operation::POW_ASSIGN());
            return *this;
        }

        static val pow(val& lhs, val& rhs) {
            return lhs.op(rhs, typename Operation::POW());
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
        return lhs.op(rhs, typename O::ADD());
    }

    template<typename A, typename O>
    value<A, O> operator-(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::SUB());   
    }

    template<typename A, typename O>
    value<A, O> operator-(value<A, O>& rhs) {
        return rhs.op(typename O::SUB_UNARY());   
    }

    template<typename A, typename O>
    value<A, O> operator*(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::MULT());
    }

    template<typename A, typename O>
    value<A, O> operator/(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::DIV());
    }

    template<typename A, typename O>
    value<A, O> operator%(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::MOD());
    }

    template<typename A, typename O>
    value<A, O> operator<(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::LT());
    }

    template<typename A, typename O>
    value<A, O> operator>(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::GT());
    }

    template<typename A, typename O>
    value<A, O> operator<=(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::LE());
    }

    template<typename A, typename O>
    value<A, O> operator>=(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::GE());
    }

    template<typename A, typename O>
    value<A, O> operator==(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::EQ());
    }

    template<typename A, typename O>
    value<A, O> operator!=(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::NE());
    }

    template<typename A, typename O>
    value<A, O> operator&&(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::AND());
    }

    template<typename A, typename O>
    value<A, O> operator||(value<A, O>& lhs, value<A, O>& rhs) {
        return lhs.op(rhs, typename O::OR());
    }
}

#endif /* SMA_VALUE_HPP */
