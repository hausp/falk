#ifndef FALK_TYPES_HPP
#define FALK_TYPES_HPP

#include <unordered_map>

namespace falk {
    namespace fundamental {
        enum class type {
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
            UNDECLARED,
            VARIABLE,
            FUNCTION,
        };
    }

    using type = fundamental::type;
    using struct_t = structural::type;
}

namespace std {
    template<>
    struct hash<falk::type> {
        inline size_t operator()(falk::type type) const {
            return static_cast<int>(type);
        }
    };
}

namespace falk {
    const std::unordered_map<falk::type, unsigned> priority = {
        {falk::type::BOOL, 0},
        {falk::type::REAL, 1},
        {falk::type::COMPLEX, 2},
    };

    inline type resolve_types(type t1, type t2) {
        if (t1 == type::COMPLEX || t2 == type::COMPLEX) {
            return type::COMPLEX;
        } else if (t1 == type::REAL || t2 == type::REAL) {
            return type::REAL;
        }
        return type::BOOL;
    }

    // inline scalar coerce(type t, const scalar& value) {
    //     if (t == value.type()) {
    //         return value;
    //     }

    //     if (t == type::REAL) {
    //         return scalar(t, value.real());
    //     }

    //     if (t == type::BOOL) {
    //         return scalar(t, value.real() != 0);
    //     }
    // }
}

#endif /* FALK_TYPES_HPP */
