#include "Action.hpp"

std::string ParamList::to_string(unsigned) const {
    std::string out;
    auto first = true;
    for (auto& action : vars) {
        if (first) {
            first = false;
        } else {
            out += ",";
        }
        out += utils::to_string(action->type());
        out += " " + action->to_string();
    }
    return out;
}
