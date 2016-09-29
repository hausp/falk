#include "Action.hpp"

void ParamList::add(Type type, const std::string& var) {
    vars.emplace_back(type, var);
}

std::string ParamList::to_string(unsigned) const {
    std::string out;
    auto first = true;
    for (auto& action : vars) {
        if (first) {
            first = false;
        } else {
            out += ",";
        }
        out += utils::to_string(action.first);
        out += " " + action.second;
    }
    return out;
}
