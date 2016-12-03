#include "ev/matrix.hpp"

falk::ev::scalar falk::ev::matrix::invalid;

falk::ev::matrix falk::ev::operator*(const matrix& lhs, const matrix& rhs) {
    if (lhs.column_count() != rhs.row_count()) {
        err::semantic<Error::MATRIX_MULT_MISMATCH>(lhs.column_count(), rhs.row_count());
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

falk::ev::scalar& falk::ev::matrix::at(size_t row, size_t column) {
    if (row >= num_rows) {
        err::semantic<Error::INDEX_OUT_OF_BOUNDS>(num_rows, row);
        fail = true;
        return invalid;
    }

    if (column >= num_columns) {
        err::semantic<Error::INDEX_OUT_OF_BOUNDS>(num_columns, column);
        fail = true;
        return invalid;
    }
    return values.at(row * num_columns + column);
}

const falk::ev::scalar& falk::ev::matrix::at(size_t row, size_t column) const {
    if (row >= num_rows) {
        err::semantic<Error::INDEX_OUT_OF_BOUNDS>(num_rows, row);
        return invalid;
    }

    if (column >= num_columns) {
        err::semantic<Error::INDEX_OUT_OF_BOUNDS>(num_columns, column);
        return invalid;
    }
    return values.at(row * num_columns + column);
}

void falk::ev::matrix::push_back(const array& row) {
    if (values.size() == 0) {
        num_columns = row.size();
    }

    if (row.size() != num_columns) {
        err::semantic<Error::WRONG_COLUMN_COUNT>(num_columns, row.size());
        fail = true;
        return;
    }

    for (size_t i = 0; i < num_columns; i++) {
        values.push_back(row[i]);
    }
    ++num_rows;
}

falk::ev::matrix& falk::ev::matrix::assign(const scalar& rhs) {
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            at(i, j) = rhs;
        }
    }
    return *this;
}


falk::ev::matrix& falk::ev::matrix::assign(const array& rhs) {
    auto value = rhs.to_matrix();
    if (row_count() != value.row_count()) {
        err::semantic<Error::ROW_SIZE_MISMATCH>(row_count(),
                                                value.row_count());
        fail = true;
        return *this;
    }

    if (column_count() != value.column_count()) {
        err::semantic<Error::COLUMN_SIZE_MISMATCH>(column_count(),
                                                   value.column_count());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < row_count(); i++) {
        for (size_t j = 0; j < column_count(); j++) {
            at(i, j) = value.at(i, j);
        }
    }
    return *this;
}

falk::ev::matrix& falk::ev::matrix::assign(const matrix& rhs) {
    if (row_count() != rhs.row_count()) {
        err::semantic<Error::ROW_SIZE_MISMATCH>(row_count(),
                                                rhs.row_count());
        fail = true;
        return *this;
    }

    if (column_count() != rhs.column_count()) {
        err::semantic<Error::COLUMN_SIZE_MISMATCH>(column_count(),
                                                   rhs.column_count());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < row_count(); i++) {
        for (size_t j = 0; j < column_count(); j++) {
            at(i, j) = rhs.at(i, j);
        }
    }
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator+=(const scalar& rhs) {
    return *this = *this + rhs;
}

falk::ev::matrix& falk::ev::matrix::operator-=(const scalar& rhs) {
    return *this = *this - rhs;
}

falk::ev::matrix& falk::ev::matrix::operator*=(const scalar& rhs) {
    return *this = *this * rhs;
}

falk::ev::matrix& falk::ev::matrix::operator/=(const scalar& rhs) {
    return *this = *this / rhs;
}

falk::ev::matrix& falk::ev::matrix::operator%=(const scalar& rhs) {
    return *this = *this % rhs;
}

falk::ev::matrix& falk::ev::matrix::operator&=(const scalar& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::SCALAR);
    fail = true;
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator|=(const scalar& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::SCALAR);
    fail = true;
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator+=(const array& rhs) {
    return *this = *this + rhs;
}

falk::ev::matrix& falk::ev::matrix::operator-=(const array& rhs) {
    return *this = *this - rhs;
}

falk::ev::matrix& falk::ev::matrix::operator*=(const array& rhs) {
    return *this = *this * rhs;
}

falk::ev::matrix& falk::ev::matrix::operator/=(const array& rhs) {
    return *this = *this / rhs;
}

falk::ev::matrix& falk::ev::matrix::operator%=(const array& rhs) {
    return *this = *this % rhs;
}

falk::ev::matrix& falk::ev::matrix::operator&=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator|=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator+=(const matrix& rhs) {
    if (row_count() != rhs.row_count()) {
        err::semantic<Error::ROW_SIZE_MISMATCH>(row_count(),
                                                rhs.row_count());
        fail = true;
        return *this;
    }

    if (column_count() != rhs.column_count()) {
        err::semantic<Error::COLUMN_SIZE_MISMATCH>(column_count(),
                                                   rhs.column_count());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < row_count(); i++) {
        for (size_t j = 0; j < column_count(); j++) {
            at(i, j) += rhs.at(i, j);
        }
    }
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator-=(const matrix& rhs) {
    if (row_count() != rhs.row_count()) {
        err::semantic<Error::ROW_SIZE_MISMATCH>(row_count(),
                                                rhs.row_count());
        fail = true;
        return *this;
    }

    if (column_count() != rhs.column_count()) {
        err::semantic<Error::COLUMN_SIZE_MISMATCH>(column_count(),
                                                   rhs.column_count());
        fail = true;
        return *this;
    }

    for (size_t i = 0; i < row_count(); i++) {
        for (size_t j = 0; j < column_count(); j++) {
            at(i, j) -= rhs.at(i, j);
        }
    }
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator*=(const matrix& rhs) {
    if (num_columns != rhs.row_count()) {
        err::semantic<Error::MATRIX_MULT_MISMATCH>(num_columns, rhs.row_count());
        fail = true;
        return *this;
    }

    if (num_columns != rhs.column_count()) {
        err::semantic<Error::NON_SQUARE_MATRIX>(num_columns, rhs.column_count());
        fail = true;
        return *this;
    }
    return *this = *this * rhs;
}

falk::ev::matrix& falk::ev::matrix::operator/=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("matrix division");
    fail = true;
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator%=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("matrix modulus");
    fail = true;
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator&=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::ev::matrix& falk::ev::matrix::operator|=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}
