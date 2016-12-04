
#ifndef FALK_OPERATORS_HPP
#define FALK_OPERATORS_HPP

namespace falk {
    struct op {
        // The first template argument specifies the type of operation.
        // The second argument specifies the specific operation.
        // The third argument specifies the arity of the operation.
        // The fourth argument specifies if the operation is a composite
        // assignment.
        template<typename Type, Type, size_t = 2>
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

        enum class assignment {
            DIRECT,
            ADD,
            SUB,
            DIV,
            MULT,
            POW,
            MOD,
            AND,
            OR,
        };
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::ADD, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs + rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::SUB, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs - rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::SUB, 1> {
        static constexpr size_t arity() { return 1; }
        
        template<typename T>
        T operator()(const T& operand) const {
            return -operand;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::MULT, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs * rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::DIV, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs / rhs;
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::POW, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return LH::pow(lhs, rhs);
        }
    };

    template<>
    struct op::callback<op::arithmetic, op::arithmetic::MOD, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs % rhs;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::ADD, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs += rhs;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::SUB, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs -= rhs;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::MULT, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs *= rhs;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::DIV, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs /= rhs;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::POW, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs.pow(rhs);
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::MOD, 2> {
        static constexpr size_t arity() { return 2; }
        
        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs %= rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::LT, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs < rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::GT, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs > rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::LE, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs <= rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::GE, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs >= rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::EQ, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs == rhs;
        }
    };

    template<>
    struct op::callback<op::comparison, op::comparison::NE, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs != rhs;
        }
    };

    template<>
    struct op::callback<op::logic, op::logic::AND, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs && rhs;
        }
    };

    template<>
    struct op::callback<op::logic, op::logic::OR, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(const LH& lhs, const RH& rhs) const {
            return lhs || rhs;
        }
    };

    template<>
    struct op::callback<op::logic, op::logic::NOT, 1> {
        static constexpr size_t arity() { return 1; }

        template<typename RH>
        decltype(auto) operator()(const RH& operand) const {
            return !operand;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::AND, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs &= rhs;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::OR, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs |= rhs;
        }
    };

    template<>
    struct op::callback<op::assignment, op::assignment::DIRECT, 2> {
        static constexpr size_t arity() { return 2; }

        template<typename LH, typename RH>
        decltype(auto) operator()(LH& lhs, const RH& rhs) const {
            return lhs.assign(rhs);
        }
    };

    template<typename LH, typename RH>
    decltype(auto) make_comparison(op::comparison comp, LH lhs, RH rhs) {
        switch (comp) {
            case op::comparison::LT:
                return lhs < rhs;
            case op::comparison::GT:
                return lhs > rhs;
            case op::comparison::LE:
                return lhs <= rhs;
            case op::comparison::GE:
                return lhs >= rhs;
            case op::comparison::EQ:
                return lhs == rhs;
            case op::comparison::NE:
                return lhs != rhs;
        }
    }

    template<typename LH, typename RH>
    decltype(auto) make_assignment(op::assignment comp, LH lhs, RH rhs) {
        switch (comp) {
            case op::assignment::DIRECT:
                return lhs = rhs;
            case op::assignment::ADD:
                return lhs += rhs;
            case op::assignment::SUB:
                return lhs -= rhs;
            case op::assignment::DIV:
                return lhs /= rhs;
            case op::assignment::MULT:
                return lhs *= rhs;
            case op::assignment::POW:
                return lhs.pow(rhs);
            case op::assignment::MOD:
                return lhs %= rhs;
            case op::assignment::AND:
                return lhs &= rhs;
            case op::assignment::OR:
                return lhs |= rhs;
        }
    }
}

#endif /* FALK_OPERATORS_HPP */
