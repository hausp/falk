
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
            return op(*this, Analyser::NOT);
        }

        value<Analyser>& pow_assign(value<Analyser>& rhs) {
            op_assign(rhs, Analyser::POW_ASSIGN);
            return *this;
        }

        value<Analyser> pow(value<Analyser>& rhs) {
            return op(*this, rhs, Analyser::POW);
        }

     private:
        node_ptr object;

        value() = default;

        template<typename T>
        void op_assign(value<Analyser>& rhs, const T& op) {
            if (rhs.object.empty()) {
                object = std::move(rhs.object);
            } else if (!object.empty()) {
                auto n = std::make_unique<node>(op);
                n.add_subnode(std::move(object));
                n.add_subnode(std::move(rhs.object));
                object = n;
            } else {
                rhs.object.reset(new ast::empty_node<Analyser>);
            }
        }

        template<typename T>
        value<Analyser> op(value<Analyser>& lhs, value<Analyser>& rhs, const T& op) {
            if (rhs.object.empty()) {
                lhs.object.reset(new ast::empty_node<Analyser>);
                auto value = sma::value{};
                value.object.reset(new ast::empty_node<Analyser>);
                return value;
            }
            
            if(lhs.object.empty()) {
                rhs.object.reset(new ast::empty_node<Analyser>);
                // a error here
                return sma::empty{};
            }
            
            auto value = value<Analyser>{op};
            value.object.add_subnode(std::move(object));
            value.object.add_subnode(std::move(rhs.object));
            return value;
        }

        template<typename T>
        value<Analyser> op(value<Analyser>& lhs, const T& op) {
            if(lhs.object.empty()) {
                rhs.object.reset(new ast::empty_node<Analyser>);
                return sma::empty{};
            }

            auto value = value<Analyser>{op};
            value.object.add_subnode(std::move(object));
            return value;
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
    value<Analyser> operator%(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::MOD);
    }

    template<typename Analyser>
    value<Analyser> operator<(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::LT);
    }

    template<typename Analyser>
    value<Analyser> operator>(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::GT);
    }

    template<typename Analyser>
    value<Analyser> operator<=(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::LE);
    }

    template<typename Analyser>
    value<Analyser> operator>=(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::GE);
    }

    template<typename Analyser>
    value<Analyser> operator==(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::EQ);
    }

    template<typename Analyser>
    value<Analyser> operator!=(value<Analyser>& lhs, value<Analyser>& rhs) {
        return op(lhs, rhs, Analyser::NE);
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
