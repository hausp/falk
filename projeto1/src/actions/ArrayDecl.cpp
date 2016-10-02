#include "Action.hpp"

ArrayDecl::ArrayDecl(Type t, const std::string& name, const std::string& size)
: t(t), name(name), size(size) { }

std::string ArrayDecl::to_string(unsigned) const {
    std::string out = name;
    out += " (size: " + size + ")";
    return out;
}
