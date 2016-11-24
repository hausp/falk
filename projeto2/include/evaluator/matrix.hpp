
#ifndef FALK_EV_MATRIX_HPP
#define FALK_EV_MATRIX_HPP

#include <vector>
#include "scalar.hpp"

// Assigned to: Merlseson
namespace falk {
    namespace ev {
        class matrix {
         public:
            // matrix()

            size_t size() const {
                return values.size();
            }

            scalar& operator[](size_t index) {
                return values[index];
            }

            void push_back(const scalar& value) {
                values.push_back(value);
            }

            const scalar& operator[](size_t index) const {
                return values.at(index);
            }

            matrix& pow(const matrix& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                for (size_t i = 0; i < size(); i++) {
                    values[i].pow(rhs[i]);
                }

                return *this;
            }

            static matrix pow(const matrix& lhs, const matrix& rhs) {
                auto copy = lhs;
                return copy.pow(rhs);
            }

            matrix& operator+=(const matrix& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                matrix result;
                for (size_t i = 0; i < size(); i++) {
                    result.push_back(values[i] + rhs[i]);
                }
                return *this;
            }

            matrix& operator-=(const matrix& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                matrix result;
                for (size_t i = 0; i < size(); i++) {
                    result.push_back(values[i] - rhs[i]);
                }
                return *this;
            }

            matrix& operator*=(const matrix& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                matrix result;
                for (size_t i = 0; i < size(); i++) {
                    result.push_back(values[i] * rhs[i]);
                }
                return *this;
            }

            matrix& operator/=(const matrix& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                matrix result;
                for (size_t i = 0; i < size(); i++) {
                    result.push_back(values[i] / rhs[i]);
                }
                return *this;
            }

            matrix& operator%=(const matrix& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                matrix result;
                for (size_t i = 0; i < size(); i++) {
                    result.push_back(values[i] % rhs[i]);                
                }
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
            auto copy = lhs;
            return copy *= rhs;
        }

        inline matrix operator/(const matrix& lhs, const matrix& rhs) {
            auto copy = lhs;
            return copy /= rhs;
        }

        inline matrix operator%(const matrix& lhs, const matrix& rhs) {
            auto copy = lhs;
            return copy %= rhs;
        }

        inline matrix operator-(const matrix& rhs) {
            matrix result;
            for (size_t i = 0; i < rhs.size(); i++) {
                result.push_back(-rhs[i]);
            }
            return result;
        }
    }
}

#endif /* FALK_EV_MATRIX_HPP */
