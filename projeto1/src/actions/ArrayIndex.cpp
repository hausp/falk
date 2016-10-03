#include "Action.hpp"

ArrayIndex::ArrayIndex(const std::string& name, Action* i)
 : t(symbols.typeof(name)), name(name), index(i), fail(i->error()) {
    if (!symbols.is_array(name)) {
        fail = true;
        // TODO: print error
    }

    if (i->type() != Type::INT) {
        fail = true;
        // TODO: print error (expected integer)
    }
}

std::string ArrayIndex::to_string(unsigned indent) const {
    auto out = std::string(indent, ' ');
    out += "[index] ";
    out += name;
    out += " " + index->to_string();
    return out;
}

