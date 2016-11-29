
#include <ostream>
#include "ev/scalar.hpp"

falk::ev::scalar& falk::ev::scalar::pow(const scalar& rhs) {
    // TODO: implement this
    return *this;
}

falk::ev::scalar& falk::ev::scalar::operator+=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            _real += rhs._real;
            _imag += rhs._imag;
            break;
        case falk::type::REAL:
            _real += rhs._real;
            break;
        case falk::type::BOOL:
            // TODO: error
            fail = true;
            break;
        default:
            // TODO: throw a brick at the user
            fail = true;
    }
    return *this;
}

falk::ev::scalar& falk::ev::scalar::operator-=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            _real -= rhs._real;
            _imag -= rhs._imag;
            break;
        case falk::type::REAL:
            _real -= rhs._real;
            break;
        case falk::type::BOOL:
            // TODO: error
            fail = true;
            break;
        default:
            // TODO: throw a brick at the user
            fail = true;
    }
    return *this;
}

falk::ev::scalar& falk::ev::scalar::operator*=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            *this = complex() * rhs.complex();
            break;
        case falk::type::REAL:
            _real *= rhs.real();
            break;
        case falk::type::BOOL:
            // TODO: error
            fail = true;
            break;
        default:
            // TODO: throw a brick at the user
            fail = true;
    }
    return *this;
}

falk::ev::scalar& falk::ev::scalar::operator/=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            *this = complex() / rhs.complex();
            break;
        case falk::type::REAL:
            _real /= rhs.real();
            break;
        case falk::type::BOOL:
            // TODO: throw a error
            fail = true;
            break;
        default:
            // TODO: throw a brick at the user
            fail = true;
    }
    return *this;
}

falk::ev::scalar& falk::ev::scalar::operator%=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            // TODO: error (operation not allowed)
            fail = true;
            break;
        case falk::type::REAL:
            _real = std::fmod(real(), rhs.real());
            break;
        case falk::type::BOOL:
            // TODO: throw a error
            fail = true;
            break;
        default:
            // TODO: throw a brick at the user
            fail = true;
    }
    return *this;
}

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
    auto copy = lhs;
    return copy += rhs;
}

falk::ev::scalar falk::ev::operator-(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    return copy -= rhs;
}

falk::ev::scalar falk::ev::operator*(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    return copy *= rhs;
}

falk::ev::scalar falk::ev::operator/(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    return copy /= rhs;
}

falk::ev::scalar falk::ev::operator%(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    return copy %= rhs;
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
