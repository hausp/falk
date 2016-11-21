
#ifndef FALK_EVALUATOR_REAL_HPP
#define FALK_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "base/operators.hpp"
#include "base/types.hpp"
#include "function.hpp"
#include "symbol_mapper.hpp"
#include "lvalue.hpp"
#include "rvalue.hpp"

namespace falk {
    namespace ev {
        // Responsible for all semantic actions in 'interpreted mode'
        class evaluator {
         public:
            // Aliases to define semantical types (objects).
            using real = double;
            using complex = std::complex<double>;
            using boolean = bool;

            // Alias to define semantic abstraction for rvalues.
            using lvalue = ev::lvalue;
            using rvalue = ev::rvalue;

            // Methods
            // assignment assign(identifier, rvalue);
            // assignment assign(identifier, rvalue, falk::op::arithmetic);
            
            int create_program() { return 0; }
            
            // declaration declare_array(const std::string&);
            // declaration declare_array(const std::string&, rvalue&);
            // declaration declare_array(const std::string&, rvalue&);
            
            // declaration declare_variable(const std::string&);
            // declaration declare_variable(const std::string&, Type);
            // declaration declare_variable(const std::string&, rvalue);
            
            // declaration declare_matrix(const std::string&);
            // declaration declare_matrix(const std::string&, matrix_index);
            // declaration declare_matrix(const std::string&, init_list);

            real make_real(const std::string& text);
            complex make_complex(const std::string& text);
            boolean make_boolean(const std::string& yytext);

            int new_line();

            // identifier retrieve_identifier(const std::string&) { return identifier{}; }
            // identifier retrieve_identifier(const std::string&, array_index) { return identifier{}; }
            // identifier retrieve_identifier(const std::string&, matrix_index) { return identifier{}; }

            rvalue single_calculation(rvalue rvalue);
         private:
            symbol_mapper mapper;
        };


        inline evaluator::real evaluator::make_real(const std::string& text) {
            return std::stod(text);
        }

        inline evaluator::complex evaluator::make_complex(const std::string& text) {
            auto clean_text = text.substr(0, text.size() - 2);
            return std::complex<double>{0, std::stod(text)};
        }

        inline evaluator::boolean evaluator::make_boolean(const std::string& text) {
            return text == "true";
        }

        inline int evaluator::new_line() {
            std::cout << "falk> ";
            return 0;
        }

        inline evaluator::rvalue evaluator::single_calculation(rvalue rvalue) {
            std::cout << "res = " << rvalue << std::endl;
            return rvalue;
        }
    }
}

#endif /* FALK_EVALUATOR_REAL_HPP */
