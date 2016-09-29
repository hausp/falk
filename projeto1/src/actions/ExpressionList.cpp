#include "Action.hpp"

void ExpressionList::add(Action* expr) {
    expressions.push_back(expr);
    fail = fail || expr->error();
}

std::string ExpressionList::to_string(unsigned) const {
    std::string result;
    if (!error()) {
        bool comma = false;
        for (auto& expr : expressions) {
            if (comma) {
                result += ", ";
            }
            result += utils::to_string(expr->type());
            result += " ";
            result += expr->to_string();
            comma = true;
        }
    }
    return result;
}
