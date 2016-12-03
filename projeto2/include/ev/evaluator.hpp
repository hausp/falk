
#ifndef FALK_EV_AST_EVALUATOR_REAL_HPP
#define FALK_EV_AST_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "array.hpp"
#include "aut/utilities.hpp"
#include "base/actions.hpp"
#include "base/operators.hpp"
#include "base/types.hpp"
#include "function.hpp"
#include "matrix.hpp"
#include "symbol_mapper.hpp"
#include "ast/declaration.hpp"
#include "ast/list.hpp"
#include "ast/lvalue.hpp"
#include "ast/rvalue.hpp"

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
            using scalar = ev::scalar;

            // Alias to define semantic abstraction for values.
            using declaration = ast::declaration<evaluator>;
            using empty = ast::empty_node<evaluator>;
            using list = ast::list<evaluator>;
            using lvalue = ast::lvalue<evaluator>;
            using rvalue = ast::rvalue<evaluator>;

            void initialize();
            real make_real(const std::string&);
            complex make_complex(const std::string&);
            boolean make_boolean(const std::string&);

            template<typename T>
            void analyse(const T&);
            void analyse(const declare_variable&, node_array<1>&);
            void analyse(const block&, std::list<node_ptr>&);
            void analyse(const conditional&, node_array<3>&);
            void analyse(const loop&, node_array<2>&);
            
            void analyse(var_id&, node_array<2>&);
            void analyse(const valueof&, node_array<1>&);

            void analyse(const create_structure&, std::list<node_ptr>&);

            // Binary calculations
            template<typename Type, Type OP>
            void analyse(op::callback<Type, OP, 2>, node_array<2>&);
            // Unary calculations
            template<typename Type, Type OP>
            void analyse(op::callback<Type, OP, 1>, node_array<1>&);

            // Binary operation-assignment calculations
            template<op::assignment OP>
            void analyse(op::callback<op::assignment, OP, 2>, node_array<2>&);
            
            array& extract(array&, rvalue&);

            template<typename Operation, typename Stack>
            void handle_operation(const Operation&, structural::type, Stack&);

            void print_result();
            void process(rvalue&);
            void prompt();

            void push(const scalar&);
            void push(const array&);
            void push(const matrix&);
            void push(const var_id&);
         private:
            symbol_mapper mapper;
            std::stack<scalar> scalar_stack;
            std::stack<array> array_stack;
            std::stack<matrix> matrix_stack;
            std::stack<var_id> id_stack;
            std::stack<structural::type> types_stack;
        };
    }
}

#include "evaluator.ipp"

#endif /* FALK_EV_AST_EVALUATOR_REAL_HPP */
