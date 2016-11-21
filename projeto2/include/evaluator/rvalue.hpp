
#ifndef FALK_EVALUATOR_RVALUE
#define FALK_EVALUATOR_RVALUE

#include <complex>
#include "base/types.hpp"

namespace falk {
    namespace ev {
        // Class to capture all kinds of rvalue possible in
        // interpreted mode.
        class rvalue {
         public:
            rvalue(double);
            rvalue(std::complex<double>);
            rvalue(falk::type = falk::type::UNDEFINED, double = 0, double = 0);
            rvalue(bool);

            bool boolean() const;
            std::complex<double> complex() const;
            
            double imag() const;
            double real() const;
            falk::type type() const;

            operator std::complex<double>() const;
            operator long() const;

            rvalue pow(const rvalue&);
         private:
            falk::type _type;
            double _real;
            double _imag = 0;
        };

        // Non-member functions
        rvalue operator+(const rvalue&, const rvalue&);
        rvalue operator-(const rvalue&, const rvalue&);
        rvalue operator*(const rvalue&, const rvalue&);
        rvalue operator/(const rvalue&, const rvalue&);
        rvalue operator%(const rvalue&, const rvalue&);
        rvalue operator-(const rvalue&);

        std::ostream& operator<<(std::ostream&, const rvalue&);

        // inline implementations

        inline rvalue::rvalue(double v):
          _type{falk::type::REAL}, _real{v} { }
        
        inline rvalue::rvalue(std::complex<double> v):
          _type{falk::type::COMPLEX}, _real{v.real()}, _imag{v.imag()} { }
        
        inline rvalue::rvalue(falk::type type, double real, double imag):
          _type{type}, _real{real}, _imag{imag} { }
        
        inline rvalue::rvalue(bool v):
          _type{falk::type::BOOL}, _real{static_cast<double>(v)} { }

        inline std::complex<double> rvalue::complex() const {
            return {_real, _imag};
        }

        inline bool rvalue::boolean() const {
            return static_cast<bool>(_real);
        }

        inline double rvalue::imag() const {
            return _imag;
        }

        inline double rvalue::real() const {
            return _real;
        }

        inline falk::type rvalue::type() const {
            return _type;
        }
        
        inline rvalue::operator std::complex<double>() const {
            return {_real, _imag};
        }

        inline rvalue::operator long() const {
            return static_cast<long>(_real);
        }

    }
}

#endif /* FALK_EVALUATOR_RVALUE */
