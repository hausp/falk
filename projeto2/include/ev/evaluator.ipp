template<typename Type, Type OP>
void falk::ev::evaluator::analyse(operation<Type, OP, 2, false> op,
                                  node_array<2>& nodes) {
    for (auto& node : nodes) {
        node->traverse(*this);
    }

    auto t1 = aut::pop(types_stack);
    auto t2 = aut::pop(types_stack);

    switch (t1) {
        case structural::type::SCALAR:
            handle_operation(op, t2, scalar_stack);
            break;
        case structural::type::ARRAY:
            handle_operation(op, t2, array_stack);
            break;
        case structural::type::MATRIX:
            handle_operation(op, t2, matrix_stack);
            break;
    }
}

template<typename Operation, typename Stack>
void falk::ev::evaluator::handle_operation(const Operation& op,
                                           structural::type rhs_type,
                                           Stack& stack) {
    switch (rhs_type) {
        case structural::type::SCALAR: {
            auto rhs = aut::pop(scalar_stack);
            auto lhs = aut::pop(stack);
            push(op(lhs, rhs));
            break;
        }
        case structural::type::ARRAY: {
            auto rhs = aut::pop(array_stack);
            auto lhs = aut::pop(stack);
            push(op(lhs, rhs));
            break;
        }
        case structural::type::MATRIX: {
            auto rhs = aut::pop(matrix_stack);
            auto lhs = aut::pop(stack);
            push(op(lhs, rhs));
            break;
        }
    }
}

template<typename Type, Type OP>
void falk::ev::evaluator::analyse(operation<Type, OP, 1, false> op,
                                  node_array<1>& nodes) {
    nodes[0]->traverse(*this);

    auto t1 = aut::pop(types_stack);

    switch (t1) {
        case structural::type::SCALAR: {
            auto lhs = aut::pop(scalar_stack);
            auto result = op(lhs);
            scalar_stack.push(result);
            types_stack.push(structural::type::SCALAR);
            break;
        }
        case structural::type::ARRAY: {
            auto lhs = aut::pop(array_stack);
            auto result = op(lhs);
            array_stack.push(result);
            types_stack.push(structural::type::ARRAY);
            break;
        }
        case structural::type::MATRIX: {
            auto lhs = aut::pop(matrix_stack);
            auto result = op(lhs);
            matrix_stack.push(result);
            types_stack.push(structural::type::MATRIX);
            break;
        }
    }
}

template<typename Type, Type OP>
void falk::ev::evaluator::analyse(operation<Type, OP, 2, true> op,
                                  node_array<2>& nodes) {
    for (auto& node : nodes) {
        node->traverse(*this);
    }

    auto t1 = aut::pop(types_stack);
    auto t2 = aut::pop(types_stack);

    if (t1 == t2) {
        switch (t1) {
            case structural::type::SCALAR: {
                auto rhs = aut::pop(scalar_stack);
                auto id = aut::pop(id_stack);
                auto& var = mapper.retrieve_variable(id.name);
                op(var, rhs);
                break;
            }
            case structural::type::ARRAY: {
                auto rhs = aut::pop(array_stack);
                auto id = aut::pop(id_stack);
                auto& var = mapper.retrieve_variable(id.name);
                op(var, rhs);
                break;
            }
            case structural::type::MATRIX: {
                auto rhs = aut::pop(matrix_stack);
                auto id = aut::pop(id_stack);
                auto& var = mapper.retrieve_variable(id.name);
                op(var, rhs);
                break;
            }
        }
    }
}

inline void falk::ev::evaluator::analyse(const identifier& id) {
    id_stack.push(id);
}

inline void falk::ev::evaluator::initialize() {
    std::cout << "falk> ";
}

inline falk::ev::evaluator::real
falk::ev::evaluator::make_real(const std::string& text) {
    return std::stod(text);
}

inline falk::ev::evaluator::complex
falk::ev::evaluator::make_complex(const std::string& text) {
    auto clean_text = text.substr(0, text.size() - 2);
    return std::complex<double>{0, std::stod(text)};
}

inline falk::ev::evaluator::boolean
falk::ev::evaluator::make_boolean(const std::string& text) {
    return text == "true";
}

inline void falk::ev::evaluator::prompt() {
    std::cout << "falk> ";
}
