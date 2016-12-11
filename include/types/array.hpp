
#ifndef FALK_EV_ARRAY_HPP
#define FALK_EV_ARRAY_HPP

#include <ostream>
#include <deque>
#include "base/errors.hpp"
#include "scalar.hpp"

namespace falk {
    class matrix;

    class array {
     public:
        explicit array(bool flag = false) : fail(flag) { }
        array(const scalar& size, falk::type type)
        : values(size.real(), 0), value_type{type} { }

        auto begin() const {
            return values.cbegin();
        }

        auto begin() {
            return values.begin();
        }

        auto end() const {
            return values.cend();
        }

        auto end() {
            return values.end();
        }

        size_t size() const {
            return values.size();
        }

        scalar& operator[](size_t index) {
            return values[index];
        }

        const scalar& operator[](size_t index) const {
            return values.at(index);
        }

        void push_front(const scalar& value) {
            values.push_front(prepare(value));
        }

        void push_back(const scalar& value) {
            values.push_back(prepare(value));
        }

        void coerce_to(falk::type);

        falk::type inner_type() const {
            return value_type;
        }

        void inner_type(falk::type type) {
            value_type = type;
        }

        void set_error() {
            fail = true;
        }

        bool error() const {
            return fail;
        }

        bool printable() const {
            return print;
        }

        static array silent() {
            array arr;
            arr.print = false;
            return arr;
        }

        matrix to_matrix() const;

        constexpr structural::type type() const {
            return structural::type::ARRAY;
        }

        array& pow(const scalar& rhs);
        array& pow(const array& rhs);
        array& pow(const matrix& rhs);

        static array pow(const array& lhs, const scalar& rhs) {
            auto copy = lhs;
            return copy.pow(rhs);
        }

        static array pow(const array& lhs, const array& rhs) {
            auto copy = lhs;
            return copy.pow(rhs);
        }

        static array pow(const array& lhs, const matrix& rhs) {
            auto copy = lhs;
            return copy.pow(rhs);
        }

        array& assign(const scalar& rhs);
        array& assign(const array& rhs);
        array& assign(const matrix& rhs);

        array& operator+=(const scalar&);
        array& operator-=(const scalar&);
        array& operator*=(const scalar&);
        array& operator/=(const scalar&);
        array& operator%=(const scalar&);
        array& operator&=(const scalar&);
        array& operator|=(const scalar&);

        array& operator+=(const array&);
        array& operator-=(const array&);
        array& operator*=(const array&);
        array& operator/=(const array&);
        array& operator%=(const array&);
        array& operator&=(const array&);
        array& operator|=(const array&);

        array& operator+=(const matrix&);
        array& operator-=(const matrix&);
        array& operator*=(const matrix&);
        array& operator/=(const matrix&);
        array& operator%=(const matrix&);
        array& operator&=(const matrix&);
        array& operator|=(const matrix&);

     private:
        std::deque<scalar> values;
        bool fail = false;
        bool print = true;
        falk::type value_type = falk::type::BOOL;

        scalar prepare(const scalar&);
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

    inline array operator!(const array& rhs) {
        array result;
        for (size_t i = 0; i < rhs.size(); i++) {
            result.push_back(!rhs[i]);
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

    inline scalar operator&&(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY,
                                              falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator||(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY,
                                              falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator<(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator>(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator<=(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator>=(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator==(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator!=(const array& lhs, const scalar& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::SCALAR);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator&&(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY,
                                              falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator||(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY,
                                              falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator<(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator>(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator<=(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator>=(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator==(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator!=(const array& lhs, const array& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::ARRAY);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator&&(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY,
                                              falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator||(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_BOOL_OP>(falk::struct_t::ARRAY,
                                              falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator<(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator>(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator<=(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator>=(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator==(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

    inline scalar operator!=(const array& lhs, const matrix& rhs) {
        err::semantic<Error::ILLEGAL_COMPARISON>(falk::struct_t::ARRAY,
                                                 falk::struct_t::MATRIX);
        scalar result;
        result.set_error();
        return result;
    }

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

#endif /* FALK_EV_ARRAY_HPP */
