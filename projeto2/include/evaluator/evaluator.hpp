
#ifndef FALK_EV_AST_EVALUATOR_REAL_HPP
#define FALK_EV_AST_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "aut/utilities.hpp"
#include "base/operators.hpp"
#include "base/types.hpp"
#include "evaluator/array.hpp"
#include "evaluator/matrix.hpp"
#include "function.hpp"
#include "symbol_mapper.hpp"
#include "sma/value.hpp"
#include "sma/list.hpp"

namespace falk {
    namespace ev {
        // Responsible for all semantic actions in 'interpreted mode'
        class evaluator {
            using node = ast::node<evaluator>;
            using node_ptr = std::shared_ptr<node>;
            template<size_t S>
            using node_array = std::array<node_ptr, S>;
         public:
            // Aliases to define semantical types (objects).
            using real = double;
            using complex = std::complex<double>;
            using boolean = bool;
            using array = ev::array;
            using matrix = ev::matrix;

            // Alias to define semantic abstraction for values.
            using value = sma::value<evaluator, falk::op>;
            using list = sma::list<evaluator>;

            // Methods
            // assignment assign(identifier, value);
            // assignment assign(identifier, value, falk::op::arithmetic);
            
            int create_program();
            
            // declaration declare_array(const std::string&);
            // declaration declare_array(const std::string&, value&);
            // declaration declare_array(const std::string&, value&);
            
            // declaration declare_variable(const std::string&);
            // declaration declare_variable(const std::string&, Type);
            // declaration declare_variable(const std::string&, value);
            
            // declaration declare_matrix(const std::string&);
            // declaration declare_matrix(const std::string&, matrix_index);
            // declaration declare_matrix(const std::string&, init_list);

            real make_real(const std::string&);
            complex make_complex(const std::string&);
            boolean make_boolean(const std::string&);

            int new_line();

            // identifier retrieve_identifier(const std::string&) { return identifier{}; }
            // identifier retrieve_identifier(const std::string&, array_index) { return identifier{}; }
            // identifier retrieve_identifier(const std::string&, matrix_index) { return identifier{}; }

            void analyse(const scalar&);
            void analyse(const array&);
            void analyse(const matrix&);

            void analyse(const op::LIST&, const std::list<node_ptr>&);

            // TODO: can the methods below be generalized?
            // Binary calculations
            template<typename Type, Type OP>
            void analyse(operation<Type, OP, 2, false>, node_array<2>&);
            // Unary calculations
            template<typename Type, Type OP>
            void analyse(operation<Type, OP, 1, false>, node_array<1>&);

            // Binary operation-assignment calculations
            template<typename Type, Type OP>
            void analyse(operation<Type, OP, 2, true>, node_array<2>&);

            value& single_calculation(value& value);
         private:
            symbol_mapper mapper;
            std::stack<scalar> var_stacker;
            std::stack<array> array_stacker;
            std::stack<matrix> matrix_stacker;
            std::stack<structural::type> types_stacker;
        };
    }
}

#include "evaluator.ipp"

#endif /* FALK_EV_AST_EVALUATOR_REAL_HPP */
