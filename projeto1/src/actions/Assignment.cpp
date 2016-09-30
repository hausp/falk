#include "Action.hpp"

Assignment::Assignment(Action* var, Action* action)
 : var(var), rhs(action), fail(var->error() || rhs->error()) {
    auto var_type = var->type();
    auto rhs_type = rhs->type();

    if (utils::can_coerce(var_type, rhs_type)) {
        rhs = new Cast(var_type, rhs);
        rhs_type = var_type;
    }

    if (!fail && !utils::type_matches(var_type, rhs_type)) {
        utils::semantic_error<Error::INCOMPATIBLE_ASSIGNMENT>(var_type, rhs_type);
        fail = true;
    }
}

std::string Assignment::to_string(unsigned indent) const {
    std::string result;
    if (!fail) {
        result += std::string(indent, ' ');
        result += "= ";
        result += var->to_string() + " ";
        result += rhs->to_string();
    }
    return result;
}

Type Assignment::type() const {
    return var->type();
}
