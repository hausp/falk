
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

            void analyse(rvalue);
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

            rvalue single_calculation(rvalue value);
         private:
            symbol_mapper mapper;
            std::stack<rvalue> var_stacker;
            std::stack<array> array_stacker;
            std::stack<matrix> matrix_stacker;
            std::stack<structural::type> types_stacker;

            template<typename T>
            void calc(std::array<node_ptr, 2>& operands, T callback) {
                for (auto& op : operands) {
                    op->traverse(*this);
                }

                auto t1 = aut::pop(types_stacker);
                auto t2 = aut::pop(types_stacker);

                if (t1 == t2) {
                    switch (t1) {
                        case structural::type::VARIABLE: {
                            auto lhs = aut::pop(var_stacker);
                            auto rhs = aut::pop(var_stacker);
                            auto result = callback(lhs, rhs);
                            var_stacker.push(result);
                            break;
                        }
                        case structural::type::ARRAY: {
                            auto lhs = aut::pop(array_stacker);
                            auto rhs = aut::pop(array_stacker);
                            auto result = callback(lhs, rhs);
                            array_stacker.push(result);
                            break;
                        }
                        case structural::type::MATRIX: {
                            auto lhs = aut::pop(matrix_stacker);
                            auto rhs = aut::pop(matrix_stacker);
                            auto result = callback(lhs, rhs);
                            matrix_stacker.push(result);
                            break;
                        }
                    }
                }
            }

            template<typename T>
            void calc_assign(std::array<node_ptr, 2>& operands, T callback) {
                for (auto& op : operands) {
                    op->traverse(*this);
                }

                auto t1 = aut::pop(types_stacker);
                auto t2 = aut::pop(types_stacker);

                if (t1 == t2) {
                    switch (t1) {
                        case structural::type::VARIABLE: {
                            auto lhs = aut::pop(var_stacker);
                            auto rhs = aut::pop(var_stacker);
                            auto result = callback(lhs, rhs);
                            // TODO
                            break;
                        }
                        case structural::type::ARRAY: {
                            auto lhs = aut::pop(array_stacker);
                            auto rhs = aut::pop(array_stacker);
                            auto result = callback(lhs, rhs);
                            // TODO
                            break;
                        }
                        case structural::type::MATRIX: {
                            auto lhs = aut::pop(matrix_stacker);
                            auto rhs = aut::pop(matrix_stacker);
                            auto result = callback(lhs, rhs);
                            // TODO
                            break;
                        }
                    }
                }
            }
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

        inline ast_evaluator::rvalue ast_evaluator::single_calculation(rvalue value) {
            rvalue->traverse(*this);
            // std::cout << "res = " << value << std::endl;
            return value;
        }
    }
}

#endif /* FALK_EV_AST_EVALUATOR_REAL_HPP */
