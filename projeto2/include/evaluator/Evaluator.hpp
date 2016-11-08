
#ifndef FALK_EVALUATOR_REAL_HPP
#define FALK_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "base/operators.hpp"
#include "base/types.hpp"
#include "value.hpp"

namespace falk {
    namespace ev {
        // Responsible for all semantic actions in 'interpreted mode'
        class Evaluator {
         public:
            using Type = Type;
            
            // using real = double;
            // using complex = std::complex<double>;
            using boolean = bool;
            using value = ev::value;
        public:
            value make_real(const std::string& yytext) {
                return {Type::REAL, std::stod(yytext), 0};
            }

            value make_complex(const std::string& yytext) {
                // TODO
                return value{Type::COMPLEX};
            }

            value make_boolean(const std::string& yytext) {
                if (yytext == "true") {
                    return TRUE;
                }
                return FALSE;
            }

            void new_line() {
                std::cout << "falk> ";
            }

            void single_calculus(value value) {
                std::cout << "res = " << value << std::endl;
            }

            static value pow(const value& lhs, const value& rhs) {
                auto type = falk::resolve_types(lhs.type, rhs.type);
                if (type == Type::REAL) {
                    // TODO
                } else {
                    // TODO
                }
                return value{};
            }
         private:
            std::stack<double> real_values;
            std::stack<std::complex<double>> complex_values;
            std::stack<bool> boolean_values;
        };
    }
}

#endif /* FALK_EVALUATOR_REAL_HPP */
