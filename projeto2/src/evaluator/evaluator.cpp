
#include "ev/evaluator.hpp"

// void falk::ev::evaluator::analyse(const list_info& info,
//                                   const std::list<node_ptr>& nodes) {
//     std::cout << "TODO: handle lists" << std::endl;
//     switch(info.type) {
//         case structural::type::ARRAY:
//             std::cout << "Array creation" << std::endl;
//             std::cout << "size: " << nodes.size() << std::endl;
//             break;
//         case structural::type::MATRIX:
//             std::cout << "Matrix creation" << std::endl;
//             std::cout << "size: " << nodes.size() << std::endl;
//             break;
//         default:;
//     }
//     for (auto& value : nodes) {
//         if (!value) {
//             // TODO: why does this happen?
//             continue;
//         }
//         // TODO: actually create the array
//         value->traverse(*this);
//     }
// }

void falk::ev::evaluator::analyse(const scalar& value) {
    var_stacker.push(value);
    types_stacker.push(structural::type::SCALAR);
}

void falk::ev::evaluator::analyse(const array& container) {
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
                std::cout << "res = " << v << std::endl;
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
