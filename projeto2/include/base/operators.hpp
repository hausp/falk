
#ifndef FALK_OPERATORS_HPP
#define FALK_OPERATORS_HPP

namespace falk {
    struct op {
        // The first template argument specifies the type of operation.
        // The second argument specifies the specific operation.
        // The third argument specifies the arity of the operation.
        // The fourth argument specifies if the operation is a composite
        // assignment.
        template<typename Type, Type, size_t = 2, bool = false>
        struct callback;

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
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::ADD, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs + rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::SUB, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs - rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::SUB, 1, false> {
        static constexpr size_t arity() { return 1; }
        
        template<typename T>
        T operator()(const T& operand) const {
            return -operand;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::MULT, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs * rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::DIV, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs / rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::POW, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return LH::pow(lhs, rhs);
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::MOD, 2, false> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        auto operator()(const LH& lhs, const RH& rhs) const {
            return lhs % rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::ADD, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename Variable, typename Rvalue>
        Variable& operator()(Variable& lhs, const Rvalue& rhs) const {
            return lhs += rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::SUB, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs -= rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::MULT, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs *= rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::DIV, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs /= rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::POW, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs.pow(rhs);
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::MOD, 2, true> {
        static constexpr size_t arity() { return 2; }
        
        template<typename T>
        T& operator()(T& lhs, const T& rhs) const {
            return lhs %= rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::LT, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs < rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::GT, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs > rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::LE, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs <= rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::GE, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs >= rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::EQ, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs == rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::NE, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs != rhs;
        }
    };

    template<>
    struct op::callback<op::logic, op::logic::AND, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs && rhs;
        }
    };

    template<>
    struct op::callback<op::logic, op::logic::OR, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs || rhs;
        }
    };

    template<>
    struct op::callback<op::logic, op::logic::NOT, 2, false> {
        static constexpr size_t arity() { return 2; }

        template<typename T>
        bool operator()(const T& operand) const {
            return !operand;
        }
    };
}

#endif /* FALK_OPERATORS_HPP */
