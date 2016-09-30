#include "Action.hpp"

Declaration::Declaration(Type type) : t(type) {}

void Declaration::add(const std::string& name) {
    if (symbols.declare(type(), name)) {
        values.push_back({name, nullptr});
    }
}

void Declaration::add(const std::string& name, Action* value) {
    if (utils::can_coerce(type(), value->type())) {
        value = new Cast(type(), value);
    }

    if (symbols.declare(type(), name, *value)) {
        values.push_back({name, value});
    }
}

std::string Declaration::to_string(unsigned indent) const {
    std::string result;
    if (values.empty()) {
        return result;
    }
    result += std::string(indent, ' ');
    result += utils::to_string(type()) + " var: ";
    size_t i = 0;
    for (auto& pair : values) {
        if (i > 0) {
            result += ", ";
        }
        result += pair.first;
        if (pair.second != nullptr) {
            result += " = " + pair.second->to_string();
        }
        ++i;
    }
    return result;
}
