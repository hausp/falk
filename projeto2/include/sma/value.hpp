
#ifndef SMA_VALUE_HPP
#define SMA_VALUE_HPP

#include "ast/node.hpp"

// Semantical Abstractions
namespace sma {
    // Abstraction for lvalues and rvalues.
    template<typename Analyser, typename Operation>
    class value {
        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:
        value():
          object{new ast::empty_node<Analyser>{}} { }

        template<typename T>
        value(const T& data):
          object{new ast::model<Analyser, T>{data}} { }
    
        bool empty() const {
            return object->empty();
        }

        value<Analyser, Operation>& operator+=(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::ADD_ASSIGN());
            return *this;
        }

        value<Analyser, Operation>& operator-=(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::SUB_ASSIGN());
            return *this;
        }

        value<Analyser, Operation>& operator*=(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::MULT_ASSIGN());
            return *this;
        }

        value<Analyser, Operation>& operator/=(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::DIV_ASSIGN());
            return *this;
        }

        value<Analyser, Operation>& operator%=(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::MOD_ASSIGN());
            return *this;
        }

        value<Analyser, Operation>& operator&=(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::AND_ASSIGN());
            return *this;
        }

        value<Analyser, Operation>& operator|=(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::OR_ASSIGN());
            return *this;
        }

        value<Analyser, Operation> operator!() {
            return op(typename Operation::NOT());
        }

        value<Analyser, Operation>& pow_assign(value<Analyser, Operation>& rhs) {
            op_assign(rhs, typename Operation::POW_ASSIGN());
            return *this;
        }

        value<Analyser, Operation> pow(value<Analyser, Operation>& rhs) {
            return op(rhs, typename Operation::POW());
        }

        template<typename T>
        void op_assign(value<Analyser, Operation>& rhs, const T& op) {
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
        value<Analyser, Operation> op(value<Analyser, Operation>& rhs, const T& op) {
            if (rhs.object->empty()) {
                object.reset(new ast::empty_node<Analyser>);
                auto value = sma::value<Analyser, Operation>{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }
            
            if(object->empty()) {
                rhs.object.reset(new ast::empty_node<Analyser>);
                auto value = sma::value<Analyser, Operation>{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }
            
            auto v = sma::value<Analyser, Operation>{op};
            v.object->add_subnode(std::move(object));
            v.object->add_subnode(std::move(rhs.object));
            return v;
        }

        template<typename T>
        value<Analyser, Operation> op(const T& op) {
            if(object->empty()) {
                object.reset(new ast::empty_node<Analyser>);
                auto value = sma::value<Analyser, Operation>{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }

            auto v = value<Analyser, Operation>{op};
            v.object->add_subnode(std::move(object));
            return v;
        }

        void traverse(Analyser& analyser) {
            object->traverse(analyser);
        }

     private:
        node_ptr object;
    };

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator+(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::ADD());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator-(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::SUB());   
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator-(value<Analyser, Operation>& rhs) {
        return rhs.op(typename Operation::SUB_UNARY());   
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator*(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::MULT());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator/(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::DIV());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator%(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::MOD());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator<(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::LT());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator>(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::GT());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator<=(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::LE());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator>=(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::GE());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator==(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::EQ());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator!=(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::NE());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator&&(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::AND());
    }

    template<typename Analyser, typename Operation>
    value<Analyser, Operation> operator||(value<Analyser, Operation>& lhs, value<Analyser, Operation>& rhs) {
        return lhs.op(rhs, typename Operation::OR());
    }
}

#endif /* SMA_VALUE_HPP */
