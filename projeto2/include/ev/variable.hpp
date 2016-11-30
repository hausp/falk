
#ifndef FALK_EV_SCALAR_HPP
#define FALK_EV_SCALAR_HPP

#include "array.hpp"
#include "aut/variant.hpp"
#include "base/operators.hpp"
#include "matrix.hpp"
#include "scalar.hpp"

namespace falk {
    namespace ev {
        class variable {
            using variant = aut::variant<scalar, array, matrix>;
         public:
            variable() = default;

            template<typename T>
            variable(const T&);

            template<typename T>
            variable& pow(const T&);
            template<typename T>
            variable& operator+=(const T&);
            template<typename T>
            variable& operator-=(const T&);
            template<typename T>
            variable& operator*=(const T&);
            template<typename T>
            variable& operator/=(const T&);
            template<typename T>
            variable& operator%=(const T&);
            template<typename T>
            variable& operator&=(const T&);
            template<typename T>
            variable& operator|=(const T&);
         private:
            variant data;
            structural::type type;

            template<typename Type, Type OP, typename T>
            variable& op(operation<Type, OP, 2, true>, const T&);
        };
    }
}

#include "variable.ipp"

#endif /* FALK_EV_SCALAR_HPP */
