
inline falk::ev::variable::variable(falk::type t): data{scalar(t)} {}

template<typename T>
falk::ev::variable::variable(const T& value): data{value} { }

template<typename Type, Type OP, typename T>
falk::ev::variable& falk::ev::variable::op(operation<Type, OP, 2, true> op,
                                           const T& v) {
    switch (type) {
        case falk::structural::type::SCALAR: {
            auto& raw = data.value<scalar>();
            op(raw, v);
            break;
        }
        case falk::structural::type::ARRAY: {
            auto& raw = data.value<array>();
            op(raw, v);
            break;
        }
        case falk::structural::type::MATRIX: {
            auto& raw = data.value<matrix>();
            op(raw, v);
            break;
        }
        default:;
    }

    return *this;
}

template<typename T>
falk::ev::variable& falk::ev::variable::pow(const T& rhs) {
    return op(falk::op::POW_ASSIGN(), rhs);
}

template<typename T>
falk::ev::variable& falk::ev::variable::operator+=(const T& rhs) {
    std::cout << "little hell" << std::endl;
    return op(falk::op::ADD_ASSIGN(), rhs);
}

template<typename T>
falk::ev::variable& falk::ev::variable::operator-=(const T& rhs) {
    return op(falk::op::SUB_ASSIGN(), rhs);
}

template<typename T>
falk::ev::variable& falk::ev::variable::operator*=(const T& rhs) {
    return op(falk::op::MULT_ASSIGN(), rhs);
}

template<typename T>
falk::ev::variable& falk::ev::variable::operator/=(const T& rhs) {
    return op(falk::op::DIV_ASSIGN(), rhs);
}

template<typename T>
falk::ev::variable& falk::ev::variable::operator%=(const T& rhs) {
            return op(falk::op::MOD_ASSIGN(), rhs);
}

template<typename T>
falk::ev::variable& falk::ev::variable::operator&=(const T& rhs) {
    // TODO
    // return op(falk::op::AND_ASSIGN(), rhs);
}

template<typename T>
falk::ev::variable& falk::ev::variable::operator|=(const T& rhs) {
    // TODO
    // return op(falk::op::OR_ASSIGN(), rhs);
}
