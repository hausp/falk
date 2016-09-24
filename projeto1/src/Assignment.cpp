#include "Action.hpp"

Assignment::Assignment(Variable* var, Action* rhs) : var(var), rhs(rhs) {}

std::string Assignment::to_string() const {
    std::string result;
    auto typedExpr = dynamic_cast<TypedAction*>(rhs);
    if (!var->error() && !typedExpr->error()) {
        result += "= ";
        result += var->to_string() + " ";
        result += rhs->to_string();
    }
    return result;
}
