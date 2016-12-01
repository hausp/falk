
#ifndef FALK_EVALUATOR_RVALUE
#define FALK_EVALUATOR_RVALUE

#include <complex>
#include <vector>
#include "base/types.hpp"

namespace falk {
    namespace ev {
        class array;
        class matrix;

        // Class to capture all kinds of scalar possible.
        class scalar {
         public:
            scalar(double);
            scalar(int);
            scalar(std::complex<double>);
            scalar(falk::type = falk::type::UNDEFINED, double = 0, double = 0);
            scalar(bool);

            bool boolean() const;
            std::complex<double> complex() const;
            double imag() const;
            double real() const;
            
            bool error() const;

            falk::fundamental::type type() const;

            array to_array(size_t) const;

            static scalar pow(const scalar&, const scalar&);
            // static scalar pow(const scalar&, const array&);
            // static scalar pow(const scalar&, const matrix&);
            scalar& pow(const scalar&);
            // scalar& pow(const array&);
            // scalar& pow(const matrix&);

            scalar& operator+=(const scalar&);
            scalar& operator-=(const scalar&);
            scalar& operator*=(const scalar&);
            scalar& operator/=(const scalar&);
            scalar& operator%=(const scalar&);

         private:
            falk::fundamental::type _type;
            double _real = 0;
            double _imag = 0;
            bool fail = false;
        };

        // Non-member functions
        scalar operator+(const scalar&, const scalar&);
        scalar operator-(const scalar&, const scalar&);
        scalar operator*(const scalar&, const scalar&);
        scalar operator/(const scalar&, const scalar&);
        scalar operator%(const scalar&, const scalar&);
        scalar operator-(const scalar&);

        array operator+(const scalar&, const array&);
        array operator-(const scalar&, const array&);
        array operator*(const scalar&, const array&);
        array operator/(const scalar&, const array&);
        array operator%(const scalar&, const array&);

        matrix operator+(const scalar&, const matrix&);
        matrix operator-(const scalar&, const matrix&);
        matrix operator*(const scalar&, const matrix&);
        matrix operator/(const scalar&, const matrix&);
        matrix operator%(const scalar&, const matrix&);

        std::ostream& operator<<(std::ostream&, const scalar&);

        // inline implementations

        // class scalar methods
        inline scalar::scalar(double v):
          _type{falk::type::REAL}, _real{v} { }

        inline scalar::scalar(int v):
          _type{falk::type::REAL}, _real{static_cast<double>(v)} { }
        
        inline scalar::scalar(std::complex<double> v):
          _type{falk::type::COMPLEX}, _real{v.real()}, _imag{v.imag()} { }
        
        inline scalar::scalar(falk::type type, double real, double imag):
          _type{type}, _real{real}, _imag{imag} { }
        
        inline scalar::scalar(bool v):
          _type{falk::type::BOOL}, _real{static_cast<double>(v)} { }

        inline std::complex<double> scalar::complex() const {
            return {_real, _imag};
        }

        inline bool scalar::boolean() const {
            return _real != 0;
        }

        inline double scalar::imag() const {
            return _imag;
        }

        inline double scalar::real() const {
            return _real;
        }

        inline falk::type scalar::type() const {
            return _type;
        }

        inline bool scalar::error() const {
            return fail;
        }
    }
}

#endif /* FALK_EVALUATOR_RVALUE */
