
#ifndef FALK_TYPES_HPP
#define FALK_TYPES_HPP

#include <string>

namespace falk {
    template<typename T>
    struct definitions;

    enum class Type {
        UNDEFINED,
        REAL,
        COMPLEX,
        BOOL,
    };

    inline Type resolve_types(Type t1, Type t2) {
        if (t1 != t2) {
            if (t1 == Type::BOOL || t2 == Type::BOOL) {
                // TODO
            } else if (t1 == Type::COMPLEX || t2 == Type::COMPLEX) {
                return Type::COMPLEX;
            }
        }
        return t1;
    }
}

#endif /* FALK_TYPES_HPP */
