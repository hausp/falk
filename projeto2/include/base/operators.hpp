
#ifndef FALK_OPERATORS_HPP
#define FALK_OPERATORS_HPP

namespace falk {
    namespace op {
        enum class arithmetic {
            ADD,
            SUB,
            DIV,
            MULT,
            POW,
            MOD,
            ADD_ASSIGN,
            SUB_ASSIGN,
            DIV_ASSIGN,
            MULT_ASSIGN,
            POW_ASSIGN,
            MOD_ASSIGN,
        };

        enum class comparison {
            LT,
            GT,
            LE,
            GE,
            EQ,
            NE,
        };

        enum class logic {
            AND,
            OR,
            NOT,
            AND_ASSIGN,
            OR_ASSIGN,
        };
    }

    template<typename Type, size_t Arity>
    struct operation {
        static constexpr size_t arity() {return Arity; }
        
        Type type;
    };
}

#endif /* FALK_OPERATORS_HPP */
