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
    for (auto child : children) {
        result += " ";
        result += child->to_string();
    }
    return result;
}

std::string Operation::op_string() const {
	return std::string(1, static_cast<char>(op));
}
