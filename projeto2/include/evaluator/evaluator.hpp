
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
            using node = ast::node<evaluator>;
            using node_ptr = std::shared_ptr<node>;
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

            void analyse(real);
            void analyse(complex);
            void analyse(boolean);
            void analyse(operation<op::Arithmetical, 2>, std::array<node_ptr, 2>&);
            void analyse(operation<op::Arithmetical, 1>, std::array<node_ptr, 1>&);

            value single_calculation(value value);
         private:
            symbol_mapper mapper;
            std::stack<real> real_stack;
            std::stack<complex> complex_stack;
            std::stack<boolean> boolean_stack;

         public:
            static const operation<op::Arithmetical, 2> ADD;
            static const operation<op::Arithmetical, 2> SUB;
            static const operation<op::Arithmetical, 2> MULT;
            static const operation<op::Arithmetical, 2> DIV;
            static const operation<op::Arithmetical, 2> POW;
            static const operation<op::Arithmetical, 2> MOD;
            static const operation<op::Logical, 2> AND;
            static const operation<op::Logical, 2> OR;
            static const operation<op::Logical, 2> NOT;
            static const operation<op::Arithmetical, 2> ADD_ASSIGN;
            static const operation<op::Arithmetical, 2> SUB_ASSIGN;
            static const operation<op::Arithmetical, 2> MULT_ASSIGN;
            static const operation<op::Arithmetical, 2> DIV_ASSIGN;
            static const operation<op::Arithmetical, 2> POW_ASSIGN;
            static const operation<op::Arithmetical, 2> MOD_ASSIGN;
            static const operation<op::Arithmetical, 1> UNARY_SUB;
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
