
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
            VARIABLE,
            ARRAY,
            MATRIX,
        };
    }

    struct type_def {
        fundamental::type f_type;
        structural::type s_type;
    };

    using type = fundamental::type;

    inline type resolve_types(type t1, type t2) {
        if (t1 != t2) {
            if (t1 == type::BOOL || t2 == type::BOOL) {
                // TODO
            } else if (t1 == type::COMPLEX || t2 == type::COMPLEX) {
                return type::COMPLEX;
            }
            // TODO: mensagem de erro
            return type::UNDEFINED;
        }
        return t1;
    }
}

#endif /* FALK_TYPES_HPP */
