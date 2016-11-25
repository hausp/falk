
#ifndef FALK_EV_SCALAR_HPP
#define FALK_EV_SCALAR_HPP

#include "array.hpp"
#include "aut/variant.hpp"
#include "matrix.hpp"
#include "scalar.hpp"

namespace falk {
    namespace ev {
        class variable {
            using variant = aut::variant<scalar, array, matrix>;
         public:
            variable(variant&);

            falk::value get_value();

            variable& operator+=(const variable& rhs) {
                // TODO
                // op_assign(rhs, typename Operation::ADD_ASSIGN());
                return *this;
            }

            variable& operator-=(const variable& rhs) {
                // TODO
                // op_assign(rhs, typename Operation::SUB_ASSIGN());
                return *this;
            }

            variable& operator*=(const variable& rhs) {
                // TODO
                // op_assign(rhs, typename Operation::MULT_ASSIGN());
                return *this;
            }

            variable& operator/=(const variable& rhs) {
                // TODO
                // op_assign(rhs, typename Operation::DIV_ASSIGN());
                return *this;
            }

            variable& operator%=(const variable& rhs) {
                // TODO
                // op_assign(rhs, typename Operation::MOD_ASSIGN());
                return *this;
            }

            variable& operator&=(const variable& rhs) {
                // TODO
                // op_assign(rhs, typename Operation::AND_ASSIGN());
                return *this;
            }

            variable& operator|=(const variable& rhs) {
                // TODO
                // op_assign(rhs, typename Operation::OR_ASSIGN());
                return *this;
            }

         private:
            variant& data;
            structural::type type;
        };
    }
}

#endif /* FALK_EV_SCALAR_HPP */
