
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
            variable(falk::type = falk::type());

            variable(bool);

            template<typename T>
            variable(const T&, structural::type);

            structural::type stored_type() const;

            template<typename T>
            T& value();

            bool error() const;

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

            template<typename T>
            variable& assign(const T&);
         private:
            variant data;
            structural::type type = structural::type::SCALAR;
            bool fail;

            template<typename Type, Type OP, typename T>
            variable& op(op::callback<Type, OP, 2>, const T&);
        };
    }
}

#include "variable.ipp"

#endif /* FALK_EV_SCALAR_HPP */
