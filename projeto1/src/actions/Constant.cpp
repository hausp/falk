#include "Action.hpp"

Constant::Constant(Type type, const std::string& value) : t(type), value(value) {}

bool Constant::error() const {
    return false;
}

Type Constant::type() const {
    return t;
}

std::string Constant::to_string(unsigned) const {
    return value;
}
