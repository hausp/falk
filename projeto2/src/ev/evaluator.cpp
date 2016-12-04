#include "base/errors.hpp"
#include "ev/evaluator.hpp"

void falk::ev::evaluator::analyse(const declare_variable& var,
                                  node_array<1>& nodes) {
    auto get_value = [this](auto& mapper, auto& var) {
        auto type = aut::pop(types_stack);
        if (type != var.s_type) {
            err::semantic<Error::ILLEGAL_ASSIGNMENT>(var.s_type, type);
            return;
        }

        switch (type) {
            case structural::type::SCALAR: {
                auto result = aut::pop(scalar_stack);
                if (!result.error()) {
                    mapper.declare_variable(
                        var.id, variable(result, structural::type::SCALAR)
                    );
                }
                break;
            }
            case structural::type::ARRAY: {
                auto result = aut::pop(array_stack);
                if (!result.error()) {
                    mapper.declare_variable(
                        var.id, variable(result, structural::type::ARRAY)
                    );
                }
                break;
            }
            case structural::type::MATRIX: {
                auto result = aut::pop(matrix_stack);
                if (!result.error()) {
                    mapper.declare_variable(
                        var.id, variable(result, structural::type::MATRIX)
                    );
                }
                break;
            }
        }
    };

    if (!nodes[0]->empty()) {
        nodes[0]->traverse(*this);
        get_value(mapper, var);
    } else {
        mapper.declare_variable(var.id, variable(var.f_type));
    }
}

void falk::ev::evaluator::analyse(const declare_function& fn,
                                  node_array<1>& nodes) {

}

void falk::ev::evaluator::analyse(var_id& vid, node_array<2>& index) {
    if (!index[0]->empty()) {
        index[0]->traverse(*this);
        auto type = aut::pop(types_stack);
        if (type != structural::type::SCALAR) {
            // TODO: error
            std::cout << "stop!" << std::endl;
        }
        vid.index.first = aut::pop(scalar_stack).real();
    }

    if (!index[1]->empty()) {
        index[1]->traverse(*this);
        auto type = aut::pop(types_stack);
        if (type != structural::type::SCALAR) {
            // TODO: error
            std::cout << "stop!!" << std::endl;
        }
        vid.index.second = aut::pop(scalar_stack).real();
    }

    push(vid);
}

void falk::ev::evaluator::analyse(const valueof&, node_array<1>& nodes) {
    nodes[0]->traverse(*this);

    // TODO: handle index
    // Assigned to Ghabriel
    auto vid = aut::pop(id_stack);
    auto& var = mapper.retrieve_variable(vid.id);

    switch (var.stored_type()) {
        case structural::type::SCALAR: {
            auto value = var.value<scalar>();
            if (vid.index.first > -1 || vid.index.second > -1) {
                err::semantic<Error::SCALAR_INDEXED_ACCESS>();
                value.set_error();
                push(value);
                return;
            }
            push(value);
            break;
        }
        case structural::type::ARRAY: {
            auto value = var.value<array>();
            if (vid.index.second > -1) {
                err::semantic<Error::TOO_MANY_INDEXES>();
                value.set_error();
                push(value);
                return;
            }

            if (vid.index.first > -1) {
                if (vid.index.first >= value.size()) {
                    err::semantic<Error::INDEX_OUT_OF_BOUNDS>(value.size(), vid.index.first);
                    value.set_error();
                    push(value);
                    return;
                }
                push(value[vid.index.first]);
            } else {
                push(var.value<array>());
            }
            break;
        }
        case structural::type::MATRIX: {
            auto value = var.value<matrix>();
            if (vid.index.first > -1 && vid.index.second > -1) {
                push(value.at(vid.index.first, vid.index.second));
            } else if (vid.index.first > -1) {
                push(value.row(vid.index.first));
            } else if (vid.index.second > -1) {
                push(value.column(vid.index.second));
            } else {
                push(value);
            }
            break;
        }
        // default:
        // THROW A BRICK AT THE USER
        // use of undefined variable
        // push(invalid_something);
    }
}

void falk::ev::evaluator::analyse(const block&, std::list<node_ptr>& nodes) {
    for (auto& node : nodes) {
        // TODO: solve this (problem number 666: unknown nullptr)
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
        mapper.open_scope();
        if (result.boolean()) {
            nodes[1]->traverse(*this);
        } else {
            nodes[2]->traverse(*this);
        }
        mapper.close_scope();
    } else {
        err::semantic<Error::NON_BOOLEAN_CONDITION>();
    }
}

void falk::ev::evaluator::analyse(const loop&, node_array<2>& nodes) {
    nodes[0]->traverse(*this);
    auto type = aut::pop(types_stack);
    if (type == structural::type::SCALAR) {
        auto result = aut::pop(scalar_stack);
        while (result.boolean()) {
            mapper.open_scope();
            nodes[1]->traverse(*this);
            mapper.close_scope();
            if (!types_stack.empty()) {
                print_result();
            }
            nodes[0]->traverse(*this);
            aut::pop(types_stack);
            result = aut::pop(scalar_stack);
        }
    } else {
        err::semantic<Error::NON_BOOLEAN_CONDITION>();
    }
}

// void falk::ev::evaluator::analyse(const index_access&, node_array<3>& nodes) {
//     nodes[0]->traverse(*this);
//     auto type = aut::pop(types_stack);
//     switch (type) {
//         case structural::type::SCALAR:
//             err::semantic<Error::NOT_A_STRUCTURE>();
//             break;
//         case structural::type::ARRAY:
//             std::cout << "TODO: implement indexed access to arrays";
//             break;
//         case structural::type::MATRIX:
//             std::cout << "TODO: implement indexed access to matrices";
//             break;
//     }
// }

void falk::ev::evaluator::process(rvalue& v) {
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
                mapper.update_result(variable(result, type));
            }
            break;
        }
        case structural::type::ARRAY: {
            auto result = aut::pop(array_stack);
            if (!result.error()) {
                std::cout << "res = " << result << std::endl;
                mapper.update_result(variable(result, type));
            }
            break;
        }
        case structural::type::MATRIX: {
            auto result = aut::pop(matrix_stack);
            if (!result.error()) {
                std::cout << "res = " << result << std::endl;
                mapper.update_result(variable(result, type));
            }
            break;
        }
    }
}

void falk::ev::evaluator::analyse(const create_structure&,
                                  std::list<node_ptr>& nodes) {
    // TODO: solve this (problem number 666: unknown nullptr)
    auto size = nodes.size() - 1;

    for (auto& node : nodes) {
        // TODO: solve this (problem number 666: unknown nullptr)
        if (node) {
            node->traverse(*this);
        }
    }

    array arr;
    matrix m;
    auto result_type = structural::type::ARRAY;

    for (auto i = 0; i < size; i++) {
        auto type = aut::pop(types_stack);
        switch (type) {
            case structural::type::SCALAR: {
                if (i > 0 && result_type == structural::type::MATRIX) {
                    err::semantic<Error::HETEROGENEOUS_STRUCTURE>();
                    m.set_error();
                    push(m);
                    return;
                }
                auto scalar = aut::pop(scalar_stack);
                arr.push_front(scalar);
                result_type = structural::type::ARRAY;
                break;
            }
            case structural::type::ARRAY: {
                if (i > 0 && result_type == structural::type::ARRAY) {
                    err::semantic<Error::HETEROGENEOUS_STRUCTURE>();
                    arr.set_error();
                    push(arr);
                    return;
                }
                auto a = aut::pop(array_stack);
                m.push_front(a);
                result_type = structural::type::MATRIX;
                break;
            }
            case structural::type::MATRIX:
                err::semantic<Error::TOO_MANY_DIMENSIONS>();
                m.set_error();
                push(m);
                return;
        }
    }

    if (result_type == structural::type::MATRIX) {
        push(m);
    } else {
        push(arr);
    }
}
