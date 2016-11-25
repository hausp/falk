
#ifndef FALK_TYPES_HPP
#define FALK_TYPES_HPP

#include <string>

namespace falk {
    template<typename T>
    struct definitions;

    namespace fundamental {
        enum class type {
            UNDEFINED,
            REAL,
            COMPLEX,
            BOOL,
        };
    }

    namespace structural {
        enum class type {
            SCALAR,
            ARRAY,
            MATRIX,
        };
    }

    namespace symbol {
        enum class type {
            VARIABLE,
            FUNCTION  
        };
    }

    using type = fundamental::type;

    inline type resolve_types(type t1, type t2) {
        if (t1 != t2) {
            if (t1 == type::COMPLEX || t2 == type::COMPLEX) {
                return type::COMPLEX;
            } else if (t1 == type::REAL || t2 == type::REAL) {
                return type::REAL;
            }
            // TODO: error (incompatible types)
            return type::UNDEFINED;
        }
        return t1;
    }
}

#endif /* FALK_TYPES_HPP */
