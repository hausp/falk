#include "Action.hpp"

ArrayIndex::ArrayIndex(const std::string& name, Action* i)
 : t(symbols.typeof(name)), name(name), index(i), fail(i->error()) {
    if (!symbols.is_array(name)) {
        fail = true;
        utils::semantic_error<Error::NON_ARRAY_INDEX>();
    }

    if (i->type() != Type::INT) {
        fail = true;
        utils::semantic_error<Error::INCOMPATIBLE_INDEX>(Type::INT, i->type());
    }
}

std::string ArrayIndex::to_string(unsigned indent) const {
    auto out = std::string(indent, ' ');
    out += "[index] ";
    out += name;
    out += " " + index->to_string();
    return out;
}

