
#include <ostream>
#include "ev/scalar.hpp"

falk::ev::scalar falk::ev::scalar::pow(const scalar& lhs, const scalar& rhs) {
    auto result_type = falk::resolve_types(lhs._type, rhs._type);
    switch (result_type) {
        case falk::type::COMPLEX:
            return std::pow(lhs.complex(), rhs.complex());
        case falk::type::REAL:
            return {result_type, std::pow(lhs.real(), rhs.real())};
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}


falk::ev::scalar falk::ev::operator+(const scalar& lhs, const scalar& rhs) {
    auto type = falk::resolve_types(lhs.type(), rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            return lhs.complex() + rhs.complex();
        case falk::type::REAL:
            return lhs.real() + rhs.real();
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::scalar falk::ev::operator-(const scalar& lhs, const scalar& rhs) {
    auto type = falk::resolve_types(lhs.type(), rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            return lhs.complex() - rhs.complex();
        case falk::type::REAL:
            return lhs.real() - rhs.real();
        case falk::type::BOOL:
            // TODO: error
            return {};
        default:
            // TODO: throw a brick at the user
            return {};
    }
}

falk::ev::scalar falk::ev::operator*(const scalar& lhs, const scalar& rhs) {
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

falk::ev::scalar falk::ev::operator/(const scalar& lhs, const scalar& rhs) {
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

falk::ev::scalar falk::ev::operator%(const scalar& lhs, const scalar& rhs) {
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

falk::ev::scalar falk::ev::operator-(const scalar& n) {
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

std::ostream& falk::ev::operator<<(std::ostream& out, const scalar& n) {
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
