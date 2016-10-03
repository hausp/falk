#include "Action.hpp"

bool Operation::error() const {
    return fail;
}

Type Operation::type() const {
    return t;
}

std::string Operation::to_string(unsigned) const {
    std::string result;
    if (!error()) {
        result += op_string();
        bool space = false;
        for (auto child : children) {
            if (space || !result.empty()) {
                result += " ";
            }
            result += child->to_string();
            space = true;
        }
    }
    return result;
}

std::string Operation::op_string() const {
    return utils::to_string(op);
}

void Operation::set_type(Type type) {
    t = type;
}

void Operation::check(Action* action) {
    auto expected = t;
    auto actual = action->type();
    bool can_coerce = false;
    if (action->type().ptr_count > 0) {
        fail = true;
        utils::semantic_error<Error::TYPE_ERROR>();
    }

    if (expected == PrimitiveType::INT && actual == PrimitiveType::FLOAT) {
        t = PrimitiveType::FLOAT;
        expected = t;
        can_coerce = true;
    } else if (expected == PrimitiveType::FLOAT && actual == PrimitiveType::INT) {
        can_coerce = true;
    }
    needs_coercion = needs_coercion || can_coerce;
    if (!utils::type_matches(expected, actual) && !can_coerce) {
        utils::semantic_error<Error::INCOMPATIBLE_OPERANDS>(op, expected, actual);
        fail = true;
    }
}

void Operation::set_children() {
    if (needs_coercion) {
        for (auto& child : children) {
            if (child->type() == PrimitiveType::INT) {
                child = new Cast(PrimitiveType::FLOAT, child);
            }
        }
    }
}
