
#ifndef FALK_EVALUATOR_RVALUE
#define FALK_EVALUATOR_RVALUE

#include <ostream>
#include "base/types.hpp"

namespace falk {
    namespace ev {
        struct numeric {
            Type type;
            double real;
            double imag = 0;
        };

        inline numeric operator+(const numeric& lhs, const numeric& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            if (type == Type::COMPLEX) {
                return {type, lhs.real + rhs.real, lhs.imag + rhs.imag};
            } else {
                return {type, lhs.real + rhs.real};
            }
        }

        inline numeric operator-(const numeric& lhs, const numeric& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            if (type == Type::COMPLEX) {
                return {type, lhs.real - rhs.real, lhs.imag - rhs.imag};
            } else {
                return {type, lhs.real - rhs.real};
            }
        }

        inline numeric operator-(const numeric& n) {
            return {n.type, -n.real, -n.imag};
        }

        inline numeric operator*(const numeric& lhs, const numeric& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            if (type == Type::COMPLEX) {
                // TODO
                return numeric{};
            } else {
                return {type, lhs.real * rhs.real};
            }
        }

        inline numeric operator/(const numeric& lhs, const numeric& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            if (type == Type::COMPLEX) {
                // TODO
                return numeric{};
            } else {
                return {type, lhs.real / rhs.real};
            }
        }

        inline numeric operator%(const numeric& lhs, const numeric& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            if (type == Type::COMPLEX) {
                // TODO
                return numeric{};
            } else {
                // TODO: is this real?
                return {
                    type,
                    static_cast<double>(
                        static_cast<long>(lhs.real) % static_cast<long>(rhs.real)
                    )
                };
            }
        }

        inline std::ostream& operator<<(std::ostream& out, const numeric& n) {
            if (n.type == Type::COMPLEX) {
                // TODO: improve this
                out << n.real << " + " << n.imag << "i";
            } else {
                out << n.real;
            }
            return out;
        }
    }
}

#endif /* FALK_EVALUATOR_RVALUE */
