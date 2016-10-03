#include "Action.hpp"

Reference::Reference(Action* lvalue)
 : t(lvalue->type()), lvalue(lvalue), fail(lvalue->error()) {
    if (!t.ptr_count) {
        fail = true;
        utils::semantic_error<Error::NOT_A_POINTER>();
        return;
    }
    --t.ptr_count;
}

std::string Reference::to_string(unsigned) const {
    std::string out;
    if (!error()) {
        out = "[ref] ";
        out += lvalue->to_string();
    }
    return out;
}
