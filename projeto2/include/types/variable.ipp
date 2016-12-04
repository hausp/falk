
inline falk::variable::variable(falk::type t):
  data{scalar(t)} {}

inline falk::variable::variable(bool flag):
  data{scalar(falk::type())}, fail{flag} {
    value<scalar>().set_error();
}

template<typename T>
falk::variable::variable(const T& value):
  data{value}, type{value.type()}, fail{value.error()} { }

template<typename T>
falk::variable::variable(const T& value, structural::type t):
  data{value}, type{t}, fail{value.error()} { }

inline falk::structural::type falk::variable::stored_type() const {
    return type;
}

template<typename T>
T& falk::variable::value() {
    return data.value<T>();
}

template<typename T>
const T& falk::variable::value() const {
    return data.value<T>();
}

inline bool falk::variable::error() const {
    return fail;
}

template<typename Type, Type OP, typename T>
falk::variable& falk::variable::op(op::callback<Type, OP, 2> op,
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
    }

    return *this;
}

template<typename T>
falk::variable& falk::variable::pow(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::POW, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::operator+=(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::ADD, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::operator-=(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::SUB, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::operator*=(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::MULT, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::operator/=(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::DIV, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::operator%=(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::MOD, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::operator&=(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::AND, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::operator|=(const T& rhs) {
    return op(op::callback<op::assignment, op::assignment::OR, 2>(), rhs);
}

template<typename T>
falk::variable& falk::variable::assign(const T& rhs) {
    return op(op::callback<op::assignment,op::assignment::DIRECT, 2>(), rhs);
}

inline std::ostream& falk::operator<<(std::ostream& out, const variable& v) {
    switch (v.stored_type()) {
        case falk::structural::type::SCALAR: {
            auto& raw = v.value<scalar>();
            out << raw;
            break;
        }
        case falk::structural::type::ARRAY: {
            auto& raw = v.value<array>();
            out << raw;
            break;
        }
        case falk::structural::type::MATRIX: {
            auto& raw = v.value<matrix>();
            out << raw;
            break;
        }
    }
    return out;
}
