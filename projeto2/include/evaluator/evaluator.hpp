
#ifndef FALK_EVALUATOR_REAL_HPP
#define FALK_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "array_index.hpp"
#include "base/operators.hpp"
#include "base/types.hpp"
#include "function.hpp"
#include "identifier.hpp"
#include "matrix_index.hpp"
#include "symbol_mapper.hpp"
#include "value.hpp"

#include "sma/value.hpp"

namespace falk {
    namespace ev {
        // Responsible for all semantic actions in 'interpreted mode'
        class evaluator {
         public:
            // Aliases to define semantical types (objects).
            using real = double;
            using complex = std::complex<double>;
            using boolean = bool;

            // Alias to define semantic abstraction for values.
            using value = sma::value<evaluator>;

            // Methods
            // assignment assign(identifier, value);
            // assignment assign(identifier, value, falk::op::Arithmetical);
            
            int create_program() { return 0; }
            
            // declaration declare_array(const std::string&);
            // declaration declare_array(const std::string&, value&);
            // declaration declare_array(const std::string&, value&);
            
            // declaration declare_variable(const std::string&);
            // declaration declare_variable(const std::string&, Type);
            // declaration declare_variable(const std::string&, value);
            
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

            value single_calculation(value value);
         private:
            symbol_mapper mapper;

         public:
            static constexpr auto ADD = 
                operation<op::Arithmetical, 2>{op::Arithmetical::ADD};
            static constexpr auto SUB =
                operation<op::Arithmetical, 2>{op::Arithmetical::SUB};
            static constexpr auto MULT =
                operation<op::Arithmetical, 2>{op::Arithmetical::MULT};
            static constexpr auto DIV =
                operation<op::Arithmetical, 2>{op::Arithmetical::DIV};
            static constexpr auto POW =
                operation<op::Arithmetical, 2>{op::Arithmetical::POW};
            static constexpr auto MOD =
                operation<op::Arithmetical, 2>{op::Arithmetical::MOD};
            static constexpr auto AND =
                operation<op::Logical, 2>{op::Logical::AND};
            static constexpr auto OR =
                operation<op::Logical, 2>{op::Logical::OR};
            static constexpr auto NOT =
                operation<op::Logical, 2>{op::Logical::NOT};
            static constexpr auto ADD_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::ADD_ASSIGN};
            static constexpr auto SUB_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::SUB_ASSIGN};
            static constexpr auto MULT_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::MULT_ASSIGN};
            static constexpr auto DIV_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::DIV_ASSIGN};
            static constexpr auto POW_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::POW_ASSIGN};
            static constexpr auto MOD_ASSIGN =
                operation<op::Arithmetical, 2>{op::Arithmetical::MOD_ASSIGN};
            static constexpr auto UNARY_SUB =
                operation<op::Arithmetical, 1>{op::Arithmetical::SUB};
        };


        inline evaluator::real evaluator::make_real(const std::string& text) {
            return std::stod(text);
        }

        inline evaluator::complex evaluator::make_complex(const std::string& text) {
            // TODO
            return std::complex<double>{};
        }

        inline evaluator::boolean evaluator::make_boolean(const std::string& text) {
            return text == "true";
        }

        inline int evaluator::new_line() {
            std::cout << "falk> ";
            return 0;
        }

        inline evaluator::value evaluator::single_calculation(value value) {
            // std::cout << "res = " << value << std::endl;
            return value;
        }
    }
}

#endif /* FALK_EVALUATOR_REAL_HPP */
