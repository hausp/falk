
#ifndef FALK_OPERATORS_HPP
#define FALK_OPERATORS_HPP

namespace falk {
    template<typename Type, Type Op>
    struct operation;

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

        using ADD  = operation<op::arithmetic, op::arithmetic::ADD>;
        using SUB  = operation<op::arithmetic, op::arithmetic::SUB>;
        using MULT = operation<op::arithmetic, op::arithmetic::MULT>;
        using DIV  = operation<op::arithmetic, op::arithmetic::DIV>;
        using POW  = operation<op::arithmetic, op::arithmetic::POW>;
        using MOD  = operation<op::arithmetic, op::arithmetic::MOD>;

        using ADD_ASSIGN  = operation<op::arithmetic, op::arithmetic::ADD_ASSIGN>;
        using SUB_ASSIGN  = operation<op::arithmetic, op::arithmetic::SUB_ASSIGN>;
        using MULT_ASSIGN = operation<op::arithmetic, op::arithmetic::MULT_ASSIGN>;
        using DIV_ASSIGN  = operation<op::arithmetic, op::arithmetic::DIV_ASSIGN>;
        using POW_ASSIGN  = operation<op::arithmetic, op::arithmetic::POW_ASSIGN>;
        using MOD_ASSIGN  = operation<op::arithmetic, op::arithmetic::MOD_ASSIGN>;

        using LT = operation<op::comparison, op::comparison::LT>;
        using GT = operation<op::comparison, op::comparison::GT>;
        using LE = operation<op::comparison, op::comparison::LE>;
        using GE = operation<op::comparison, op::comparison::GE>;
        using EQ = operation<op::comparison, op::comparison::EQ>;
        using NE = operation<op::comparison, op::comparison::NE>;

        using AND = operation<op::logic, op::logic::AND>;
        using OR  = operation<op::logic, op::logic::OR>;
        using NOT = operation<op::logic, op::logic::NOT>;

        using AND_ASSIGN = operation<op::logic, op::logic::AND_ASSIGN>;
        using OR_ASSIGN  = operation<op::logic, op::comparison::OR_ASSIGN>;
    }

    template<op::arithmetic Op>
    struct operation<op::arithmetic, Op> {
        static constexpr size_t arity() { return 2; }
    };

    template<op::comparison Op>
    struct operation<op::comparison, Op> {
        static constexpr size_t arity() { return 2; }
    };

    template<op::logic Op>
    struct operation<op::logic, Op> {
        static constexpr size_t arity() { return 2; }
    };
}

#endif /* FALK_OPERATORS_HPP */
