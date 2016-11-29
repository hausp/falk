
#ifndef FALK_EV_ARRAY_HPP
#define FALK_EV_ARRAY_HPP

#include <ostream>
#include <vector>
#include "scalar.hpp"

namespace falk {
    namespace ev {
        class matrix;

        class array {
         public:
            array(bool flag = false) : fail(flag) { }

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

            bool error() const {
                return fail;
            }

            matrix to_matrix() const;

            array& pow(const array& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    return *this;
                }

                for (size_t i = 0; i < size(); i++) {
                    values[i].pow(rhs[i]);
                }

                return *this;
            }

            static array pow(const array& lhs, const array& rhs) {
                auto copy = lhs;
                return copy.pow(rhs);
            }

            array& operator+=(const array& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    fail = true;
                    return *this;
                }

                for (size_t i = 0; i < size(); i++) {
                    values[i] += rhs[i];
                }
                return *this;
            }

            array& operator-=(const array& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    fail = true;
                    return *this;
                }

                for (size_t i = 0; i < size(); i++) {
                    values[i] -= rhs[i];
                }
                return *this;
            }

            array& operator*=(const array& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    fail = true;
                    return *this;
                }

                for (size_t i = 0; i < size(); i++) {
                    values[i] *= rhs[i];
                }
                return *this;
            }

            array& operator/=(const array& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    fail = true;
                    return *this;
                }

                for (size_t i = 0; i < size(); i++) {
                    values[i] /= rhs[i];
                }
                return *this;
            }

            array& operator%=(const array& rhs) {
                if (size() != rhs.size()) {
                    // TODO: error (incompatible operands)
                    fail = true;
                    return *this;
                }

                for (size_t i = 0; i < size(); i++) {
                    values[i] %= rhs[i];                
                }
                return *this;
            }

         private:
            std::vector<scalar> values;
            bool fail = false;
        };

        inline array operator+(const array& lhs, const array& rhs) {
            auto copy = lhs;
            return copy += rhs;
        }

        inline array operator-(const array& lhs, const array& rhs) {
            auto copy = lhs;
            return copy -= rhs;
        }

        inline array operator*(const array& lhs, const array& rhs) {
            auto copy = lhs;
            return copy *= rhs;
        }

        inline array operator/(const array& lhs, const array& rhs) {
            auto copy = lhs;
            return copy /= rhs;
        }

        inline array operator%(const array& lhs, const array& rhs) {
            auto copy = lhs;
            return copy %= rhs;
        }

        inline array operator-(const array& rhs) {
            array result;
            for (size_t i = 0; i < rhs.size(); i++) {
                result.push_back(-rhs[i]);
            }
            return result;
        }

        inline array operator+(const array& lhs, const scalar& rhs) {
            return rhs + lhs;
        }

        inline array operator-(const array& lhs, const scalar& rhs) {
            return rhs - lhs;
        }

        inline array operator*(const array& lhs, const scalar& rhs) {
            return rhs * lhs;
        }

        inline array operator/(const array& lhs, const scalar& rhs) {
            return rhs / lhs;
        }

        inline array operator%(const array& lhs, const scalar& rhs) {
            return rhs % lhs;
        }

        matrix operator+(const array& lhs, const matrix& rhs);
        matrix operator-(const array& lhs, const matrix& rhs);
        matrix operator*(const array& lhs, const matrix& rhs);
        matrix operator/(const array& lhs, const matrix& rhs);
        matrix operator%(const array& lhs, const matrix& rhs);

        inline std::ostream& operator<<(std::ostream& out, const array& arr) {
            out << "[";
            for (size_t i = 0; i < arr.size(); i++) {
                if (i != 0) {
                   out << ", ";
                }
                out << arr[i];
            }
            return out << "]";
        }
    }
}

#endif /* FALK_EV_ARRAY_HPP */
