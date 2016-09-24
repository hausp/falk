#include "Action.hpp"

Variable::Variable(const std::string& name)
 : fail(!symbols.var_exists(name)), name(name) {
    if (error()) {
        utils::semantic_error<Error::UNDECLARED_VARIABLE>(name);
    } else {
        t = symbols.typeof(name);
    }
}

bool Variable::error() const {
    return fail;
}

Type Variable::type() const {
    return t;
}

std::string Variable::to_string() const {
    return name;
}
