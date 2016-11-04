
#ifndef FALK_DEFINITIONS_HPP
#define FALK_DEFINITIONS_HPP

#include <complex>
#include "interpreter/base.hpp"

namespace falk {
    using real = double;
    using complex = std::complex<double>;

    enum class Types {
        UNDEFINED,
        REAL,
        COMPLEX,
    }

    namespace op {
        enum class Arithmetical {
            ADD,
            SUB,
            DIV,
            MULT,
            POW,
            MOD,
        };

        enum class Comparison {
            LT,
            GT,
            LE,
            GE,
            EQ,
            NE,
        };
        
        enum class Logical {
            AND,
            OR,
            NOT,
        };
    }

    template<typename T>
    T pow(const T&, const T&);
}

#endif /* FALK_DEFINITIONS_HPP */
