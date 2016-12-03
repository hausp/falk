#include "ev/array.hpp"
#include "ev/matrix.hpp"

falk::ev::array& falk::ev::array::operator=(const scalar& rhs) {
    return *this = rhs.to_array(size());
}

falk::ev::array& falk::ev::array::operator+=(const scalar& rhs) {
    return *this = *this + rhs;
}

falk::ev::array& falk::ev::array::operator-=(const scalar& rhs) {
    return *this = *this - rhs;
}

falk::ev::array& falk::ev::array::operator*=(const scalar& rhs) {
    return *this = *this * rhs;
}

falk::ev::array& falk::ev::array::operator/=(const scalar& rhs) {
    return *this = *this / rhs;
}

falk::ev::array& falk::ev::array::operator%=(const scalar& rhs) {
    return *this = *this % rhs;
}

falk::ev::array& falk::ev::array::operator=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::ev::array& falk::ev::array::operator+=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::ev::array& falk::ev::array::operator-=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::ev::array& falk::ev::array::operator*=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::ev::array& falk::ev::array::operator/=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::ev::array& falk::ev::array::operator%=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::ev::array& falk::ev::array::operator=(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i] = rhs[i];
    }
    return *this;
}

falk::ev::array& falk::ev::array::operator+=(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i] += rhs[i];
    }
    return *this;
}

falk::ev::array& falk::ev::array::operator-=(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i] -= rhs[i];
    }
    return *this;
}

falk::ev::array& falk::ev::array::operator*=(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i] *= rhs[i];
    }
    return *this;
}

falk::ev::array& falk::ev::array::operator/=(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i] /= rhs[i];
    }
    return *this;
}

falk::ev::array& falk::ev::array::operator%=(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i] %= rhs[i];                
    }
    return *this;
}

falk::ev::array& falk::ev::array::pow(const scalar& rhs) {
    for (size_t i = 0; i < size(); i++) {
        values[i].pow(rhs);
    }
    return *this;
}

falk::ev::array& falk::ev::array::pow(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i].pow(rhs[i]);
    }

    return *this;
}

falk::ev::array& falk::ev::array::pow(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("matrix exponentiation");
    fail = true;
    return *this;
}

falk::ev::matrix falk::ev::array::to_matrix() const {
    matrix result;
    result.push_back(*this);
    return result;
}

falk::ev::matrix falk::ev::operator+(const falk::ev::array& lhs, const falk::ev::matrix& rhs) {
    return lhs.to_matrix() + rhs;
}

falk::ev::matrix falk::ev::operator-(const falk::ev::array& lhs, const falk::ev::matrix& rhs) {
    return lhs.to_matrix() - rhs;
}

falk::ev::matrix falk::ev::operator*(const falk::ev::array& lhs, const falk::ev::matrix& rhs) {
    return lhs.to_matrix() * rhs;
}

falk::ev::matrix falk::ev::operator/(const falk::ev::array& lhs, const falk::ev::matrix& rhs) {
    return lhs.to_matrix() / rhs;
}

falk::ev::matrix falk::ev::operator%(const falk::ev::array& lhs, const falk::ev::matrix& rhs) {
    return lhs.to_matrix() % rhs;
}
