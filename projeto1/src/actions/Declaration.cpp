#include "Action.hpp"

Declaration::Declaration(Type type) : type(type) {}

void Declaration::add(const std::string& name) {
    if (symbols.declare(type, name)) {
        values.push_back({name, ""});
    }
}

void Declaration::add(const std::string& name, Action* value) {
    auto val = dynamic_cast<TypedAction*>(value);
    if (symbols.declare(type, name, *val)) {
        values.push_back({name, value->to_string()});
    }
}

std::string Declaration::to_string() const {
    std::string result;
    if (values.empty()) {
        return result;
    }
    result = utils::to_string(type) + " var: ";
    size_t i = 0;
    for (auto& pair : values) {
        if (i > 0) {
            result += ", ";
        }
        result += pair.first;
        if (!pair.second.empty()) {
            result += " = " + pair.second;
        }
        ++i;
    }
    return result;
}
