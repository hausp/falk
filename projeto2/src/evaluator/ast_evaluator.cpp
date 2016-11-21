
#include "evaluator/ast_evaluator.hpp"

void falk::ev::ast_evaluator::analyse(scalar value) {
    var_stacker.push(value);
    types_stacker.push(structural::type::VARIABLE);
}

void falk::ev::ast_evaluator::analyse(op::ADD, std::array<node_ptr, 2>& operands) {
    calc(operands, [=](auto& lhs, auto& rhs) {
        return lhs + rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::SUB, std::array<node_ptr, 2>& operands) {
    calc(operands, [=](auto& lhs, auto& rhs) {
        return lhs - rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::MULT, std::array<node_ptr, 2>& operands) {
    calc(operands, [=](auto& lhs, auto& rhs) {
        return lhs * rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::DIV, std::array<node_ptr, 2>& operands) {
    calc(operands, [=](auto& lhs, auto& rhs) {
        return lhs / rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::POW, std::array<node_ptr, 2>& operands) {
    calc(operands, [=](auto& lhs, auto& rhs) {
        return lhs.pow(rhs);
    });
}

void falk::ev::ast_evaluator::analyse(op::MOD, std::array<node_ptr, 2>& operands) {
    calc(operands, [=](auto& lhs, auto& rhs) {
        return lhs % rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::ADD_ASSIGN, std::array<node_ptr, 2>& operands) {
    calc_assign(operands, [=](auto& lhs, auto& rhs) {
        return lhs += rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::SUB_ASSIGN, std::array<node_ptr, 2>& operands) {
    calc_assign(operands, [=](auto& lhs, auto& rhs) {
        return lhs -= rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::MULT_ASSIGN, std::array<node_ptr, 2>& operands) {
    calc_assign(operands, [=](auto& lhs, auto& rhs) {
        return lhs *= rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::DIV_ASSIGN, std::array<node_ptr, 2>& operands) {
    calc_assign(operands, [=](auto& lhs, auto& rhs) {
        return lhs /= rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::POW_ASSIGN, std::array<node_ptr, 2>& operands) {
    calc_assign(operands, [=](auto& lhs, auto& rhs) {
        return lhs.pow_assign(rhs);
    });
}

void falk::ev::ast_evaluator::analyse(op::MOD_ASSIGN, std::array<node_ptr, 2>& operands) {
    calc_assign(operands, [=](auto& lhs, auto& rhs) {
        return lhs %= rhs;
    });
}

void falk::ev::ast_evaluator::analyse(op::SUB_UNARY, std::array<node_ptr, 1>& operand) {
    operand[0]->traverse(*this);

    auto t1 = aut::pop(types_stacker);

    switch (t1) {
        case structural::type::VARIABLE: {
            auto lhs = aut::pop(var_stacker);
            auto result = -lhs;
            var_stacker.push(result);
            break;
        }
        case structural::type::ARRAY: {
            auto lhs = aut::pop(array_stacker);
            auto result = -lhs;
            array_stacker.push(result);
            break;
        }
        case structural::type::MATRIX: {
            auto lhs = aut::pop(matrix_stacker);
            auto result = -lhs;
            matrix_stacker.push(result);
            break;
        }
    }
}

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

