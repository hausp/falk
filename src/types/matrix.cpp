#include "types/matrix.hpp"

falk::scalar falk::matrix::invalid;

falk::array falk::matrix::row(size_t index) const {
    array result;
    if (index >= num_rows) {
        err::semantic<Error::INDEX_OUT_OF_BOUNDS>(num_rows, index);
        result.set_error();
        return result;
    }

    for (size_t i = 0; i < num_columns; i++) {
        result.push_back(at(index, i));
    }
    return result;
}

falk::array falk::matrix::column(size_t index) const {
    array result;
    if (index >= num_columns) {
        err::semantic<Error::INDEX_OUT_OF_BOUNDS>(num_columns, index);
        result.set_error();
        return result;
    }

    for (size_t i = 0; i < num_rows; i++) {
        result.push_back(at(i, index));
    }
    return result;
}

falk::matrix& falk::matrix::assign_row(size_t index, const array& data) {
    for (size_t i = 0; i < num_columns; i++) {
        at(index, i) = data[i];
    }
    return *this;
}

falk::matrix& falk::matrix::assign_column(size_t index, const array& data) {
    for (size_t i = 0; i < num_columns; i++) {
        at(i, index) = data[i];
    }
    return *this;
}

falk::matrix falk::operator*(const matrix& lhs, const matrix& rhs) {
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

std::ostream& falk::operator<<(std::ostream& out, const falk::matrix& mat) {
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

falk::scalar& falk::matrix::at(size_t row, size_t column) {
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

const falk::scalar& falk::matrix::at(size_t row, size_t column) const {
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

void falk::matrix::push_back(const array& new_row) {
    auto row = prepare(new_row);
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

void falk::matrix::push_front(const array& new_row) {
    auto row = prepare(new_row);
    if (values.size() == 0) {
        num_columns = row.size();
    }

    if (row.size() != num_columns) {
        err::semantic<Error::WRONG_COLUMN_COUNT>(num_columns, row.size());
        fail = true;
        return;
    }

    for (size_t i = 0; i < num_columns; i++) {
        values.push_front(row[num_columns - i - 1]);
    }
    ++num_rows;
}

falk::matrix& falk::matrix::assign(const scalar& rhs) {
    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_columns; j++) {
            at(i, j).assign(rhs);
        }
    }
    return *this;
}


falk::matrix& falk::matrix::assign(const array& rhs) {
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

falk::matrix& falk::matrix::assign(const matrix& rhs) {
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

falk::matrix& falk::matrix::operator+=(const scalar& rhs) {
    return *this = *this + rhs;
}

falk::matrix& falk::matrix::operator-=(const scalar& rhs) {
    return *this = *this - rhs;
}

falk::matrix& falk::matrix::operator*=(const scalar& rhs) {
    return *this = *this * rhs;
}

falk::matrix& falk::matrix::operator/=(const scalar& rhs) {
    return *this = *this / rhs;
}

falk::matrix& falk::matrix::operator%=(const scalar& rhs) {
    return *this = *this % rhs;
}

falk::matrix& falk::matrix::operator&=(const scalar& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::SCALAR);
    fail = true;
    return *this;
}

falk::matrix& falk::matrix::operator|=(const scalar& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::SCALAR);
    fail = true;
    return *this;
}

falk::matrix& falk::matrix::operator+=(const array& rhs) {
    return *this = *this + rhs;
}

falk::matrix& falk::matrix::operator-=(const array& rhs) {
    return *this = *this - rhs;
}

falk::matrix& falk::matrix::operator*=(const array& rhs) {
    return *this = *this * rhs;
}

falk::matrix& falk::matrix::operator/=(const array& rhs) {
    return *this = *this / rhs;
}

falk::matrix& falk::matrix::operator%=(const array& rhs) {
    return *this = *this % rhs;
}

falk::matrix& falk::matrix::operator&=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::matrix& falk::matrix::operator|=(const array& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::ARRAY);
    fail = true;
    return *this;
}

falk::matrix& falk::matrix::operator+=(const matrix& rhs) {
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

falk::matrix& falk::matrix::operator-=(const matrix& rhs) {
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

falk::matrix& falk::matrix::operator*=(const matrix& rhs) {
    if (num_columns != rhs.row_count()) {
        err::semantic<Error::MATRIX_MULT_MISMATCH>(num_columns, rhs.row_count());
        fail = true;
        return *this;
    }

    if (num_columns != rhs.column_count()) {
        err::semantic<Error::NON_SQUARE_MATRIX>(rhs.row_count(), rhs.column_count());
        fail = true;
        return *this;
    }
    return *this = *this * rhs;
}

falk::matrix& falk::matrix::operator/=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("matrix division");
    fail = true;
    return *this;
}

falk::matrix& falk::matrix::operator%=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_OPERATION>("matrix modulus");
    fail = true;
    return *this;
}

falk::matrix& falk::matrix::operator&=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::matrix& falk::matrix::operator|=(const matrix& rhs) {
    err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX, falk::struct_t::MATRIX);
    fail = true;
    return *this;
}

falk::array falk::matrix::prepare(const array& row) {
    auto arr_type = row.inner_type();
    auto arr_priority = falk::priority.at(arr_type);
    auto curr_priority = falk::priority.at(value_type);
    if (arr_priority < curr_priority) {
        auto copy = row;
        copy.coerce_to(value_type);
        return copy;
    } else if (arr_priority > curr_priority) {
        value_type = arr_type;
        for (size_t i = 0; i < num_rows; i++) {
            for (size_t j = 0; j < num_columns; j++) {
                auto& value = at(i, j);
                at(i, j) = scalar(arr_type, value.real(), value.imag());
            }
        }
    }
    return row;
}
