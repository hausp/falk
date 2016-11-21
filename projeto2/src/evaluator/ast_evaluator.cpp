
#include "evaluator/ast_evaluator.hpp"

void falk::ev::ast_evaluator::analyse(real value) {
    real_stack.push(value);
    types_stack.push(Type::REAL);
}

void falk::ev::ast_evaluator::analyse(complex value) {
    complex_stack.push(value);
    types_stack.push(Type::COMPLEX);
}

void falk::ev::ast_evaluator::analyse(boolean value) {
    boolean_stack.push(value);
    types_stack.push(Type::BOOL);
}

void falk::ev::ast_evaluator::analyse(ADD op, std::array<node_ptr, 2>& operands) {
    for (auto& op : operands) {
        op->traverse(*this);
    }

    auto t1 = types.top();
    types.pop();
    auto t2 = types.top();
    types.pop();

    if (t1 == structural::type::MATRIX && t1 == t2) {
        auto m1 = matrices.top();
        matrices.pop():
        auto m2 = matrices.top();
        matrices.pop():
        result = m1 + m2;
    }
}

void falk::ev::ast_evaluator::analyse(operation<op::arithmetic, 1> op, std::array<node_ptr, 1>& operand) {
    switch (op) {
        // TODO
    }
}

void falk::ev::ast_evaluator::calc(const std::function<value(value, value)>& fn) {
    auto lhs = stacker.top();
    stacker.pop();
    auto rhs = stacker.top();
    stacker.pop();

    auto result_type = resolve_types(lhs.type, rhs.type);
    // TODO: what if result_type == Type::UNDEFINED?

    stacker.push(fn(lhs, rhs));
};


// falk::ev::ast_evaluator::program falk::ev::ast_evaluator::append(program, command) {
//  return program{};
// }

// falk::ev::ast_evaluator::array_index falk::ev::ast_evaluator::make_array_index(value) {
//  return array_index{};
// }

// falk::ev::ast_evaluator::assignment falk::ev::ast_evaluator::assign(identifier id, value val) {
//  mapper.assign(id, val);
//  return val; // é ou não - GRAF, Merlseson. 2016.
// }

// falk::ev::ast_evaluator::assignment falk::ev::ast_evaluator::assign(identifier id, value val, op::arithmetic op) {
//  auto curr_value = mapper.get(id);
//  // TODO: apply op(curr_value, val)
//  // mapper.assign(id, ??);
//  return assignment{};
// }

// falk::ev::ast_evaluator::program falk::ev::ast_evaluator::create_program() {
//  return program{};
// }
// falk::ev::ast_evaluator::command falk::ev::ast_evaluator::empty_command() {
//  return command{};
// }

// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_array(const std::string&) {
//  return declaration{};
// }
// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_array(const std::string&, array_index) {
//  return declaration{};
// }
// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_array(const std::string&, init_list) {
//  return declaration{};
// }

// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_variable(const std::string&) {
//  return declaration{};
// }
// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_variable(const std::string&, Type) {
//  return declaration{};
// }
// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_variable(const std::string&, value) {
//  return declaration{};
// }

// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_matrix(const std::string&) {
//  return declaration{};
// }
// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_matrix(const std::string&, matrix_index) {
//  return declaration{};
// }
// falk::ev::ast_evaluator::declaration falk::ev::ast_evaluator::declare_matrix(const std::string&, init_list) {
//  return declaration{};
// }

// value falk::ev::ast_evaluator::make_real(const std::string& text) {
//  return value{};
// }

// value falk::ev::ast_evaluator::make_complex(const std::string& text) {
//  return value{};
// }

// value falk::ev::ast_evaluator::make_boolean(const std::string& yytext) {
//  return value{};
// }

// falk::ev::ast_evaluator::matrix_index falk::ev::ast_evaluator::make_matrix_index(value) {
//  return matrix_index{};
// }

// falk::ev::ast_evaluator::matrix_index falk::ev::ast_evaluator::make_matrix_index(value, value) {
//  return matrix_index{};
// }

// control new_line() {
//  return control{};
// }

// falk::ev::ast_evaluator::control falk::ev::ast_evaluator::semicolon() {
//  return control{};
// }

// falk::ev::ast_evaluator::identifier falk::ev::ast_evaluator::retrieve_identifier(const std::string&) {
//  return identifier{};
// }
// falk::ev::ast_evaluator::identifier falk::ev::ast_evaluator::retrieve_identifier(const std::string&, array_index) {
//  return identifier{};
// }
// falk::ev::ast_evaluator::identifier falk::ev::ast_evaluator::retrieve_identifier(const std::string&, matrix_index) {
//  return identifier{};
// }

// falk::ev::ast_evaluator::value falk::ev::ast_evaluator::pow(const value& lhs,
//                                                     const value& rhs) {
//     auto type = falk::resolve_types(lhs.type, rhs.type);
//     if (type == Type::REAL) {
//         // TODO
//     } else {
//         // TODO
//     }
//     return value{};
// }

