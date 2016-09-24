#include "Action.hpp"

Variable::Variable(const std::string& name)
 : fail(!symbols.var_exists(name)), name(name) {
    if (error()) {
        utils::semantic_error<Error::UNDECLARED_VARIABLE>(name);
    }
}

bool Variable::error() const {
    return fail;
}

Type Variable::type() const {
    return Type::INT;
}

std::string Variable::to_string() const {
    return name;
}
