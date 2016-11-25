
#include "evaluator/evaluator.hpp"

void falk::ev::evaluator::analyse(scalar value) {
    var_stacker.push(value);
    types_stacker.push(structural::type::SCALAR);
}

falk::ev::evaluator::value& falk::ev::evaluator::single_calculation(value& v) {
    if (!v.empty()) {
        v.traverse(*this);
        auto type = aut::pop(types_stacker);
        switch (type) {
            case structural::type::SCALAR: {
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
    return v;
}
