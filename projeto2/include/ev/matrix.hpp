
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

            static matrix pow(const matrix&, const scalar&);
            static matrix pow(const matrix&, const array&);
            static matrix pow(const matrix&, const matrix&);
            matrix& pow(const scalar&);
            matrix& pow(const array&);
            matrix& pow(const matrix&);

            matrix& operator+=(const scalar&);
            matrix& operator-=(const scalar&);
            matrix& operator*=(const scalar&);
            matrix& operator/=(const scalar&);
            matrix& operator%=(const scalar&);

            matrix& operator+=(const array&);
            matrix& operator-=(const array&);
            matrix& operator*=(const array&);
            matrix& operator/=(const array&);
            matrix& operator%=(const array&);

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

        inline matrix& matrix::pow(const scalar&) {
            // TODO
            fail = true;
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

        inline matrix matrix::pow(const matrix&, const scalar&) {
            // TODO
            return invalid_matrix;
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
