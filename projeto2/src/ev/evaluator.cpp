#include "base/errors.hpp"
#include "ev/evaluator.hpp"

// void falk::ev::evaluator::analyse(const scalar& value) {
//     scalar_stack.push(value);
//     types_stack.push(structural::type::SCALAR);
// }

// void falk::ev::evaluator::analyse(const array& container) {
//     array_stack.push(container);
//     types_stack.push(structural::type::ARRAY);
// }

// void falk::ev::evaluator::analyse(const matrix& container) {
//     matrix_stack.push(container);
//     types_stack.push(structural::type::MATRIX);
// }

// void falk::ev::evaluator::analyse(const identifier& id) {
    
// }

void falk::ev::evaluator::analyse(const declare_variable& var,
                                  node_array<1>& nodes) {
    switch (var.s_type) {
        case structural::type::SCALAR: {
            if (!nodes[0]->empty()) {
                nodes[0]->traverse(*this);
                // TODO: assigned to Ghabriel
            } else {
                mapper.declare_variable(var.id, variable(var.f_type));
            }
            break;
        }
        case structural::type::ARRAY: {
            // TODO: assigned to Ghabriel
            break;
        }
        case structural::type::MATRIX: {
            // TODO: assigned to Ghabriel
            break;
        }
        default:;
    }
}

void falk::ev::evaluator::analyse(const valueof& request) {
    std::cout << "hello" << std::endl;
    auto& var = mapper.retrieve_variable(request.id);
    switch (var.stored_type()) {
        case structural::type::SCALAR: {
            std::cout << "darkness" << std::endl;
            push(var.value<scalar>());
            break;
        }
        case structural::type::ARRAY: {
            push(var.value<array>());
            break;
        }
        case structural::type::MATRIX: {
            push(var.value<matrix>());
            break;
        }
        default:
            std::cout << "satan" << std::endl;
    }
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
    auto type = aut::pop(types_stack);
    if (type == structural::type::SCALAR) {
        auto result = aut::pop(scalar_stack);
        if (result.boolean()) {
            nodes[1]->traverse(*this);
        } else {
            nodes[2]->traverse(*this);
        }
    } else {
        err::semantic<Error::NON_BOOLEAN_CONDITION>();
    }
}

void falk::ev::evaluator::analyse(const loop&, node_array<2>& nodes) {
    nodes[0]->traverse(*this);
    auto type = aut::pop(types_stack);
    if (type == structural::type::SCALAR) {
        // TODO
        std::cout << "while loop" << std::endl;
    } else {
        err::semantic<Error::NON_BOOLEAN_CONDITION>();
    }
}

void falk::ev::evaluator::process(value& v) {
    if (!v.empty()) {
        v.traverse(*this);
    }

    while (!types_stack.empty()) {
        print_result();
    }
}

void falk::ev::evaluator::print_result() {
    auto type = aut::pop(types_stack);
    switch (type) {
        case structural::type::SCALAR: {
            auto result = aut::pop(scalar_stack);
            if (!result.error()) {
                std::cout << "res = " << result << std::endl;
            }
            break;
        }
        case structural::type::ARRAY: {
            auto result = aut::pop(array_stack);
            if (!result.error()) {
                std::cout << "res = " << result << std::endl;
            }
            break;
        }
        case structural::type::MATRIX: {
            auto result = aut::pop(matrix_stack);
            if (!result.error()) {
                std::cout << "res = " << result << std::endl;
            }
            break;
        }
    }
}

falk::ev::array& falk::ev::evaluator::extract(array& arr, value& v) {
    v.traverse(*this);
    if (aut::pop(types_stack) == structural::type::SCALAR) {
        auto scalar = aut::pop(scalar_stack);
        arr.push_back(scalar);
    } else {
        // TODO: error
    }
    return arr;
}
