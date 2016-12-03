template<typename Type, Type OP>
void falk::ev::evaluator::analyse(op::callback<Type, OP, 2> op,
                                  node_array<2>& nodes) {
    for (auto& node : nodes) {
        node->traverse(*this);
    }
    auto t1 = aut::pop(types_stack);
    auto t2 = aut::pop(types_stack);

    switch (t2) {
        case structural::type::SCALAR:
            handle_operation(op, t1, scalar_stack);
            break;
        case structural::type::ARRAY:
            handle_operation(op, t1, array_stack);
            break;
        case structural::type::MATRIX:
            handle_operation(op, t1, matrix_stack);
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
void falk::ev::evaluator::analyse(op::callback<Type, OP, 1> op,
                                  node_array<1>& nodes) {
    nodes[0]->traverse(*this);

    auto t1 = aut::pop(types_stack);
    switch (t1) {
        case structural::type::SCALAR:
            push(op(aut::pop(scalar_stack)));
            break;
        case structural::type::ARRAY:
            push(op(aut::pop(array_stack)));
            break;
        case structural::type::MATRIX:
            push(op(aut::pop(matrix_stack)));
            break;
    }
}

template<falk::op::assignment OP>
void falk::ev::evaluator::analyse(op::callback<op::assignment, OP, 2> op,
                                  node_array<2>& nodes) {
    for (auto& node : nodes) {
        node->traverse(*this);
    }
    auto t1 = aut::pop(types_stack);
    switch (t1) {
        case structural::type::SCALAR: {
            auto rhs = aut::pop(scalar_stack);
            auto& var = mapper.retrieve_variable(aut::pop(id_stack).id);
            op(var, rhs);
            break;
        }
        case structural::type::ARRAY: {
            auto rhs = aut::pop(array_stack);
            auto& var = mapper.retrieve_variable(aut::pop(id_stack).id);
            op(var, rhs);
            break;
        }
        case structural::type::MATRIX: {
            auto rhs = aut::pop(matrix_stack);
            auto& var = mapper.retrieve_variable(aut::pop(id_stack).id);
            op(var, rhs);
            break;
        }
    }
}

template<typename T>
void falk::ev::evaluator::analyse(const T& object) {
    push(object);
}

inline void falk::ev::evaluator::push(const scalar& data) {
    scalar_stack.push(data);
    types_stack.push(structural::type::SCALAR);
}

inline void falk::ev::evaluator::push(const array& data) {
    array_stack.push(data);
    types_stack.push(structural::type::ARRAY);
}

inline void falk::ev::evaluator::push(const matrix& data) {
    matrix_stack.push(data);
    types_stack.push(structural::type::MATRIX);
}

inline void falk::ev::evaluator::push(const var_id& data) {
    id_stack.push(data);
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
