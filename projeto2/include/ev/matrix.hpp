
#ifndef FALK_EV_MATRIX_HPP
#define FALK_EV_MATRIX_HPP

#include <vector>
#include "array.hpp"
#include "base/errors.hpp"
#include "scalar.hpp"

namespace falk {
    namespace ev {
        class matrix {
         public:
            explicit matrix(bool = false);
            matrix(size_t, size_t);

            scalar& at(size_t, size_t);
            const scalar& at(size_t, size_t) const;
            void push_back(const array&);
            bool error() const;
            std::pair<size_t, size_t> size() const;
            size_t row_count() const;
            size_t column_count() const;

            static matrix pow(const matrix&, const matrix&);
            matrix& pow(const matrix&);
            matrix& operator+=(const matrix&);
            matrix& operator-=(const matrix&);
            matrix& operator*=(const matrix&);
            matrix& operator/=(const matrix&);
            matrix& operator%=(const matrix&);

         private:
            std::vector<scalar> values;
            static scalar invalid;
            size_t num_rows = 0;
            size_t num_columns = 0;
            bool fail = false;
        };

        const auto invalid_matrix = matrix(true);

        inline matrix operator+(const matrix& lhs, const matrix& rhs) {
            auto copy = lhs;
            return copy += rhs;
        }

        inline matrix operator-(const matrix& lhs, const matrix& rhs) {
            auto copy = lhs;
            return copy -= rhs;
        }

        matrix operator*(const matrix& lhs, const matrix& rhs);

        inline matrix operator/(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_OPERATION>("matrix division");
            return invalid_matrix;
        }

        inline matrix operator%(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_OPERATION>("matrix modulus");
            return invalid_matrix;
        }

        inline matrix operator+(const matrix& lhs, const scalar& rhs) {
            return rhs + lhs;
        }

        inline matrix operator-(const matrix& lhs, const scalar& rhs) {
            return rhs - lhs;
        }

        inline matrix operator*(const matrix& lhs, const scalar& rhs) {
            return rhs * lhs;
        }

        inline matrix operator/(const matrix& lhs, const scalar& rhs) {
            return rhs / lhs;
        }

        inline matrix operator%(const matrix& lhs, const scalar& rhs) {
            return rhs % lhs;
        }

        inline matrix operator+(const matrix& lhs, const array& rhs) {
            return rhs + lhs;
        }

        inline matrix operator-(const matrix& lhs, const array& rhs) {
            return rhs - lhs;
        }

        inline matrix operator*(const matrix& lhs, const array& rhs) {
            return rhs * lhs;
        }

        inline matrix operator/(const matrix& lhs, const array& rhs) {
            return rhs / lhs;
        }

        inline matrix operator%(const matrix& lhs, const array& rhs) {
            return rhs % lhs;
        }

        inline matrix operator-(const matrix& rhs) {
            auto result = matrix(rhs.row_count(), rhs.column_count());
            for (size_t i = 0; i < result.row_count(); i++) {
                for (size_t j = 0; j < result.column_count(); j++) {
                    result.at(i, j) = -rhs.at(i, j);
                }
            }
            return result;
        }

        std::ostream& operator<<(std::ostream&, const matrix&);

        inline matrix::matrix(bool flag) : fail{flag} { }

        inline matrix::matrix(size_t rows, size_t columns):
          values(rows * columns), num_rows{rows}, num_columns{columns} { }

        inline scalar& matrix::at(size_t row, size_t column) {
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

        inline const scalar& matrix::at(size_t row, size_t column) const {
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

        inline void matrix::push_back(const array& row) {
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

        inline bool matrix::error() const {
            return fail;
        }

        inline std::pair<size_t, size_t> matrix::size() const {
            return {num_rows, num_columns};
        }

        inline size_t matrix::row_count() const {
            return num_rows;
        }

        inline size_t matrix::column_count() const {
            return num_columns;
        }

        inline matrix& matrix::pow(const matrix& rhs) {
            // TODO: error (operation not allowed)
            return *this;
        }

        inline matrix matrix::pow(const matrix& lhs, const matrix& rhs) {
            // TODO: error (operation not allowed)
            return invalid_matrix;
        }

        inline matrix& matrix::operator+=(const matrix& rhs) {
            if (size() != rhs.size()) {
                // TODO: error (incompatible operands)
                return *this;
            }

            for (size_t i = 0; i < row_count(); i++) {
                for (size_t j = 0; j < column_count(); j++) {
                    at(i, j) += rhs.at(i, j);
                }
            }
            return *this;
        }

        inline matrix& matrix::operator-=(const matrix& rhs) {
            if (size() != rhs.size()) {
                // TODO: error (incompatible operands)
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

        inline matrix& matrix::operator*=(const matrix& rhs) {
            if (num_rows != rhs.row_count() || num_rows != rhs.column_count()) {
                // TODO: error (incompatible operands)
                fail = true;
                return *this;
            }
            return *this = *this * rhs;
        }

        inline matrix& matrix::operator/=(const matrix& rhs) {
            // TODO: error (operation not allowed)
            fail = true;
            return *this;
        }

        inline matrix& matrix::operator%=(const matrix& rhs) {
            // TODO: error (operation not allowed)
            fail = true;
            return *this;
        }
    }
}

#endif /* FALK_EV_MATRIX_HPP */
