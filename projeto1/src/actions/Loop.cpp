#include "Action.hpp"

Loop::Loop(Action* init, Action* bool_expr, Action* update, Action* code)
 : init(init), update(update), code(code) {

	fail = fail || (init != nullptr && init->error());
	fail = fail || (bool_expr != nullptr && bool_expr->error());
	fail = fail || (update != nullptr && update->error());
    auto test_type = bool_expr->type();
    if (test_type != PrimitiveType::BOOL) {
        utils::semantic_error<Error::INCOMPATIBLE_TEST>(test_type);
        fail = true;
    } else {
        test = bool_expr;
    }
}

std::string Loop::to_string(unsigned indent) const {
    std::string out;
    if (!error()) {
        std::string spaces(indent, ' ');
        out += spaces;
        out += "for: ";
        if (init != nullptr) out += init->to_string();
        out += ", ";
        if (test != nullptr) out += test->to_string();
        out += ", ";
        if (update != nullptr) out += update->to_string();
        out += "\n" + spaces + "do:\n";
        out += code->to_string(indent + 2);
    }
    return out;
}
