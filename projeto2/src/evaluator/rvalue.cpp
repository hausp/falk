
#include <ostream>
#include "evaluator/rvalue.hpp"

falk::ev::rvalue falk::ev::rvalue::pow(const rvalue& rhs) {
    auto result_type = falk::resolve_types(_type, rhs._type);
    switch (result_type) {
        case falk::type::COMPLEX:
            return std::pow(complex(), rhs);
        case falk::type::REAL:
            return {result_type, std::pow(_real, rhs._real)};
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::rvalue falk::ev::operator+(const rvalue& lhs, const rvalue& rhs) {
    auto type = falk::resolve_types(lhs.type(), rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            return {type, lhs.real() + rhs.real(), lhs.imag() + rhs.imag()};
        case falk::type::REAL:
            return {type, lhs.real() + rhs.real()};
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::rvalue falk::ev::operator-(const rvalue& lhs, const rvalue& rhs) {
    auto type = falk::resolve_types(lhs.type(), rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            return {type, lhs.real() - rhs.real(), lhs.imag() - rhs.imag()};
        case falk::type::REAL:
            return {type, lhs.real() - rhs.real()};
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::rvalue falk::ev::operator*(const rvalue& lhs, const rvalue& rhs) {
    auto type = falk::resolve_types(lhs.type(), rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            return lhs.complex() * rhs.complex();
        case falk::type::REAL:
            return lhs.real() * rhs.real();
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::rvalue falk::ev::operator/(const rvalue& lhs, const rvalue& rhs) {
    auto type = falk::resolve_types(lhs.type(), rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            return lhs.complex() / rhs.complex();
        case falk::type::REAL:
            return lhs.real() / rhs.real();
        case falk::type::BOOL:
            // TODO: throw a error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::rvalue falk::ev::operator%(const rvalue& lhs, const rvalue& rhs) {
    auto type = falk::resolve_types(lhs.type(), rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            // TODO
            return {};
        case falk::type::REAL:
            return std::fmod(lhs.real(), rhs.real());
        case falk::type::BOOL:
            // TODO: throw a error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::rvalue falk::ev::operator-(const rvalue& n) {
    auto type = n.type();
    switch (type) {
        case falk::type::COMPLEX:
        case falk::type::REAL:
            return {n.type(), -n.real(), -n.imag()};
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

std::ostream& falk::ev::operator<<(std::ostream& out, const rvalue& n) {
    auto type = n.type();
    switch (type) {
        case falk::type::COMPLEX:
            if (std::signbit(n.imag())) {
                out << n.real() << " - " << std::abs(n.imag()) << "i";
            } else {
                out << n.real() << " + " << n.imag() << "i";
            }
            break;
        case falk::type::REAL:
            out << n.real();
            break;
        case falk::type::BOOL:
            out << std::boolalpha << n.boolean() << std::noboolalpha;
            break;
        default:;
    }
    return out;
}
