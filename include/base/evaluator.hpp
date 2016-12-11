
#ifndef FALK_EV_AST_EVALUATOR_REAL_HPP
#define FALK_EV_AST_EVALUATOR_REAL_HPP

#include <complex>
#include <iostream>
#include <stack>

#include "actions.hpp"
#include "ast/declaration.hpp"
#include "ast/list.hpp"
#include "ast/lvalue.hpp"
#include "ast/rvalue.hpp"
#include "aut/utilities.hpp"
#include "operators.hpp"
#include "symbol_mapper.hpp"
#include "types.hpp"
#include "types/array.hpp"
#include "types/matrix.hpp"

namespace falk {
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
        using array = array;
        using matrix = matrix;
        using scalar = scalar;

        // Alias to define abstractions for AST construction.
        using declaration = ast::declaration<evaluator>;
        using empty = ast::empty_node<evaluator>;
        using list = ast::list<evaluator>;
        using lvalue = ast::lvalue<evaluator>;
        using rvalue = ast::rvalue<evaluator>;

        // enable/disable console mode (see prompt() method)
        void console_mode(bool);
        // instantiates a real token
        real make_real(const std::string&);
        // instantiates a complex token
        complex make_complex(const std::string&);
        // instantiates a boolean token
        boolean make_boolean(const std::string&);

        // store values in the correspondent stack (see push(...) methods)
        template<typename T>
        void analyse(const T&);
        // executes a block of commands 
        void analyse(const block&, std::list<node_ptr>&);
        // executes conditionals (if-then-else)
        void analyse(const conditional&, node_array<3>&);
        // creates a structure to store data to initialize arrays and matrices
        void analyse(const create_structure&, std::list<node_ptr>&);
        // declares a variable
        void analyse(const declare_variable&, node_array<1>&);
        // declares a function
        void analyse(const declare_function&, node_array<1>&);
        // executes 'for' loops
        void analyse(const for_it&, node_array<2>&);
        // executes 'while' loops
        void analyse(const loop&, node_array<2>&);
        // place a value as return
        void analyse(const ret&, node_array<1>&);
        // remove definition of a given function
        void analyse(const undef&);
        // retrieves a given id as function
        void analyse(fun_id&, node_array<1>&);
        // retrieves a given id as variable
        void analyse(var_id&, node_array<2>&);
        // prints a value
        void analyse(const print&, node_array<1>&);
        // creates a scope around the node
        void analyse(const scoped&, node_array<1>&);
        // get the value of an lvalue
        void analyse(const valueof&, node_array<1>&);
        // get the type of an lvalue
        void analyse(const typeof&, node_array<1>&);
        // Creates a value with the specified type in materialize struct
        // and with size passed by the node
        void analyse(const materialize&, node_array<1>&);
        // Binary calculations
        template<typename Type, Type OP>
        void analyse(op::callback<Type, OP, 2>, node_array<2>&);
        // Unary calculations
        template<typename Type, Type OP>
        void analyse(op::callback<Type, OP, 1>, node_array<1>&);
        // Binary operation-assignment calculations
        template<op::assignment OP>
        void analyse(op::callback<op::assignment, OP, 2>, node_array<2>&);
        // Auxiliar method for calculations
        template<typename Operation, typename Stack>
        void handle_operation(const Operation&, structural::type, Stack&);
        // Auxiliar method for variable declarations
        void get_value(symbol_mapper&, const declare_variable&);
        // Process a command, received as a node
        void process(node_ptr);
        // prompts "falk>"
        void prompt();
        // pushes a scalar to scalar_stack
        void push(const scalar&);
        // pushes a array to array_stack
        void push(const array&);
        // pushes a matrix to matrix_stack
        void push(const matrix&);
        // pushes a var_id to id_stack
        void push(const var_id&);
     private:
        symbol_mapper mapper;
        std::deque<scalar> scalar_stack;
        std::deque<array> array_stack;
        std::deque<matrix> matrix_stack;
        std::deque<var_id> id_stack;
        std::deque<structural::type> types_stack;
        bool console = true;
        bool return_called = false;
        size_t function_counter = 0;
        // size_t return_counter = 0;
    };
}

#include "evaluator.ipp"

#endif /* FALK_EV_AST_EVALUATOR_REAL_HPP */
