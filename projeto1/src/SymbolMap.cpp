
#include "SymbolMap.hpp"
#include "macros.hpp"

SymbolMap& SymbolMap::instance() {
    static auto defined = false;
    static SymbolMap inst;
    if (!defined) {
        inst.open_scope();
        defined = true;
    }
    return inst;
}

bool SymbolMap::declare(Type type, const std::string& name) {
    auto& scope = scopes.back();
    if (scope.count(name)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    scope[name] = type;
    return true;
}

bool SymbolMap::var_exists(const std::string& name) const {
    for (auto& scope : scopes) {
        if (scope.count(name)) {
            return true;
        }
    }
    return false;
}

Type SymbolMap::typeof(const std::string& name) const {
    for (auto& scope : scopes) {
        if (scope.count(name)) {
            return scope.at(name);
        }
    }
    return Type::VOID;    
}

void SymbolMap::open_scope() {
    scopes.emplace_back();
}

void SymbolMap::close_scope() {
    scopes.pop_back();
}