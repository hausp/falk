
#ifndef FALK_EVALUATOR_VALUE
#define FALK_EVALUATOR_VALUE

#include <ostream>
#include "base/types.hpp"

namespace falk {
    namespace ev {
        struct value {
            // TODO

            Type type;
            double real;
            double imag = 0;
        };

        constexpr auto TRUE = value{Type::BOOL, 1};
        constexpr auto FALSE = value{Type::BOOL, 0};

        inline value operator+(const value& lhs, const value& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case Type::COMPLEX:
                    return {type, lhs.real + rhs.real, lhs.imag + rhs.imag};
                case Type::REAL:
                    return {type, lhs.real + rhs.real};
                case Type::BOOL:
                    // TODO: error
                    return value{};
                default:
                    // TODO: throw a brick at the user
                    return value{};
            }
        }

        inline value operator-(const value& lhs, const value& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case Type::COMPLEX:
                    return {type, lhs.real - rhs.real, lhs.imag - rhs.imag};
                case Type::REAL:
                    return {type, lhs.real - rhs.real};
                case Type::BOOL:
                    // TODO: error
                    return value{};
                default:
                    // TODO: throw a brick at the user
                    return value{};
            }
        }

        inline value operator-(const value& n) {
            auto type = n.type;
            switch (type) {
                case Type::COMPLEX:
                case Type::REAL:
                    return {n.type, -n.real, -n.imag};
                case Type::BOOL:
                    // TODO: error
                    return value{};
                default:
                    // TODO: throw a brick at the user
                    return value{};
            }
        }

        inline value operator*(const value& lhs, const value& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case Type::COMPLEX:
                    // TODO
                    return value{};
                case Type::REAL:
                    return {type, lhs.real * rhs.real};
                case Type::BOOL:
                    // TODO: error
                    return value{};
                default:
                    // TODO: throw a brick at the user
                    return value{};
            }
        }

        inline value operator/(const value& lhs, const value& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case Type::COMPLEX:
                    // TODO
                    return value{};
                case Type::REAL:
                    return {type, lhs.real / rhs.real};
                case Type::BOOL:
                    // TODO: error
                    return value{};
                default:
                    // TODO: throw a brick at the user
                    return value{};
            }
        }

        inline value operator%(const value& lhs, const value& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case Type::COMPLEX:
                    // TODO
                    return value{};
                case Type::REAL:
                    // TODO: is this real?
                    return {
                        type,
                        static_cast<double>(
                            static_cast<long>(lhs.real) % static_cast<long>(rhs.real)
                        )
                    };
                case Type::BOOL:
                    // TODO: error
                    return value{};
                default:
                    // TODO: throw a brick at the user
                    return value{};
            }
        }

        inline std::ostream& operator<<(std::ostream& out, const value& n) {
            auto type = n.type;
            switch (type) {
                case Type::COMPLEX:
                    // TODO: improve this
                    out << n.real << " + " << n.imag << "i";
                    break;
                case Type::REAL:
                    out << n.real;
                    break;
                case Type::BOOL:
                    out << std::boolalpha << n << std::noboolalpha;
                    break;
                default:
                    // TODO
                    break;
            }
            return out;
        }
    }
}

#endif /* FALK_EVALUATOR_VALUE */
