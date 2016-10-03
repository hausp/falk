#include "macros.hpp"
#include "Action.hpp"

Conditional::Conditional(Action* cond,
                         Action* accepted,
                         Action* rejected)
 : accepted(accepted), rejected(rejected), fail(cond->error()) {
    auto type = cond->type();
    if (type != PrimitiveType::BOOL) {
        utils::semantic_error<Error::INCOMPATIBLE_TEST>(type);
        fail = true;
    } else {
        condition = cond;
    }
 }

std::string Conditional::to_string(unsigned indent) const {
    std::string out;
    if (!error()) {
        std::string spaces(indent, ' ');
        out += spaces;
        out += "if: " + condition->to_string();
        out += "\n" + spaces + "then:\n";
        out += accepted->to_string(indent + 2);
        if (rejected) {
            out += "\n" + spaces + "else:\n";
            out += rejected->to_string(indent + 2);
        }
    }
    return out;
}