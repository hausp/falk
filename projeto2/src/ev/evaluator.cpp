
#include "ev/evaluator.hpp"

void falk::ev::evaluator::analyse(const scalar& value) {
    var_stacker.push(value);
    types_stacker.push(structural::type::SCALAR);
}

void falk::ev::evaluator::analyse(const array& container) {
    array_stacker.push(container);
    types_stacker.push(structural::type::ARRAY);
}

void falk::ev::evaluator::analyse(const matrix& container) {
    matrix_stacker.push(container);
    types_stacker.push(structural::type::MATRIX);
}

falk::ev::evaluator::value& falk::ev::evaluator::single_calculation(value& v) {
    if (!v.empty()) {
        v.traverse(*this);
        auto type = aut::pop(types_stacker);
        switch (type) {
            case structural::type::SCALAR: {
                auto result = aut::pop(var_stacker);
                if (!result.error()) {
                    std::cout << "res = " << result << std::endl;
                }
                break;
            }
            case structural::type::ARRAY: {
                auto result = aut::pop(array_stacker);
                if (!result.error()) {
                    std::cout << "res = " << result << std::endl;
                }
                break;
            }
            case structural::type::MATRIX: {
                auto result = aut::pop(matrix_stacker);
                if (!result.error()) {
                    std::cout << "res = " << result << std::endl;
                }
                break;
            }
        }
    }
    return v;
}

falk::ev::array& falk::ev::evaluator::extract(array& arr, value& v) {
    v.traverse(*this);
    if (aut::pop(types_stacker) == structural::type::SCALAR) {
        auto scalar = aut::pop(var_stacker);
        arr.push_back(scalar);
    } else {
        // TODO: error
    }
    return arr;
}
