#include "Action.hpp"

std::string Operation::to_string() const {
    std::string result;
    result += static_cast<char>(op);
    for (auto child : children) {
        result += " ";
        result += child->to_string();
    }
    return result;
}
