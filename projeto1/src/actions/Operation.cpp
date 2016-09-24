#include "Action.hpp"

bool Operation::error() const {
	return fail;
}

Type Operation::type() const {
	return t;
}

std::string Operation::to_string() const {
    std::string result;
    result += op_string();
    bool space = false;
    for (auto child : children) {
        if (space || !result.empty()) {
            result += " ";
        }
        result += child->to_string();
        space = true;
    }
    return result;
}

std::string Operation::op_string() const {
	return utils::to_string(op);
}

void Operation::set_error() {
    fail = true;
}
