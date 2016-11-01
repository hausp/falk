
#ifndef FALK_INTERPRETER_COMPLEX_HPP
#define FALK_INTERPRETER_COMPLEX_HPP

namespace falk {
    struct complex_t {
        double real;
        double imag;
        
        complex_t operator+(const complex_t& c) const;

        complex_t operator-(const complex_t& c) const;

        complex_t operator-() const;

        complex_t operator*(const complex_t& c) const;

        complex_t operator/(const complex_t& c) const;

        complex_t operator/(double n) const;

        complex_t conjugate() const;

        double norm() const;
    };

    inline complex_t complex_t::operator+(const complex_t& c) const {
        return {real + c.real, imag + c.imag};
    }

    inline complex_t complex_t::operator-(const complex_t& c) const {
        return {real - c.real, imag - c.imag};
    }

    inline complex_t complex_t::operator-() const {
        return complex_t{0, 0} - *this;
    }

    inline complex_t complex_t::operator*(const complex_t& c) const {
        return {real * c.real - imag * c.imag, real * c.imag + imag * c.real};
    }

    inline complex_t complex_t::operator/(const complex_t& c) const {
        return (*this * c.conjugate()) / c.norm();
    }

    inline complex_t complex_t::operator/(double n) const {
        return {real/n, imag/n};
    }

    inline complex_t complex_t::conjugate() const {
        return {real, -imag};
    }

    inline double complex_t::norm() const {
        return real * real + imag * imag;
    }
}

#endif /* FALK_INTERPRETER_COMPLEX_HPP */
