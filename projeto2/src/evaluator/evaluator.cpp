
#include "evaluator/evaluator.hpp"

void falk::ev::evaluator::analyse(const op::LIST&, const std::list<node_ptr>& nodes) {
    std::cout << "TODO: handle lists" << std::endl;
    for (auto& value : nodes) {
        if (!value) {
            // TODO: why does this happen?
            continue;
        }
        // TODO: actually create the array
        value->traverse(*this);
    }
}

void falk::ev::evaluator::analyse(const scalar& value) {
    var_stacker.push(value);
    types_stacker.push(structural::type::SCALAR);
}

void falk::ev::evaluator::analyse(const array& container) {
    std::cout << "array" << std::endl;
    array_stacker.push(container);
    types_stacker.push(structural::type::ARRAY);
}

void falk::ev::evaluator::analyse(const matrix& container) {
    std::cout << "matrix" << std::endl;
    matrix_stacker.push(container);
    types_stacker.push(structural::type::MATRIX);
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
                std::cout << "type = array" << std::endl;
                // std::cout << "res = " << v << std::endl;
                break;
            }
            case structural::type::MATRIX: {
                auto v = aut::pop(matrix_stacker);
                std::cout << "type = matrix" << std::endl;
                // std::cout << "res = " << v << std::endl;
                break;
            }
        }
    }
    return v;
}
