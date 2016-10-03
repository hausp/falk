
#include "Action.hpp"
#include "SymbolMap.hpp"
#include "macros.hpp"

namespace {
    bool is_equal(const Function& f1, const Function& f2) {
        auto equal = f1 == f2 && f1.type == f2.type;
        if (equal) {
            auto f1_begin = f1.params.begin();
            auto f1_end = f1.params.end();
            auto f2_begin = f2.params.begin();
            auto f2_end = f2.params.end();
            
            return std::equal(f1_begin, f1_end, f2_begin, f2_end);
        }
        return false;
    }
}

size_t SymbolMap::Scope::count(const Symbol& sym) const {
    return vars.count(sym) + functions.count(sym) + arrays.count(sym);
}

SymbolMap& SymbolMap::instance() {
    static SymbolMap inst;
    return inst;
}

bool SymbolMap::declare(Type type, const std::string& name) {
    auto& scope = scopes.back();
    auto symbol = Symbol{name, type};
    if (scope.count(symbol)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    scope.vars.insert(symbol);
    return true;
}

bool SymbolMap::declare_array(Type type,
                        const std::string& name,
                        const std::string& size) {
    auto& scope = scopes.back();
    auto array = Array(name, type, size);
    if (scope.count(array)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    scope.arrays.insert(array);
    return true;
}

bool SymbolMap::exists(const std::string& name) const {
    for (auto& scope : scopes) {
        if (scope.count({name, Type::ANY})) {
            return true;
        }
    }
    return false;
}

Type SymbolMap::typeof(const std::string& name) const {
    for (auto& scope : scopes) {
        auto symbol = Symbol{name, Type::ANY};
        if (scope.vars.count(symbol)) {
            return scope.vars.find(symbol)->type;
        } else if (scope.functions.count(symbol)) {
            return scope.functions.find(symbol)->type;
        } else if (scope.arrays.count(symbol)) {
            return scope.arrays.find(symbol)->type;
        }
    }
    return Type::VOID;
}

std::list<Symbol> SymbolMap::params(const std::string& name) const {
    for (auto& scope : scopes) {
        auto fn_it = scope.functions.find({name, Type::ANY});
        if (fn_it != scope.functions.end()) {
            return fn_it->params;
        }
    }
    return std::list<Symbol>();
}

void SymbolMap::open_scope() {
    scopes.emplace_back();
}

void SymbolMap::close_scope() {
    auto& scope = scopes.back();
    auto& functions = scope.functions;
    for (auto& fn : functions) {
        if (!fn.defined) {
            utils::semantic_error<Error::DECLARED_BUT_NEVER_DEFINED>(fn.name);
        }
    }
    scopes.pop_back();
}

bool SymbolMap::declare_function(Type type,
                                 const std::string& name,
                                 ParamList* params) {
    auto& scope = scopes.back();
    if (!scope.count({name, Type::ANY})) {
        auto funct = Function(name, type);
        for (auto& pair : *params) {
            funct.params.push_back({pair.second, pair.first});
        }
        scope.functions.insert(funct);
        return true;
    }
    utils::semantic_error<Error::MULTIPLE_DEFINITION_FN>(name);
    return false;
}

bool SymbolMap::define_function(Type type,
                                const std::string& name,
                                ParamList* params) {
    auto& scope = scopes.back();
    auto it = scope.functions.find({name, Type::ANY});
    auto funct = Function(name, type);
    for (auto& pair : *params) {
        funct.params.push_back({pair.second, pair.first});
    }

    if (it == scope.functions.end()) {
        funct.defined = true;
        scope.functions.insert(funct);
        return true;
    }

    bool ok = is_equal(*it, funct) && !it->defined;
    if (ok) {
        it->defined = true;
    } else {
        utils::semantic_error<Error::MULTIPLE_DEFINITION_FN>(name);
    }
    return ok;
}