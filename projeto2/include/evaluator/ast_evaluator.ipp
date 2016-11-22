template<typename T>
void falk::ev::ast_evaluator::calc(std::array<node_ptr, 2>& operands, T callback) {
    for (auto& op : operands) {
        op->traverse(*this);
    }

    auto t1 = aut::pop(types_stacker);
    auto t2 = aut::pop(types_stacker);

    if (t1 == t2) {
        switch (t1) {
            case structural::type::VARIABLE: {
                auto rhs = aut::pop(var_stacker);
                auto lhs = aut::pop(var_stacker);
                auto result = callback(lhs, rhs);
                var_stacker.push(result);
                types_stacker.push(structural::type::VARIABLE);
                break;
            }
            case structural::type::ARRAY: {
                auto rhs = aut::pop(array_stacker);
                auto lhs = aut::pop(array_stacker);
                auto result = callback(lhs, rhs);
                array_stacker.push(result);
                types_stacker.push(structural::type::ARRAY);
                break;
            }
            case structural::type::MATRIX: {
                auto rhs = aut::pop(matrix_stacker);
                auto lhs = aut::pop(matrix_stacker);
                auto result = callback(lhs, rhs);
                matrix_stacker.push(result);
                types_stacker.push(structural::type::MATRIX);
                break;
            }
        }
    }
}

template<typename T>
void falk::ev::ast_evaluator::calc_assign(std::array<node_ptr, 2>& operands, T callback) {
    for (auto& op : operands) {
        op->traverse(*this);
    }

    auto t1 = aut::pop(types_stacker);
    auto t2 = aut::pop(types_stacker);

    if (t1 == t2) {
        switch (t1) {
            case structural::type::VARIABLE: {
                auto rhs = aut::pop(var_stacker);
                auto lhs = aut::pop(var_stacker);
                auto result = callback(lhs, rhs);
                // TODO
                break;
            }
            case structural::type::ARRAY: {
                auto rhs = aut::pop(array_stacker);
                auto lhs = aut::pop(array_stacker);
                auto result = callback(lhs, rhs);
                // TODO
                break;
            }
            case structural::type::MATRIX: {
                auto rhs = aut::pop(matrix_stacker);
                auto lhs = aut::pop(matrix_stacker);
                auto result = callback(lhs, rhs);
                // TODO
                break;
            }
        }
    }
}

inline falk::ev::ast_evaluator::real
falk::ev::ast_evaluator::make_real(const std::string& text) {
    return std::stod(text);
}

inline falk::ev::ast_evaluator::complex
falk::ev::ast_evaluator::make_complex(const std::string& text) {
    auto clean_text = text.substr(0, text.size() - 2);
    return std::complex<double>{0, std::stod(text)};
}

inline falk::ev::ast_evaluator::boolean
falk::ev::ast_evaluator::make_boolean(const std::string& text) {
    return text == "true";
}

inline int falk::ev::ast_evaluator::new_line() {
    std::cout << "falk> ";
    return 0;
}

inline falk::ev::ast_evaluator::rvalue&
falk::ev::ast_evaluator::single_calculation(rvalue& value) {
    if (!value.empty()) {
        value.traverse(*this);
        auto type = aut::pop(types_stacker);
        switch (type) {
            case structural::type::VARIABLE: {
                auto v = aut::pop(var_stacker);
                std::cout << "res = " << v << std::endl;
                break;
            }
            case structural::type::ARRAY: {
                auto v = aut::pop(array_stacker);
                // std::cout << "res = " << v << std::endl;
                break;
            }
            case structural::type::MATRIX: {
                auto v = aut::pop(matrix_stacker);
                // std::cout << "res = " << v << std::endl;
                break;
            }
        }
    }
    return value;
}
