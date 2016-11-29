
#ifndef FALK_OPERATORS_HPP
#define FALK_OPERATORS_HPP

namespace falk {
    // The first template argument specifies the type of operation.
    // The second argument specifies the specific operation.
    // The third argument specifies if the operation is a composite
    // assignment.
    template<typename Type, Type, size_t = 2, bool = false>
    struct operation;

    struct op {
        enum class arithmetic {
            ADD,
            SUB,
            DIV,
            MULT,
            POW,
            MOD,
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
        };

        // Arithmetic operations
        using ADD = operation<arithmetic, arithmetic::ADD>;
        using SUB = operation<arithmetic, arithmetic::SUB>;
        using MULT = operation<arithmetic, arithmetic::MULT>;
        using DIV = operation<arithmetic, arithmetic::DIV>;
        using POW = operation<arithmetic, arithmetic::POW>;
        using MOD = operation<arithmetic, arithmetic::MOD>;
        using SUB_UNARY  = operation<arithmetic, arithmetic::SUB, 1>;
        using ADD_ASSIGN = operation<arithmetic, arithmetic::ADD, 2, true>;
        using SUB_ASSIGN = operation<arithmetic, arithmetic::SUB, 2, true>;
        using MULT_ASSIGN = operation<arithmetic, arithmetic::MULT, 2, true>;
        using DIV_ASSIGN = operation<arithmetic, arithmetic::DIV, 2, true>;
        using POW_ASSIGN = operation<arithmetic, arithmetic::POW, 2, true>;
        using MOD_ASSIGN = operation<arithmetic, arithmetic::MOD, 2, true>;
        // Comparison operations
        using LT = operation<comparison, comparison::LT>;
        using GT = operation<comparison, comparison::GT>;
        using LE = operation<comparison, comparison::LE>;
        using GE = operation<comparison, comparison::GE>;
        using EQ = operation<comparison, comparison::EQ>;
        using NE = operation<comparison, comparison::NE>;
        // Logic operations
        using AND = operation<logic, logic::AND>;
        using OR = operation<logic, logic::OR>;
        using NOT = operation<logic, logic::NOT>;
        using AND_ASSIGN = operation<logic, logic::AND, 2, true>;
        using OR_ASSIGN = operation<logic, logic::OR, 2, true>;
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::ADD, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs + rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::SUB, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs - rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::SUB, 1, false> {
        static constexpr size_t arity() { return 1; }
        
        template<typename T>
        T operator()(const T& operand) const {
            return -operand;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::MULT, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs * rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::DIV, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs / rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::POW, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return LH::pow(lhs, rhs);
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::MOD, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs % rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::ADD, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename Variable, typename Rvalue>
        Variable& operator()(Variable& lhs, const Rvalue& rhs) const {
            return lhs += rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::SUB, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs -= rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::MULT, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs *= rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::DIV, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs /= rhs;
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::POW, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs.pow(rhs);
        }
    };

    template<>
    struct operation<op::arithmetic, op::arithmetic::MOD, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs %= rhs;
        }
    };

    template<>
    struct operation<op::comparison, op::comparison::LT, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs < rhs;
        }
    };

    template<>
    struct operation<op::comparison, op::comparison::GT, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs > rhs;
        }
    };

    template<>
    struct operation<op::comparison, op::comparison::LE, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs <= rhs;
        }
    };

    template<>
    struct operation<op::comparison, op::comparison::GE, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs >= rhs;
        }
    };

    template<>
    struct operation<op::comparison, op::comparison::EQ, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs == rhs;
        }
    };

    template<>
    struct operation<op::comparison, op::comparison::NE, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs != rhs;
        }
    };

    template<>
    struct operation<op::logic, op::logic::AND, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs && rhs;
        }
    };

    template<>
    struct operation<op::logic, op::logic::OR, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs || rhs;
        }
    };

    template<>
    struct operation<op::logic, op::logic::NOT, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& operand) const {
            return !operand;
        }
    };
}

#endif /* FALK_OPERATORS_HPP */
