
#ifndef FALK_EVALUATOR_RVALUE
#define FALK_EVALUATOR_RVALUE

#include <complex>
#include <vector>

#include "base/types.hpp"

namespace falk {
    namespace ev {
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
            
            falk::fundamental::type type() const;

            // Function for unique purpose of compatibility 
            // with parser generic structure.
            operator long() const;

            static scalar pow(const scalar&, const scalar&);

            scalar& pow(const scalar&) {
                // TODO: implement this
                return *this;
            }

            scalar& operator+=(const scalar&) {
                // TODO: implement this
                return *this;
            }

            scalar& operator-=(const scalar&) {
                // TODO: implement this
                return *this;
            }

            scalar& operator*=(const scalar&) {
                // TODO: implement this
                return *this;
            }

            scalar& operator/=(const scalar&) {
                // TODO: implement this
                return *this;
            }

            scalar& operator%=(const scalar&) {
                // TODO: implement this
                return *this;
            }

         private:
            falk::fundamental::type _type;
            double _real = 0;
            double _imag = 0;
        };

        // Non-member functions
        scalar operator+(const scalar&, const scalar&);
        scalar operator-(const scalar&, const scalar&);
        scalar operator*(const scalar&, const scalar&);
        scalar operator/(const scalar&, const scalar&);
        scalar operator%(const scalar&, const scalar&);
        scalar operator-(const scalar&);

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
            return static_cast<bool>(_real);
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

        inline scalar::operator long() const {
            return static_cast<long>(_real);
        }
    }
}

#endif /* FALK_EVALUATOR_RVALUE */
