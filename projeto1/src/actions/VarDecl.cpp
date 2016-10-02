#include "Action.hpp"

VarDecl::VarDecl(Type t, const std::string& name, Action* value)
: t(t), name(name), value(value) { }

std::string VarDecl::to_string(unsigned) const {
    std::string out = name;
    if (value) {
        out += " = " + value->to_string();
    }
    return out;
}
