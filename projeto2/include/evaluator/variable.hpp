
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

            template<typename T>
            T& get_data();

            template<typename T>
            const T& get_data() const;

         private:
            variant& data;
        };
    }
}

#endif /* FALK_EV_SCALAR_HPP */
