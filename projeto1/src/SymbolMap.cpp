
#include "SymbolMap.hpp"
#include "macros.hpp"

SymbolMap& SymbolMap::instance() {
    static SymbolMap inst;
    return inst;
}

bool SymbolMap::declare(Type type, const std::string& name) {
    if (symbols.count(name)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    symbols[name] = type;
    return true;
}

bool SymbolMap::var_exists(const std::string& name) const {
    return symbols.count(name);
}

Type SymbolMap::typeof(const std::string& name) const {
    return symbols.at(name);
}
