#include "Action.hpp"

Address::Address(Action* lvalue)
 : t(lvalue->type()), lvalue(lvalue), fail(lvalue->error()) {
    ++t.ptr_count;
}

std::string Address::to_string(unsigned) const {
    std::string out;
    if (!error()) {
        out += "[addr] ";
        out += lvalue->to_string();
    }
    return out;
}
