
#ifndef FALK_EV_AST_EVALUATOR_REAL_HPP
#define FALK_EV_AST_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "base/operators.hpp"
#include "base/types.hpp"
#include "function.hpp"
#include "symbol_mapper.hpp"

#include "sma/value.hpp"

namespace falk {
    namespace ev {
        // Responsible for all semantic actions in 'interpreted mode'
        class ast_evaluator {
            using node = ast::node<ast_evaluator>;
            using node_ptr = std::shared_ptr<node>;
         public:
            // Aliases to define semantical types (objects).
            using real    = double;
            using complex = std::complex<double>;
            using boolean = bool;

            // Alias to define semantic abstraction for values.
            using rvalue = sma::value<ast_evaluator>;
            using lvalue = int; // TODO

            using falk::op;

            // Methods
            // assignment assign(identifier, value);
            // assignment assign(identifier, value, falk::op::arithmetic);
            
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
            void analyse(ADD, std::array<node_ptr, 2>&);
            void analyse(SUB, std::array<node_ptr, 2>&);
            void analyse(MULT, std::array<node_ptr, 2>&);
            void analyse(DIV, std::array<node_ptr, 2>&);
            void analyse(POW, std::array<node_ptr, 2>&);
            void analyse(MOD, std::array<node_ptr, 2>&);

            void analyse(ADD_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(SUB_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(MULT_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(DIV_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(POW_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(MOD_ASSIGN, std::array<node_ptr, 2>&);

            void analyse(SUB_UNARY, std::array<node_ptr, 1>&);

            value single_calculation(value value);
         private:
            symbol_mapper mapper;
            std::stack<value> stacker;

            void calc(const std::function<value(value, value)>&);
        };


        inline ast_evaluator::real ast_evaluator::make_real(const std::string& text) {
            return std::stod(text);
        }

        inline ast_evaluator::complex ast_evaluator::make_complex(const std::string& text) {
            // TODO
            return std::complex<double>{};
        }

        inline ast_evaluator::boolean ast_evaluator::make_boolean(const std::string& text) {
            return text == "true";
        }

        inline int ast_evaluator::new_line() {
            std::cout << "falk> ";
            return 0;
        }

        inline ast_evaluator::value ast_evaluator::single_calculation(value value) {
            // std::cout << "res = " << value << std::endl;
            return value;
        }
    }
}

#endif /* FALK_EV_AST_EVALUATOR_REAL_HPP */
