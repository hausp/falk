
#include "evaluator/evaluator.hpp"

void falk::ev::evaluator::analyse(scalar value) {
    var_stacker.push(value);
    types_stacker.push(structural::type::VARIABLE);
}

falk::ev::evaluator::rvalue& falk::ev::evaluator::single_calculation(rvalue& value) {
    if (!value.empty()) {
        value.traverse(*this);
        auto type = aut::pop(types_stacker);
        switch (type) {
            case structural::type::VARIABLE: {
                auto v = aut::pop(var_stacker);
                std::cout << "res = " << v << std::endl;
                break;
            }
            case structural::type::ARRAY: {
                auto v = aut::pop(array_stacker);
                // std::cout << "res = " << v << std::endl;
                break;
            }
            case structural::type::MATRIX: {
                auto v = aut::pop(matrix_stacker);
                // std::cout << "res = " << v << std::endl;
                break;
            }
        }
    }
    return value;
}
