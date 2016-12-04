#include "types/array.hpp"
#include "types/matrix.hpp"

void falk::array::coerce_to(falk::type new_type) {
    auto new_priority = falk::priority.at(new_type);
    auto curr_priority = falk::priority.at(value_type);
    value_type = new_type;
    if (new_priority > curr_priority) {
        for (size_t i = 0; i < size(); i++) {
            values[i] = scalar(value_type, values[i].real(), values[i].imag());
        }
    }
}

falk::scalar falk::array::prepare(const scalar& value) {
    auto val_priority = falk::priority.at(value.inner_type());
    auto curr_priority = falk::priority.at(value_type);
    coerce_to(value.inner_type());
    if (val_priority < curr_priority) {
        return scalar(value_type, value.real(), value.imag());
    }
    return value;
}

falk::array& falk::array::assign(const scalar& rhs) {
    return assign(rhs.to_array(size()));
}

falk::array& falk::array::assign(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i].real() = rhs[i].real();
        values[i].imag() = rhs[i].imag();
    }
    return *this;
}

falk::array& falk::array::assign(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator+=(const scalar& rhs) {
    return *this = *this + rhs;
}

falk::array& falk::array::operator-=(const scalar& rhs) {
    return *this = *this - rhs;
}

falk::array& falk::array::operator*=(const scalar& rhs) {
    return *this = *this * rhs;
}

falk::array& falk::array::operator/=(const scalar& rhs) {
    return *this = *this / rhs;
}

falk::array& falk::array::operator%=(const scalar& rhs) {
    return *this = *this % rhs;
}

falk::array& falk::array::operator&=(const scalar& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY, falk::struct_t::SCALAR);
    fail = true;
    return *this;
}

falk::array& falk::array::operator|=(const scalar& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY, falk::struct_t::SCALAR);
    fail = true;
    return *this;
}

falk::array& falk::array::operator+=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator-=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator*=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator/=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator%=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_ASSIGNMENT>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator&=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator|=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array& falk::array::operator+=(const array& rhs) {
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

falk::array& falk::array::operator-=(const array& rhs) {
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

falk::array& falk::array::operator*=(const array& rhs) {
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

falk::array& falk::array::operator/=(const array& rhs) {
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

falk::array& falk::array::operator%=(const array& rhs) {
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

falk::array& falk::array::operator&=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::array& falk::array::operator|=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::array& falk::array::pow(const scalar& rhs) {
    for (size_t i = 0; i < size(); i++) {
        values[i].pow(rhs);
    }
    return *this;
}

falk::array& falk::array::pow(const array& rhs) {
    if (size() != rhs.size()) {
        err::semantic<Error::ARRAY_SIZE_MISMATCH>(size(), rhs.size());
        return *this;
    }

    for (size_t i = 0; i < size(); i++) {
        values[i].pow(rhs[i]);
    }

    return *this;
}

falk::array& falk::array::pow(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("matrix exponentiation");
    fail = true;
    return *this;
}

falk::matrix falk::array::to_matrix() const {
    matrix result;
    result.push_back(*this);
    return result;
}

falk::matrix falk::operator+(const falk::array& lhs, const falk::matrix& rhs) {
    return lhs.to_matrix() + rhs;
}

falk::matrix falk::operator-(const falk::array& lhs, const falk::matrix& rhs) {
    return lhs.to_matrix() - rhs;
}

falk::matrix falk::operator*(const falk::array& lhs, const falk::matrix& rhs) {
    return lhs.to_matrix() * rhs;
}

falk::matrix falk::operator/(const falk::array& lhs, const falk::matrix& rhs) {
    return lhs.to_matrix() / rhs;
}

falk::matrix falk::operator%(const falk::array& lhs, const falk::matrix& rhs) {
    return lhs.to_matrix() % rhs;
}
