
#ifndef FALK_EVALUATOR_RVALUE
#define FALK_EVALUATOR_RVALUE

#include <ostream>
#include "base/types.hpp"

namespace falk {
    namespace ev {
        struct rvalue {
            rvalue(double v):
              type{falk::type::REAL}, real{v} { }
            
            rvalue(std::complex<double> v):
              type{falk::type::COMPLEX}, real{v.real()}, imag{v.imag()} { }
            
            rvalue(falk::type type = falk::type::UNDEFINED, double real = 0, double imag = 0):
              type{type}, real{real}, imag{imag} { }
            
            rvalue(bool v):
              type{falk::type::BOOL}, real{static_cast<double>(v)} { }

            std::complex<double> complex() const { return {real, imag}; }

            bool boolean() const { return static_cast<bool>(real); }
            
            operator std::complex<double>() const { return {real, imag}; }

            operator long() const { return static_cast<long>(real); }

            inline rvalue pow(const rvalue& rhs) {
                auto result_type = falk::resolve_types(type, rhs.type);
                switch (result_type) {
                    case falk::type::COMPLEX:
                        return std::pow(complex(), rhs);
                    case falk::type::REAL:
                        return {result_type, std::pow(real, rhs.real)};
                    case falk::type::BOOL:
                        // TODO: error
                        return {};
                    default:
                        // TODO: throw a brick at the user
                        return {};
                }
            }

            falk::type type;
            double real;
            double imag = 0;
        };

        inline rvalue operator+(const rvalue& lhs, const rvalue& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case falk::type::COMPLEX:
                    return {type, lhs.real + rhs.real, lhs.imag + rhs.imag};
                case falk::type::REAL:
                    return {type, lhs.real + rhs.real};
                case falk::type::BOOL:
                    // TODO: error
                    return {};
                default:
                    // TODO: throw a brick at the user
                    return {};
            }
        }

        inline rvalue operator-(const rvalue& lhs, const rvalue& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case falk::type::COMPLEX:
                    return {type, lhs.real - rhs.real, lhs.imag - rhs.imag};
                case falk::type::REAL:
                    return {type, lhs.real - rhs.real};
                case falk::type::BOOL:
                    // TODO: error
                    return {};
                default:
                    // TODO: throw a brick at the user
                    return {};
            }
        }

        inline rvalue operator-(const rvalue& n) {
            auto type = n.type;
            switch (type) {
                case falk::type::COMPLEX:
                case falk::type::REAL:
                    return {n.type, -n.real, -n.imag};
                case falk::type::BOOL:
                    // TODO: error
                    return {};
                default:
                    // TODO: throw a brick at the user
                    return {};
            }
        }

        inline rvalue operator*(const rvalue& lhs, const rvalue& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case falk::type::COMPLEX:
                    return lhs.complex() * rhs.complex();
                case falk::type::REAL:
                    return lhs.real * rhs.real;
                case falk::type::BOOL:
                    // TODO: error
                    return {};
                default:
                    // TODO: throw a brick at the user
                    return {};
            }
        }

        inline rvalue operator/(const rvalue& lhs, const rvalue& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case falk::type::COMPLEX:
                    return lhs / rhs;
                case falk::type::REAL:
                    return lhs.real / rhs.real;
                case falk::type::BOOL:
                    // TODO: throw a error
                    return {};
                default:
                    // TODO: throw a brick at the user
                    return {};
            }
        }

        inline rvalue operator%(const rvalue& lhs, const rvalue& rhs) {
            auto type = falk::resolve_types(lhs.type, rhs.type);
            switch (type) {
                case falk::type::COMPLEX:
                    // TODO
                    return {};
                case falk::type::REAL:
                    return std::fmod(lhs.real, rhs.real);
                case falk::type::BOOL:
                    // TODO: throw a error
                    return {};
                default:
                    // TODO: throw a brick at the user
                    return {};
            }
        }


        inline std::ostream& operator<<(std::ostream& out, const rvalue& n) {
            auto type = n.type;
            switch (type) {
                case falk::type::COMPLEX:
                    if (std::signbit(n.imag)) {
                        out << n.real << " - " << std::abs(n.imag) << "i";
                    } else {
                        out << n.real << " + " << n.imag << "i";
                    }
                    break;
                case falk::type::REAL:
                    out << n.real;
                    break;
                case falk::type::BOOL:
                    out << std::boolalpha << n << std::noboolalpha;
                    break;
                default:;
            }
            return out;
        }
    }
}

#endif /* FALK_EVALUATOR_RVALUE */
