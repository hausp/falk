
#include <ostream>
#include "types/scalar.hpp"
#include "types/array.hpp"
#include "types/matrix.hpp"

falk::scalar& falk::scalar::pow(const scalar& rhs) {
    auto result_type = falk::resolve_types(_type, rhs._type);
    switch (result_type) {
        case falk::type::COMPLEX: {
            auto result = std::pow(complex(), rhs.complex());
            _real = result.real();
            _imag = result.imag();
            break;
        }
        case falk::type::REAL:
        case falk::type::BOOL:
            _real = std::pow(_real, rhs.real());
            break;
    }

    return *this;
}

falk::scalar& falk::scalar::pow(const array& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("array exponentiation");
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::pow(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("matrix exponentiation");
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::assign(const scalar& rhs) {
    _real = rhs._real;
    _imag = rhs._imag;
    return *this;
}

falk::scalar& falk::scalar::assign(const array& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::assign(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator+=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            _real += rhs._real;
            _imag += rhs._imag;
            break;
        case falk::type::REAL:
        case falk::type::BOOL:
            _real += rhs._real;
            break;
    }
    return *this;
}

falk::scalar& falk::scalar::operator-=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            _real -= rhs._real;
            _imag -= rhs._imag;
            break;
        case falk::type::REAL:
        case falk::type::BOOL:
            _real -= rhs._real;
            break;
    }
    return *this;
}

falk::scalar& falk::scalar::operator*=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            *this = complex() * rhs.complex();
            break;
        case falk::type::REAL:
        case falk::type::BOOL:
            _real *= rhs.real();
            break;
    }
    return *this;
}

falk::scalar& falk::scalar::operator/=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            *this = complex() / rhs.complex();
            break;
        case falk::type::REAL:
        case falk::type::BOOL:
            _real /= rhs.real();
            break;
    }
    return *this;
}

falk::scalar& falk::scalar::operator%=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
            err::semantic<Error::ILLEGAL_OPERATION>("complex modulus");
            fail = true;
            break;
        case falk::type::REAL:
        case falk::type::BOOL:
            _real = std::fmod(real(), rhs.real());
            break;
    }
    return *this;
}

falk::scalar& falk::scalar::operator&=(const scalar& rhs) {
    switch (_type) {
        case falk::type::COMPLEX:
        case falk::type::REAL:
            err::semantic<Error::ILLEGAL_ASSIGNMENT>(_type,
                                                     falk::type::BOOL);
            fail = true;
            break;
        case falk::type::BOOL:
            _real = _real && rhs._real;
            break;
    }
    return *this;
}

falk::scalar& falk::scalar::operator|=(const scalar& rhs) {
    auto type = falk::resolve_types(_type, rhs.type());
    switch (type) {
        case falk::type::COMPLEX:
        case falk::type::REAL:
            err::semantic<Error::ILLEGAL_ASSIGNMENT>(type,
                                                     falk::type::BOOL);
            fail = true;
            break;
        case falk::type::BOOL:
            _real = _real || rhs._real;
            break;
    }
    return *this;
}

falk::scalar& falk::scalar::operator+=(const array& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator-=(const array& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator*=(const array& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator/=(const array& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator%=(const array& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator&=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator|=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::SCALAR, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator+=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator-=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator*=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator/=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator%=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator&=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar& falk::scalar::operator|=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::SCALAR, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::scalar falk::scalar::pow(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    return copy.pow(rhs);
}

falk::array falk::scalar::pow(const scalar& lhs, const array& rhs) {
    return lhs.to_array(rhs.size()) * rhs;
}

falk::matrix falk::scalar::pow(const scalar& lhs, const matrix& rhs) {
    auto num_rows = rhs.row_count();
    auto num_columns = rhs.column_count();
    auto result = matrix(num_rows, num_columns);
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            result.at(i, j) = scalar::pow(lhs, rhs.at(i, j));
        }
    }
    return result;
}

falk::scalar falk::operator+(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    copy.type(falk::resolve_types(lhs.type(), rhs.type()));
    return copy += rhs;
}

falk::scalar falk::operator-(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    copy.type(falk::resolve_types(lhs.type(), rhs.type()));
    return copy -= rhs;
}

falk::scalar falk::operator*(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    copy.type(falk::resolve_types(lhs.type(), rhs.type()));
    return copy *= rhs;
}

falk::scalar falk::operator/(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    copy.type(falk::resolve_types(lhs.type(), rhs.type()));
    return copy /= rhs;
}

falk::scalar falk::operator%(const scalar& lhs, const scalar& rhs) {
    auto copy = lhs;
    copy.type(falk::resolve_types(lhs.type(), rhs.type()));
    return copy %= rhs;
}

falk::scalar falk::operator-(const scalar& n) {
    auto type = n.type();
    switch (type) {
        case falk::type::COMPLEX:
        case falk::type::REAL:
        case falk::type::BOOL:
            return {n.type(), -n.real(), -n.imag()};
    }
}

falk::array falk::scalar::to_array(size_t size) const {
    array result;
    for (size_t i = 0; i < size; i++) {
        result.push_back(*this);
    }
    return result;
}

falk::array falk::operator+(const scalar& lhs, const array& rhs) {
    return lhs.to_array(rhs.size()) + rhs;
}

falk::array falk::operator-(const scalar& lhs, const array& rhs) {
    return lhs.to_array(rhs.size()) - rhs;
}

falk::array falk::operator*(const scalar& lhs, const array& rhs) {
    return lhs.to_array(rhs.size()) * rhs;
}

falk::array falk::operator/(const scalar& lhs, const array& rhs) {
    return lhs.to_array(rhs.size()) / rhs;
}

falk::array falk::operator%(const scalar& lhs, const array& rhs) {
    return lhs.to_array(rhs.size()) % rhs;
}

falk::matrix falk::operator+(const scalar& lhs, const matrix& rhs) {
    auto num_rows = rhs.row_count();
    auto num_columns = rhs.column_count();
    auto result = matrix(num_rows, num_columns);
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            result.at(i, j) = lhs + rhs.at(i, j);
        }
    }
    return result;
}

falk::matrix falk::operator-(const scalar& lhs, const matrix& rhs) {
    auto num_rows = rhs.row_count();
    auto num_columns = rhs.column_count();
    auto result = matrix(num_rows, num_columns);
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            result.at(i, j) = lhs - rhs.at(i, j);
        }
    }
    return result;
}

falk::matrix falk::operator*(const scalar& lhs, const matrix& rhs) {
    auto num_rows = rhs.row_count();
    auto num_columns = rhs.column_count();
    auto result = matrix(num_rows, num_columns);
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            result.at(i, j) = lhs * rhs.at(i, j);
        }
    }
    return result;
}

falk::matrix falk::operator/(const scalar& lhs, const matrix& rhs) {
    auto num_rows = rhs.row_count();
    auto num_columns = rhs.column_count();
    auto result = matrix(num_rows, num_columns);
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            result.at(i, j) = lhs / rhs.at(i, j);
        }
    }
    return result;
}

falk::matrix falk::operator%(const scalar& lhs, const matrix& rhs) {
    auto num_rows = rhs.row_count();
    auto num_columns = rhs.column_count();
    auto result = matrix(num_rows, num_columns);
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            result.at(i, j) = lhs % rhs.at(i, j);
        }
    }
    return result;
}

std::ostream& falk::operator<<(std::ostream& out, const scalar& n) {
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
    }
    return out;
}
