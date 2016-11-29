#include "ev/array.hpp"
#include "ev/matrix.hpp"

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
