
#ifndef FALK_EV_MATRIX_HPP
#define FALK_EV_MATRIX_HPP

#include <vector>
#include "scalar.hpp"

// Assigned to: Merlseson
namespace falk {
    namespace ev {
        class matrix;
        matrix operator*(const matrix& lhs, const matrix& rhs);

        class matrix {
         public:
            // TODO: grammar-friendly constructor
            matrix() = default;

            matrix(size_t rows, size_t columns):
              num_rows{rows}, num_columns{columns} { }

            scalar& at(size_t row, size_t column) {
                if (row >= num_rows || column >= num_columns) {
                    // TODO: error (index out of bounds)
                    // TODO: return what?
                    return values[0];
                }
                return values.at(row * num_rows + column);
            }

            const scalar& at(size_t row, size_t column) const {
                if (row >= num_rows || column >= num_columns) {
                    // TODO: error (index out of bounds)
                    // TODO: return what?
                    return values.at(0);
                }
                return values.at(row * num_rows + column);
            }

            std::pair<size_t, size_t> size() const {
                return {num_rows, num_columns};
            }

            size_t row_count() const {
                return num_rows;
            }

            size_t column_count() const {
                return num_columns;
            }

            // scalar& operator[](size_t index) {
            //     return values[index];
            // }

            // const scalar& operator[](size_t index) const {
            //     return values.at(index);
            // }

            // void push_back(const scalar& value) {
            //     values.push_back(value);
            // }

            matrix& pow(const matrix& rhs) {
                // TODO: error (operation not allowed)
                return *this;
            }

            static matrix pow(const matrix& lhs, const matrix& rhs) {
                // TODO: error (operation not allowed)
                // TODO: return what?
                return matrix{};
            }

            matrix& operator+=(const matrix& rhs) {
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

            matrix& operator-=(const matrix& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                for (size_t i = 0; i < row_count(); i++) {
                    for (size_t j = 0; j < column_count(); j++) {
                        at(i, j) -= rhs.at(i, j);
                    }
                }
                return *this;
            }

            matrix& operator*=(const matrix& rhs) {
                if (num_rows != rhs.row_count() || num_rows != rhs.column_count()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }
                return *this = *this * rhs;
            }

            matrix& operator/=(const matrix& rhs) {
                // TODO: error (operation not allowed)
                return *this;
            }

            matrix& operator%=(const matrix& rhs) {
                // TODO: error (operation not allowed)
                return *this;
            }

         private:
            std::vector<scalar> values;
            size_t num_rows;
            size_t num_columns;
        };


        inline matrix operator+(const matrix& lhs, const matrix& rhs) {
            auto copy = lhs;
            return copy += rhs;
        }

        inline matrix operator-(const matrix& lhs, const matrix& rhs) {
            auto copy = lhs;
            return copy -= rhs;
        }

        inline matrix operator*(const matrix& lhs, const matrix& rhs) {
            if (lhs.column_count() != rhs.row_count()) {
                // TODO: error (incompatible operands)
                // TODO: return what?
                return matrix{};
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

        inline matrix operator/(const matrix& lhs, const matrix& rhs) {
            // TODO: error (incompatible operands)
            // TODO: return what?
            return matrix{};
        }

        inline matrix operator%(const matrix& lhs, const matrix& rhs) {
            // TODO: error (incompatible operands)
            // TODO: return what?
            return matrix{};
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
    }
}

#endif /* FALK_EV_MATRIX_HPP */
