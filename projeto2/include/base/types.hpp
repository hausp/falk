
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

    // temporary values
    struct rvalue {
        std::string content;
        Type type;
    };
}

#endif /* FALK_TYPES_HPP */
