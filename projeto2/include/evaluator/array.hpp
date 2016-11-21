
#ifndef FALK_EV_ARRAY_HPP
#define FALK_EV_ARRAY_HPP

namespace falk {
    namespace ev {
        struct array {
            array pow(const array&);
            array& pow_assign(const array&);

            array& operator+=(const array&);
            array& operator-=(const array&);
            array& operator*=(const array&);
            array& operator/=(const array&);
            array& operator%=(const array&);
        };

        array operator+(const array&, const array&);
        array operator-(const array&, const array&);
        array operator*(const array&, const array&);
        array operator/(const array&, const array&);
        array operator%(const array&, const array&);
        array operator-(const array&);

    }
}

#endif /* FALK_EV_ARRAY_HPP */
