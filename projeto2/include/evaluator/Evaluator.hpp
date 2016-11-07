
#ifndef FALK_EVALUATOR_REAL_HPP
#define FALK_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "base/types.hpp"

namespace falk {
    // Responsible for all semantic actions in 'interpreted mode'
    class Evaluator {
     public:
        class rvalue;
        class arithmetic_expr;

        using Type = Type;
        using real = double;
        using complex = std::complex<double>;
        using boolean = bool;
    public:
        void evaluate(rvalue&);
        void evaluate(arithmetic_expr&);

        real make_real(const std::string& yytext) {
            return std::stod(yytext);
        }

        complex make_complex(const std::string& yytext) {
            // TODO
            return complex{};
        }

        boolean make_boolean(const std::string& yytext) {
            if (yytext == "true") {
                return true;
            }
            return false;
        }

        void new_line() {
            std::cout << "falk> ";
        }

        void real_calculus(real value) {
            std::cout << "res = " << value << std::endl;
        }

        void complex_calculus(complex value) {
            std::cout << "res = " << value << std::endl;
        }
     private:
        std::stack<double> real_values;
        std::stack<std::complex<double>> complex_values;
        std::stack<bool> boolean_values;
    };
}

#endif /* FALK_EVALUATOR_REAL_HPP */
