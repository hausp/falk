#include "base/errors.hpp"
#include "base/evaluator.hpp"

void falk::evaluator::analyse(const declare_variable& var,
                                  node_array<1>& nodes) {
    auto get_value = [this](auto& mapper, auto& var) {
        auto type = aut::pop(types_stack);
        if (!var.deduce_type && type != var.s_type) {
            err::semantic<Error::ILLEGAL_ASSIGNMENT>(var.s_type, type);
            return;
        }

        switch (type) {
            case structural::type::SCALAR: {
                auto result = aut::pop(scalar_stack);
                if (!result.error()) {
                    mapper.declare_variable(var.id, variable(result));
                }
                break;
            }
            case structural::type::ARRAY: {
                auto result = aut::pop(array_stack);
                if (!result.error()) {
                    mapper.declare_variable(var.id, variable(result));
                }
                break;
            }
            case structural::type::MATRIX: {
                auto result = aut::pop(matrix_stack);
                if (!result.error()) {
                    mapper.declare_variable(var.id, variable(result));
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

void falk::evaluator::analyse(const declare_function& fn,
                                  node_array<1>& nodes) {
    auto& id = fn.id;
    auto& params = fn.params;

    mapper.declare_function(id, {params, nodes[0]});
}

void falk::evaluator::analyse(var_id& vid, node_array<2>& index) {
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

void falk::evaluator::analyse(fun_id& fun, node_array<1>& nodes) {
    auto& fn = mapper.retrieve_function(fun.id);
    auto& params = fn.params();
    if (!fn.error() && params.size() == fun.number_of_params) {
        nodes[0]->traverse(*this);
        mapper.open_scope();
        bool error = false;
        for (int i = fun.number_of_params - 1; i >= 0; i--) {
            auto t = aut::pop(types_stack);
            if (params[i].s_type != t) {
                err::semantic<Error::MISMATCHING_PARAMETER>(
                    fun.id, params[i].vid.id, params[i].s_type, t
                );
                error = true;
            }
            switch (t) {
                case structural::type::SCALAR: {
                    auto v = aut::pop(scalar_stack);
                    mapper.declare_variable(params[i].vid.id, variable(v));
                    break;
                }
                case structural::type::ARRAY: {
                    auto v = aut::pop(array_stack);
                    auto expected_size = params[i].vid.index.first;
                    if (expected_size != -1 && v.size() != expected_size) {
                        err::semantic<Error::PARAMETER_ARRAY_SIZE_MISMATCH>(
                            fun.id, params[i].vid.id, expected_size, v.size()
                        );
                        error = true;
                        break;
                    }
                    mapper.declare_variable(params[i].vid.id, variable(v));
                    break;
                }
                case structural::type::MATRIX: {
                    auto v = aut::pop(matrix_stack);
                    auto expected_rows = params[i].vid.index.first;
                    auto expected_columns = params[i].vid.index.second;
                    bool row_mismatch = expected_rows != -1
                                     && v.row_count() != expected_rows;
                    bool column_mismatch = expected_columns != -1
                                        && v.column_count() != expected_columns;
                    if (row_mismatch || column_mismatch) {
                        err::semantic<Error::PARAMETER_MATRIX_SIZE_MISMATCH>(
                            fun.id, params[i].vid.id,
                            expected_rows, expected_columns,
                            v.row_count(), v.column_count()
                        );
                        error = true;
                        break;
                    }
                    mapper.declare_variable(params[i].vid.id, variable(v));
                    break;
                }
            }
        }

        if (!error) {
            auto& code = fn.code();
            ++function_counter;
            code->traverse(*this);
            --function_counter;

            if (!return_called) {
                push(scalar::silent());
            }
        } else {
            push(scalar::invalid());
        }
        return_called = false;
        mapper.close_scope();
    } else if (fn.error()) {
        push(scalar::invalid());
    } else {
        err::semantic<Error::MISMATCHING_PARAMETER_COUNT>(
            fun.id, params.size(), fun.number_of_params
        );
        push(scalar::invalid());
    }
}

void falk::evaluator::analyse(const print& p, node_array<1>& nodes) {
    nodes[0]->traverse(*this);
    auto type = aut::pop(types_stack);
    switch (type) {
        case structural::type::SCALAR: {
            auto result = aut::pop(scalar_stack);
            if (!result.error())
                mapper.update_result(p(result));
            break;
        }
        case structural::type::ARRAY: {
            auto result = aut::pop(array_stack);
            if (!result.error())
                mapper.update_result(p(result));
            break;
        }
        case structural::type::MATRIX: {
            auto result = aut::pop(matrix_stack);
            if (!result.error())
                mapper.update_result(p(result));
            break;
        }
    }
}

void falk::evaluator::analyse(const scoped&, node_array<1>& nodes) {
    mapper.open_scope();
    nodes[0]->traverse(*this);
    mapper.close_scope();
}

void falk::evaluator::analyse(const valueof&, node_array<1>& nodes) {
    nodes[0]->traverse(*this);
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

void falk::evaluator::analyse(const typeof&, node_array<1>& nodes) {
    // std::cout << "hello" << std::endl;
    nodes[0]->traverse(*this);

    if(aut::pop(types_stack) != structural::type::SCALAR) {
        // TODO: usuário burro toma erro na cara
    }
    
    auto value = aut::pop(scalar_stack);
    auto type = value.inner_type();

    push(scalar(type));
    // std::cout << "darkness" << std::endl;
}

void falk::evaluator::analyse(const block&, std::list<node_ptr>& nodes) {
    for (auto& node : nodes) {
        node->traverse(*this);
        if (return_called) {
            break;
        }
    }
}

void falk::evaluator::analyse(const conditional&, node_array<3>& nodes) {
    nodes[0]->traverse(*this);
    auto type = aut::pop(types_stack);
    if (type == structural::type::SCALAR) {
        auto result = aut::pop(scalar_stack);
        // mapper.open_scope();
        if (result.boolean()) {
            nodes[1]->traverse(*this);
        } else {
            nodes[2]->traverse(*this);
        }
        // mapper.close_scope();
    } else {
        err::semantic<Error::NON_BOOLEAN_CONDITION>();
    }
}

void falk::evaluator::analyse(const loop&, node_array<2>& nodes) {
    nodes[0]->traverse(*this);
    auto type = aut::pop(types_stack);
    if (type == structural::type::SCALAR) {
        auto result = aut::pop(scalar_stack);
        while (result.boolean() && !return_called) {
            // mapper.open_scope();
            nodes[1]->traverse(*this);
            // mapper.close_scope();
            nodes[0]->traverse(*this);
            aut::pop(types_stack);
            result = aut::pop(scalar_stack);
        }
    } else {
        err::semantic<Error::NON_BOOLEAN_CONDITION>();
    }
}

void falk::evaluator::analyse(const for_it& fit, node_array<2>& nodes) {
    nodes[0]->traverse(*this);
    auto vid = aut::pop(id_stack);
    auto& var = mapper.retrieve_variable(vid.id);
    
    switch (var.stored_type()) {
        case structural::type::SCALAR: {
            // TODO: usuário burro bostão morra
            break;
        }
        case structural::type::ARRAY: {
            for (auto& element : var.value<array>()) {
                mapper.open_scope();
                mapper.declare_variable(fit.var_name, variable(element));
                nodes[1]->traverse(*this);
                mapper.close_scope();
            }
            break;
        }
        case structural::type::MATRIX: {
            auto& banana = var.value<matrix>();
            for (size_t i = 0; i < banana.row_count(); i++) {
                auto row = banana.row(i);
                mapper.open_scope();
                mapper.declare_variable(fit.var_name, variable(row));
                nodes[1]->traverse(*this);
                mapper.close_scope();
            }
            break;
        }
    }
}

void falk::evaluator::analyse(const ret&, node_array<1>& nodes) {
    if (function_counter > 0) {
        nodes[0]->traverse(*this);
        return_called = true;
    } else {
        // TODO: error or kill the program (Assigned to Ghabriel)
    }
}

void falk::evaluator::analyse(const undef& container) {
    mapper.undefine_function(container.id);
}

void falk::evaluator::process(node_ptr v) {
    if (!v->empty()) {
        v->traverse(*this);
    }
}

void falk::evaluator::analyse(const create_structure&,
                              std::list<node_ptr>& nodes) {
    auto size = nodes.size();
    for (auto& node : nodes) {
        node->traverse(*this);
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
