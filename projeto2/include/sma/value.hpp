
#ifndef SMA_VALUE_HPP
#define SMA_VALUE_HPP

#include "ast/node.hpp"

// Semantical Abstractions
namespace sma {
    // Empty node
    template<typename Analyser>
    class empty;

    // Abstraction for lvalues and rvalues.
    template<typename Analyser>
    class value {
        friend class empty<Analyser>;

        using node = ast::node<Analyser>;
        using node_ptr = std::shared_ptr<node>;
     public:
        value() = default;

        template<typename T>
        value(T data):
          object{new ast::model<Analyser, T>{std::move(data)}} { }

        // value(const value& v):
        //   object{std::move(v.object)} { }

        // value<Analyser>& operator=(const value& v) {
        //     object = std::move(v.object);
        // }
    
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

        value<Analyser>& operator%=(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::MOD_ASSIGN);
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
            return op(Analyser::NOT);
        }

        value<Analyser>& pow_assign(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::POW_ASSIGN);
            return *this;
        }

        value<Analyser> pow(value<Analyser>& rhs) {
            return op(rhs, Analyser::POW);
        }

        template<typename T>
        void op_assign(value<Analyser>& rhs, const T& op) {
            if (rhs.object->empty()) {
                object = std::move(rhs.object);
            } else if (!object->empty()) {
                auto n = std::make_unique<node>(op);
                n.add_subnode(std::move(object));
                n.add_subnode(std::move(rhs.object));
                object = n;
            } else {
                rhs.object.reset(new ast::empty_node<Analyser>);
            }
        }

        template<typename T>
        value<Analyser> op(value<Analyser>& rhs, const T& op) {
            if (rhs.object->empty()) {
                object.reset(new ast::empty_node<Analyser>);
                auto value = sma::value<Analyser>{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }
            
            if(object->empty()) {
                rhs.object.reset(new ast::empty_node<Analyser>);
                auto value = sma::value<Analyser>{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }
            
            auto v = sma::value<Analyser>{op};
            v.object->add_subnode(std::move(object));
            v.object->add_subnode(std::move(rhs.object));
            return v;
        }

        template<typename T>
        value<Analyser> op(const T& op) {
            if(object->empty()) {
                object.reset(new ast::empty_node<Analyser>);
                auto value = sma::value<Analyser>{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }

            auto v = value<Analyser>{op};
            v.object->add_subnode(std::move(object));
            return v;
        }

     private:
        node_ptr object;
    };

    template<typename Analyser>
    value<Analyser> operator+(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::ADD);
    }

    template<typename Analyser>
    value<Analyser> operator-(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::SUB);   
    }

    template<typename Analyser>
    value<Analyser> operator-(value<Analyser>& rhs) {
        return rhs.op(Analyser::UNARY_SUB);   
    }

    template<typename Analyser>
    value<Analyser> operator*(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::MULT);
    }

    template<typename Analyser>
    value<Analyser> operator/(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::DIV);
    }

    template<typename Analyser>
    value<Analyser> operator%(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::MOD);
    }

    template<typename Analyser>
    value<Analyser> operator<(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::LT);
    }

    template<typename Analyser>
    value<Analyser> operator>(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::GT);
    }

    template<typename Analyser>
    value<Analyser> operator<=(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::LE);
    }

    template<typename Analyser>
    value<Analyser> operator>=(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::GE);
    }

    template<typename Analyser>
    value<Analyser> operator==(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::EQ);
    }

    template<typename Analyser>
    value<Analyser> operator!=(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::NE);
    }

    template<typename Analyser>
    value<Analyser> operator&&(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::AND);
    }

    template<typename Analyser>
    value<Analyser> operator||(value<Analyser>& lhs, value<Analyser>& rhs) {
        return lhs.op(rhs, Analyser::OR);
    }
}

#endif /* SMA_VALUE_HPP */
