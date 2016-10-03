#include "Action.hpp"

Declaration::Declaration(Type type, const std::string& symbol_type)
: t(type), symbol_type(symbol_type) {}

void Declaration::add(const std::string& name) {
    if (symbols.declare(type(), name)) {
        auto decl = new VarDecl(type(), name);
        declarations.push_back(decl);
    }
}

void Declaration::add(const std::string& name, Action* value) {
    if (utils::can_coerce(type(), value->type())) {
        value = new Cast(type(), value);
    }

    if (symbols.declare(type(), name, *value)) {
        auto decl = new VarDecl(type(), name, value);
        declarations.push_back(decl);
    }
}

void Declaration::add(const std::string& name, const utils::literal& literal) {
    if (symbols.declare_array(type(), name, literal.value)) {
        auto decl = new ArrayDecl(type(), name, literal.value);
        declarations.push_back(decl);
    }
}

std::string Declaration::to_string(unsigned indent) const {
    std::string result;
    if (declarations.empty()) {
        return result;
    }
    result += std::string(indent, ' ');
    result += utils::to_string(type());
    result += " " + symbol_type + ": ";
    size_t i = 0;
    for (auto& decl : declarations) {
        if (i > 0) {
            result += ", ";
        }
        result += decl->to_string();
        ++i;
    }
    return result;
}
