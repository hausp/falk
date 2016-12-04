
#ifndef FALK_EV_MATRIX_HPP
#define FALK_EV_MATRIX_HPP

#include <deque>
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
            array row(size_t) const;
            array column(size_t) const;

            matrix& assign_row(size_t, const array&);
            matrix& assign_column(size_t, const array&);

            void push_back(const array&);
            void push_front(const array&);
            void set_error();
            bool error() const;
            std::pair<size_t, size_t> size() const;
            size_t row_count() const;
            size_t column_count() const;

            static matrix pow(const matrix&, const scalar&);
            static matrix pow(const matrix&, const array&);
            static matrix pow(const matrix&, const matrix&);
            matrix& pow(const scalar&);
            matrix& pow(const array&);
            matrix& pow(const matrix&);

            matrix& assign(const scalar&);
            matrix& assign(const array&);
            matrix& assign(const matrix&);

            matrix& operator+=(const scalar&);
            matrix& operator-=(const scalar&);
            matrix& operator*=(const scalar&);
            matrix& operator/=(const scalar&);
            matrix& operator%=(const scalar&);
            matrix& operator&=(const scalar&);
            matrix& operator|=(const scalar&);

            matrix& operator+=(const array&);
            matrix& operator-=(const array&);
            matrix& operator*=(const array&);
            matrix& operator/=(const array&);
            matrix& operator%=(const array&);
            matrix& operator&=(const array&);
            matrix& operator|=(const array&);

            matrix& operator+=(const matrix&);
            matrix& operator-=(const matrix&);
            matrix& operator*=(const matrix&);
            matrix& operator/=(const matrix&);
            matrix& operator%=(const matrix&);
            matrix& operator&=(const matrix&);
            matrix& operator|=(const matrix&);

         private:
            std::deque<scalar> values;
            static scalar invalid;
            size_t num_rows = 0;
            size_t num_columns = 0;
            bool fail = false;
        };

        const auto invalid_matrix = matrix(true);

        inline void matrix::set_error() {
            fail = true;
        }

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
            return lhs + rhs.to_matrix();
        }

        inline matrix operator-(const matrix& lhs, const array& rhs) {
            return lhs - rhs.to_matrix();
        }

        inline matrix operator*(const matrix& lhs, const array& rhs) {
            return lhs * rhs.to_matrix();
        }

        inline matrix operator/(const matrix& lhs, const array& rhs) {
            return lhs / rhs.to_matrix();
        }

        inline matrix operator%(const matrix& lhs, const array& rhs) {
            return lhs % rhs.to_matrix();
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

        inline scalar operator&&(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX,
                                                  falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator||(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX,
                                                  falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator<(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator>(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator<=(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator>=(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator==(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator!=(const matrix& lhs, const scalar& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::SCALAR);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator&&(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX,
                                                  falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator||(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX,
                                                  falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator<(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator>(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator<=(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator>=(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator==(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator!=(const matrix& lhs, const array& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::ARRAY);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator&&(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX,
                                                  falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator||(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::MATRIX,
                                                  falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator<(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator>(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator<=(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator>=(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator==(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        inline scalar operator!=(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::MATRIX,
                                                     falk::struct_t::MATRIX);
            scalar result;
            result.set_error();
            return result;
        }

        std::ostream& operator<<(std::ostream&, const matrix&);

        inline matrix::matrix(bool flag) : fail{flag} { }

        inline matrix::matrix(size_t rows, size_t columns):
          values(rows * columns), num_rows{rows}, num_columns{columns} { }

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

        inline matrix& matrix::pow(const scalar& rhs) {
            for (size_t i = 0; i < num_rows; i++) {
                for (size_t j = 0; j < num_columns; j++) {
                    at(i, j) = scalar::pow(at(i, j), rhs);
                }
            }
            return *this;
        }

        inline matrix& matrix::pow(const array&) {
            err::semantic<Error::ILLEGAL_OPERATION>("array exponentiation");
            fail = true;
            return *this;
        }

        inline matrix& matrix::pow(const matrix& rhs) {
            err::semantic<Error::ILLEGAL_OPERATION>("matrix exponentiation");
            fail = true;
            return *this;
        }

        inline matrix matrix::pow(const matrix& lhs, const scalar& rhs) {
            auto num_rows = lhs.row_count();
            auto num_columns = lhs.column_count();
            auto result = matrix(num_rows, num_columns);
            for (size_t i = 0; i < num_rows; i++) {
                for (size_t j = 0; j < num_columns; j++) {
                    result.at(i, j) = scalar::pow(lhs.at(i, j), rhs);
                }
            }
            return result;
        }

        inline matrix matrix::pow(const matrix&, const array&) {
            err::semantic<Error::ILLEGAL_OPERATION>("array exponentiation");
            return invalid_matrix;
        }

        inline matrix matrix::pow(const matrix& lhs, const matrix& rhs) {
            err::semantic<Error::ILLEGAL_OPERATION>("matrix exponentiation");
            return invalid_matrix;
        }
    }
}

#endif /* FALK_EV_MATRIX_HPP */
