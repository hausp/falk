
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

// auto SymbolMap::Table::find(const Symbol& sym) {
//     auto it = vars.find(sym);
//     if (it != vars.end()) return it;
//     it = functions.find(sym);
//     return it;
// }

// auto SymbolMap::Table::insert(const Symbol& sym) {
//     if (!functions.count(sym)) {
//         return vars.insert(sym);
//     }
//     return functions.insert(sym);
// }

// auto SymbolMap::Table::insert(const Function& fun) {
//     if (!vars.count(fun)) {
//         return functions.insert(fun);
//     }
//     return vars.insert(fun);
// }

size_t SymbolMap::Table::count(const Symbol& sym) const {
    auto funct = Function(sym.name, sym.type);
    return vars.count(sym) + functions.count(funct);
}

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
    scope.vars.insert(symbol);
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
        auto var_it = scope.vars.find({name, Type::ANY});
        if (var_it != scope.vars.end()) {
            return var_it->type;
        }
        auto fn_it = scope.functions.find({name, Type::ANY});
        if (fn_it != scope.functions.end()) {
            return fn_it->type;
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
    auto& scope = scopes.back();
    if (!scope.count({name, Type::ANY})) {
        auto funct = Function(name, type);
        for (auto& pair : *params) {
            funct.params.push_back({pair.second, pair.first});
        }
        scope.functions.insert(funct);
        return true;
    }
    return false;
}

bool SymbolMap::define_function(Type type,
                                const std::string& name,
                                ParamList* params,Action*) {
    auto& scope = scopes.back();
    auto it = scope.functions.find({name, Type::ANY});
    auto funct = Function(name, type);
    if (it == scope.functions.end()) {
        for (auto& pair : *params) {
            funct.params.push_back({pair.second, pair.first});
        }
        return true;
    }

    return is_equal(*it, funct) && !it->defined;
}