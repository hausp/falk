
#ifndef FALK_EVALUATOR_RVALUE
#define FALK_EVALUATOR_RVALUE

#include <complex>
#include <vector>
#include "base/types.hpp"

namespace falk {
    namespace ev {
        // Class to capture all kinds of rvalue possible in
        // interpreted mode.
        class rvalue {
            struct value {
                double real = 0;
                double imag = 0;

                operator bool() const;
                operator double() const;
                operator std::complex<double>() const;
            };
         public:
            rvalue(double);
            rvalue(std::complex<double>);
            rvalue(falk::type = falk::type::UNDEFINED, double = 0, double = 0);
            rvalue(bool);

            bool boolean(double = 0) const;
            std::complex<double> complex(double = 0) const;
            
            double imag(double = 0) const;
            double real(double = 0) const;
            falk::type type() const;

            // Function for unique purpose of compatibility 
            // with parser generic structure.
            operator long() const;

            rvalue pow(const rvalue&);
         private:
            falk::fundamental::type _ftype;
            falk::structural::type _stype;
            std::vector<value> values;
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

        // struct value methods
        inline rvalue::value::operator bool() const {
            return static_cast<bool>(real);
        }

        inline rvalue::value::operator double() const {
            return real;
        }

        inline rvalue::value::operator std::complex<double>() const {
            return {real, imag};
        }

        // class rvalue methods
        inline rvalue::rvalue(double v):
          _ftype{falk::type::REAL}, values{{v, 0}} { }
        
        inline rvalue::rvalue(std::complex<double> v):
          _ftype{falk::type::COMPLEX}, values{{v.real(), v.imag()}} { }
        
        inline rvalue::rvalue(falk::type type, double real, double imag):
          _ftype{type}, values{{real, imag}} { }
        
        inline rvalue::rvalue(bool v):
          _ftype{falk::type::BOOL}, values{{static_cast<double>(v), 0}} { }

        inline std::complex<double> rvalue::complex(double i) const {
            return values.at(i);
        }

        inline bool rvalue::boolean(double i) const {
            return values.at(i);
        }

        inline double rvalue::imag(double i) const {
            return values.at(i);
        }

        inline double rvalue::real(double i) const {
            return values.at(i);
        }

        inline falk::type rvalue::type() const {
            return _ftype;
        }

        inline rvalue::operator long() const {
            return static_cast<long>(values.at(0).real);
        }

    }
}

#endif /* FALK_EVALUATOR_RVALUE */
