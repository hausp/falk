
#ifndef FALK_EVALUATOR_REAL_HPP
#define FALK_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "base/operators.hpp"
#include "base/types.hpp"
#include "numeric.hpp"

namespace falk {
    namespace ev {
        // Responsible for all semantic actions in 'interpreted mode'
        class Evaluator {
         public:
            using Type = Type;
            
            // using real = double;
            // using complex = std::complex<double>;
            using boolean = bool;
            using numeric = ev::numeric;
        public:
            numeric make_real(const std::string& yytext) {
                return {Type::REAL, std::stod(yytext), 0};
            }

            numeric make_complex(const std::string& yytext) {
                // TODO
                return numeric{Type::COMPLEX};
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

            void single_calculus(numeric value) {
                std::cout << "res = " << value << std::endl;
            }
         private:
            std::stack<double> real_values;
            std::stack<std::complex<double>> complex_values;
            std::stack<bool> boolean_values;
        };
    }
}

#endif /* FALK_EVALUATOR_REAL_HPP */
