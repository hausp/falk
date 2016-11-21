
#ifndef FALK_EV_MATRIX_HPP
#define FALK_EV_MATRIX_HPP

namespace falk {
    namespace ev {
        struct matrix {
            matrix pow(const matrix&);
            matrix& pow_assign(const matrix&);

            matrix& operator+=(const matrix&);
            matrix& operator-=(const matrix&);
            matrix& operator*=(const matrix&);
            matrix& operator/=(const matrix&);
            matrix& operator%=(const matrix&);
        };

        matrix operator+(const matrix&, const matrix&);
        matrix operator-(const matrix&, const matrix&);
        matrix operator*(const matrix&, const matrix&);
        matrix operator/(const matrix&, const matrix&);
        matrix operator%(const matrix&, const matrix&);
        matrix operator-(const matrix&);

    }
}

#endif /* FALK_EV_MATRIX_HPP */
