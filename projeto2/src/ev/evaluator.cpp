
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

void falk::ev::evaluator::analyse(const block&, std::list<node_ptr>& nodes) {
    for (auto& node : nodes) {
        if (node) {
            node->traverse(*this);        
        }
    }
}

void falk::ev::evaluator::analyse(const conditional&, node_array<3>& nodes) {
    nodes[0]->traverse(*this);
    auto type = aut::pop(types_stacker);
    if (type == structural::type::SCALAR) {
        auto result = aut::pop(var_stacker);
        if (result) {
            nodes[1]->traverse(*this);
        } else {
            nodes[2]->traverse(*this);
        }
    } else {
        // TODO: error (expression must be boolean)
    }
}

void falk::ev::evaluator::process(value& v) {
    if (!v.empty()) {
        v.traverse(*this);
    }

    while (!types_stacker.empty()) {
        print_result();
    }
}

void falk::ev::evaluator::print_result() {
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
