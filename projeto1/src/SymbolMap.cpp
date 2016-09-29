
#include "Action.hpp"
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
    auto symbol = Symbol{name, type};
    if (scope.count(symbol)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    scope.insert(symbol);
    return true;
}

bool SymbolMap::var_exists(const std::string& name) const {
    for (auto& scope : scopes) {
        if (scope.count({name, Type::ANY})) {
            return true;
        }
    }
    return false;
}

Type SymbolMap::typeof(const std::string& name) const {
    for (auto& scope : scopes) {
        auto it = scope.find({name, Type::ANY});
        if (it != scope.end()) {
            return it->type;
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

bool SymbolMap::declare_function(Type type,
                                 const std::string& name,
                                 ParamList* params) {
    return true;
}

bool SymbolMap::define_function(Type type,
                                const std::string& name,
                                ParamList* params,
                                Action* body) {
    return true;
}