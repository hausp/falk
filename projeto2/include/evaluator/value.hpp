
#ifndef FALK_EVALUATOR_VALUE
#define FALK_EVALUATOR_VALUE

#include <ostream>
#include "base/types.hpp"

namespace falk {
    namespace ev {
        struct value {
            // TODO

            value(double v) : type{Type::REAL}, real{v} { }
            value(std::complex<double> v) : type{Type::COMPLEX}, real{v.real()}, imag{v.imag()} { }
            value(Type type = Type::UNDEFINED, double real = 0, double imag = 0) : type{type}, real{real}, imag{imag} { }
            value(bool v) : type{Type::BOOL}, real{static_cast<double>(v)} { }

            Type type;
            double real;
            double imag = 0;

            inline value pow(const value& rhs) {
                auto result_type = falk::resolve_types(type, rhs.type);
                switch (result_type) {
                    case Type::COMPLEX:
                        // TODO
                        return value{};
                    case Type::REAL:
                        // TODO: is this real?
                        return value{result_type, std::pow(real, rhs.real)};
                    case Type::BOOL:
                        // TODO: error
                        return value{};
                    default:
                        // TODO: throw a brick at the user
                        return value{};
                }
            }
        };

        // constexpr auto TRUE = value(true);
        // constexpr auto FALSE = value{Type::BOOL, 0};

        inline value operator+(const value& lhs, const value& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case Type::COMPLEX:
                    return value{type, lhs.real + rhs.real, lhs.imag + rhs.imag};
                case Type::REAL:
                    return value{type, lhs.real + rhs.real};
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
                    return value{type, lhs.real - rhs.real, lhs.imag - rhs.imag};
                case Type::REAL:
                    return value{type, lhs.real - rhs.real};
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
                    return value{type, lhs.real * rhs.real};
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
                    return value{type, lhs.real / rhs.real};
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
