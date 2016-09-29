#include "Action.hpp"

Return::Return(Action* operand) : operand(operand), fail(operand->error()) {

}

std::string Return::to_string(unsigned) const {
    std::string result;
    if (!error()) {
        result += "ret " + operand->to_string();
    }
    return result;
}

Type Return::type() const {
    return operand->type();
}
