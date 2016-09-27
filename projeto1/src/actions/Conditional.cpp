#include "Action.hpp"

Conditional::Conditional(Action* cond,
                         Action* accepted,
                         Action* rejected)
 : accepted(accepted), rejected(rejected) {
    auto type = cond->type();
    if (type != Type::BOOL) {
        utils::semantic_error<Error::INCOMPATIBLE_TEST>(type);
        invalid = true;
    } else {
        condition = cond;
    }
 }

std::string Conditional::to_string(unsigned indent) const {
    std::string spaces(indent, ' ');
    std::string out = spaces;
    out += "if: " + condition->to_string();
    out += "\n" + spaces + "then:\n";
    out += accepted->to_string(indent + 2);
    if (rejected) {
        out += "\n" + spaces + "else:\n";
        out += rejected->to_string(indent + 2);
    }
    return out;
}