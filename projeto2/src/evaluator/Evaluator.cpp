
#include "evaluator/Evaluator.hpp"
#include "evaluator/arithmetic_expr.hpp"
#include "evaluator/rvalue.hpp"

void falk::Evaluator::evaluate(rvalue& node) {
    switch (node.type) {
        case Type::UNDEFINED:
            // TODO
            break;
        case Type::REAL:
            real_values.push(std::stod(node.value));
            break;
        case Type::COMPLEX:
            // TODO
            // real_values.push(std::stod(node.value));
            break;
        case Type::BOOL:
            // TODO
            // real_values.push(std::stod(node.value));
            break;
    }
}

void falk::Evaluator::evaluate(arithmetic_expr& expr) {
    switch (expr.operation) {
        case op::Arithmetical::ADD:
            break;
        case op::Arithmetical::SUB:
            break;
        case op::Arithmetical::MULT:
            break;
        case op::Arithmetical::DIV:
            break;
        case op::Arithmetical::POW:
            break;
        case op::Arithmetical::MOD:
            break;
    }
}