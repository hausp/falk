
#ifndef FALK_EV_AST_EVALUATOR_REAL_HPP
#define FALK_EV_AST_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "array.hpp"
#include "aut/utilities.hpp"
#include "base/operators.hpp"
#include "base/types.hpp"
#include "function.hpp"
#include "matrix.hpp"
#include "scalar.hpp"
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
            using rvalue = sma::value<ast_evaluator, falk::op>;
            using lvalue = int; // TODO

            // using namespace falk::op;

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

            void analyse(scalar);
            void analyse(op::ADD, std::array<node_ptr, 2>&);
            void analyse(op::SUB, std::array<node_ptr, 2>&);
            void analyse(op::MULT, std::array<node_ptr, 2>&);
            void analyse(op::DIV, std::array<node_ptr, 2>&);
            void analyse(op::POW, std::array<node_ptr, 2>&);
            void analyse(op::MOD, std::array<node_ptr, 2>&);

            void analyse(op::ADD_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(op::SUB_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(op::MULT_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(op::DIV_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(op::POW_ASSIGN, std::array<node_ptr, 2>&);
            void analyse(op::MOD_ASSIGN, std::array<node_ptr, 2>&);

            void analyse(op::SUB_UNARY, std::array<node_ptr, 1>&);

            rvalue& single_calculation(rvalue& value);
         private:
            symbol_mapper mapper;
            std::stack<scalar> var_stacker;
            std::stack<array> array_stacker;
            std::stack<matrix> matrix_stacker;
            std::stack<structural::type> types_stacker;

            template<typename T>
            void calc(std::array<node_ptr, 2>& operands, T callback);

            template<typename T>
            void calc_assign(std::array<node_ptr, 2>& operands, T callback);
        };
    }
}

#include "ast_evaluator.ipp"

#endif /* FALK_EV_AST_EVALUATOR_REAL_HPP */
