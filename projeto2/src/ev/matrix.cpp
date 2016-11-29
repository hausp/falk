#include "ev/matrix.hpp"

falk::ev::scalar falk::ev::matrix::invalid;

falk::ev::matrix falk::ev::operator*(const matrix& lhs, const matrix& rhs) {
    if (lhs.column_count() != rhs.row_count()) {
        // TODO: error (incompatible operands)
        return invalid_matrix;
    }

    auto num_rows = lhs.row_count();
    auto num_columns = rhs.column_count();
    auto result = matrix(num_rows, num_columns);
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            scalar sum;
            for (size_t k = 0; k < lhs.column_count(); k++) {
                auto factor = lhs.at(i, k) * rhs.at(k, j);
                if (k == 0) {
                    sum = factor;
                } else {
                    sum += factor;
                }
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

std::ostream& falk::ev::operator<<(std::ostream& out, const falk::ev::matrix& mat) {
    out << "[";
    for (size_t i = 0; i < mat.row_count(); i++) {
        if (i != 0) {
           out << ", ";
        }
        out << "[";
        for (size_t j = 0; j < mat.column_count(); j++) {
            if (j != 0) {
               out << ", ";
            }
            out << mat.at(i, j);
        }
        out << "]";
    }
    return out << "]";
}
