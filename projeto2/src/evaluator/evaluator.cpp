
#include "evaluator/evaluator.hpp"
#include "evaluator/expr.hpp"

const auto falk::ev::evaluator::ADD = 
    operation<op::Arithmetical, 2>{op::Arithmetical::ADD};
const auto falk::ev::evaluator::SUB =
    operation<op::Arithmetical, 2>{op::Arithmetical::SUB};
const auto falk::ev::evaluator::MULT =
    operation<op::Arithmetical, 2>{op::Arithmetical::MULT};
const auto falk::ev::evaluator::DIV =
    operation<op::Arithmetical, 2>{op::Arithmetical::DIV};
const auto falk::ev::evaluator::POW =
    operation<op::Arithmetical, 2>{op::Arithmetical::POW};
const auto falk::ev::evaluator::MOD =
    operation<op::Arithmetical, 2>{op::Arithmetical::MOD};
const auto falk::ev::evaluator::AND =
    operation<op::Logical, 2>{op::Logical::AND};
const auto falk::ev::evaluator::OR =
    operation<op::Logical, 2>{op::Logical::OR};
const auto falk::ev::evaluator::NOT =
    operation<op::Logical, 2>{op::Logical::NOT};
const auto falk::ev::evaluator::ADD_ASSIGN =
    operation<op::Arithmetical, 2>{op::Arithmetical::ADD_ASSIGN};
const auto falk::ev::evaluator::SUB_ASSIGN =
    operation<op::Arithmetical, 2>{op::Arithmetical::SUB_ASSIGN};
const auto falk::ev::evaluator::MULT_ASSIGN =
    operation<op::Arithmetical, 2>{op::Arithmetical::MULT_ASSIGN};
const auto falk::ev::evaluator::DIV_ASSIGN =
    operation<op::Arithmetical, 2>{op::Arithmetical::DIV_ASSIGN};
const auto falk::ev::evaluator::POW_ASSIGN =
    operation<op::Arithmetical, 2>{op::Arithmetical::POW_ASSIGN};
const auto falk::ev::evaluator::MOD_ASSIGN =
    operation<op::Arithmetical, 2>{op::Arithmetical::MOD_ASSIGN};
const auto falk::ev::evaluator::UNARY_SUB =
    operation<op::Arithmetical, 1>{op::Arithmetical::SUB};

void falk::ev::evaluator::analyse(real value) {
    real_stack.push(value);
}

void falk::ev::evaluator::analyse(complex value) {
    complex_stack.push(value);
}

void falk::ev::evaluator::analyse(boolean value) {
    boolean_stack.push(value);
}

void falk::ev::evaluator::analyse(operation<op::Arithmetical, 2> op, std::array<node_ptr, 2>& operands) {
    using callback = std::function<void(evaluator&)>;
    static const std::unordered_map<decltype(op), callback> functions = {
        {ADD, [](evaluator& instance) {

        }}
    }

    // auto fn = functions[op];
}

void falk::ev::evaluator::analyse(operation<op::Arithmetical, 1> op, std::array<node_ptr, 1>& operand) {
    switch (op) {
        // TODO
    }
}

// falk::ev::evaluator::program falk::ev::evaluator::append(program, command) {
// 	return program{};
// }

// falk::ev::evaluator::array_index falk::ev::evaluator::make_array_index(value) {
// 	return array_index{};
// }

// falk::ev::evaluator::assignment falk::ev::evaluator::assign(identifier id, value val) {
// 	mapper.assign(id, val);
// 	return val; // é ou não - GRAF, Merlseson. 2016.
// }

// falk::ev::evaluator::assignment falk::ev::evaluator::assign(identifier id, value val, op::Arithmetical op) {
// 	auto curr_value = mapper.get(id);
// 	// TODO: apply op(curr_value, val)
// 	// mapper.assign(id, ??);
// 	return assignment{};
// }

// falk::ev::evaluator::program falk::ev::evaluator::create_program() {
// 	return program{};
// }
// falk::ev::evaluator::command falk::ev::evaluator::empty_command() {
// 	return command{};
// }

// falk::ev::evaluator::declaration falk::ev::evaluator::declare_array(const std::string&) {
// 	return declaration{};
// }
// falk::ev::evaluator::declaration falk::ev::evaluator::declare_array(const std::string&, array_index) {
// 	return declaration{};
// }
// falk::ev::evaluator::declaration falk::ev::evaluator::declare_array(const std::string&, init_list) {
// 	return declaration{};
// }

// falk::ev::evaluator::declaration falk::ev::evaluator::declare_variable(const std::string&) {
// 	return declaration{};
// }
// falk::ev::evaluator::declaration falk::ev::evaluator::declare_variable(const std::string&, Type) {
// 	return declaration{};
// }
// falk::ev::evaluator::declaration falk::ev::evaluator::declare_variable(const std::string&, value) {
// 	return declaration{};
// }

// falk::ev::evaluator::declaration falk::ev::evaluator::declare_matrix(const std::string&) {
// 	return declaration{};
// }
// falk::ev::evaluator::declaration falk::ev::evaluator::declare_matrix(const std::string&, matrix_index) {
// 	return declaration{};
// }
// falk::ev::evaluator::declaration falk::ev::evaluator::declare_matrix(const std::string&, init_list) {
// 	return declaration{};
// }

// value falk::ev::evaluator::make_real(const std::string& text) {
// 	return value{};
// }

// value falk::ev::evaluator::make_complex(const std::string& text) {
// 	return value{};
// }

// value falk::ev::evaluator::make_boolean(const std::string& yytext) {
// 	return value{};
// }

// falk::ev::evaluator::matrix_index falk::ev::evaluator::make_matrix_index(value) {
// 	return matrix_index{};
// }

// falk::ev::evaluator::matrix_index falk::ev::evaluator::make_matrix_index(value, value) {
// 	return matrix_index{};
// }

// control new_line() {
// 	return control{};
// }

// falk::ev::evaluator::control falk::ev::evaluator::semicolon() {
// 	return control{};
// }

// falk::ev::evaluator::identifier falk::ev::evaluator::retrieve_identifier(const std::string&) {
// 	return identifier{};
// }
// falk::ev::evaluator::identifier falk::ev::evaluator::retrieve_identifier(const std::string&, array_index) {
// 	return identifier{};
// }
// falk::ev::evaluator::identifier falk::ev::evaluator::retrieve_identifier(const std::string&, matrix_index) {
// 	return identifier{};
// }

// falk::ev::evaluator::value falk::ev::evaluator::pow(const value& lhs,
//                                                     const value& rhs) {
//     auto type = falk::resolve_types(lhs.type, rhs.type);
//     if (type == Type::REAL) {
//         // TODO
//     } else {
//         // TODO
//     }
//     return value{};
// }

