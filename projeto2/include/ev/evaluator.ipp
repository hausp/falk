template<typename Type, Type OP>
void falk::ev::evaluator::analyse(operation<Type, OP, 2, false> op,
                                  node_array<2>& nodes) {
    for (auto& node : nodes) {
        node->traverse(*this);
    }

    auto t1 = aut::pop(types_stacker);
    auto t2 = aut::pop(types_stacker);

    switch (t1) {
        case structural::type::SCALAR:
            handle_operation(op, t2, var_stacker);
            break;
        case structural::type::ARRAY:
            handle_operation(op, t2, array_stacker);
            break;
        case structural::type::MATRIX:
            handle_operation(op, t2, matrix_stacker);
            break;
    }
}

template<typename Operation, typename Stack>
void falk::ev::evaluator::handle_operation(const Operation& op,
                                           structural::type rhs_type,
                                           Stack& stack) {
    switch (rhs_type) {
        case structural::type::SCALAR: {
            auto rhs = aut::pop(var_stacker);
            auto lhs = aut::pop(stack);
            push(op(lhs, rhs));
            break;
        }
        case structural::type::ARRAY: {
            auto rhs = aut::pop(array_stacker);
            auto lhs = aut::pop(stack);
            push(op(lhs, rhs));
            break;
        }
        case structural::type::MATRIX: {
            auto rhs = aut::pop(matrix_stacker);
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

    auto t1 = aut::pop(types_stacker);

    switch (t1) {
        case structural::type::SCALAR: {
            auto lhs = aut::pop(var_stacker);
            auto result = op(lhs);
            var_stacker.push(result);
            types_stacker.push(structural::type::SCALAR);
            break;
        }
        case structural::type::ARRAY: {
            auto lhs = aut::pop(array_stacker);
            auto result = op(lhs);
            array_stacker.push(result);
            types_stacker.push(structural::type::ARRAY);
            break;
        }
        case structural::type::MATRIX: {
            auto lhs = aut::pop(matrix_stacker);
            auto result = op(lhs);
            matrix_stacker.push(result);
            types_stacker.push(structural::type::MATRIX);
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

    auto t1 = aut::pop(types_stacker);
    auto t2 = aut::pop(types_stacker);

    if (t1 == t2) {
        switch (t1) {
            case structural::type::SCALAR: {
                auto rhs = aut::pop(var_stacker);
                auto lhs = aut::pop(var_stacker);
                auto result = op(lhs, rhs);
                (void)result;
                // TODO
                break;
            }
            case structural::type::ARRAY: {
                auto rhs = aut::pop(array_stacker);
                auto lhs = aut::pop(array_stacker);
                auto result = op(lhs, rhs);
                (void)result;
                // TODO
                break;
            }
            case structural::type::MATRIX: {
                auto rhs = aut::pop(matrix_stacker);
                auto lhs = aut::pop(matrix_stacker);
                auto result = op(lhs, rhs);
                (void)result;
                // TODO
                break;
            }
        }
    }
}

inline falk::ev::evaluator::list falk::ev::evaluator::make_program() {
    std::cout << "falk> ";
    return {};
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

inline int falk::ev::evaluator::new_line() {
    std::cout << "falk> ";
    return 0;
}
