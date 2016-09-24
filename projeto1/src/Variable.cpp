#include "Action.hpp"

Variable::Variable(const std::string& name) : name(name) {
    if (error()) {
        utils::semantic_error<Error::UNDECLARED_VARIABLE>(0, name);
    }
}

bool Variable::error() const {
    return !symbols.var_exists(name);
}

Type Variable::type() const {
    return Type::INT;
}

std::string Variable::to_string() const {
    return name;
}
