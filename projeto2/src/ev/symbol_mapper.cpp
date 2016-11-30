
#include "ev/symbol_mapper.hpp"

falk::ev::symbol_mapper::symbol_mapper() {
    scopes.emplace();
}

void falk::ev::symbol_mapper::declare_function(const std::string& id,
                                               function fn) {
    if (!symbol_table.count(id)) {
        symbol_table[id] = symbol::type::FUNCTION;
        auto& scope = scopes.top();
        scope.functions[id] = std::move(fn);
    } else {
        // TODO: error: redeclaration of symbol
    }
}

void falk::ev::symbol_mapper::declare_variable(const std::string& id,
                                               variable var) {
    if (!symbol_table.count(id)) {
        symbol_table[id] = symbol::type::VARIABLE;
        auto& scope = scopes.top();
        scope.variables[id] = std::move(var);
    } else {
        // TODO: error: redeclaration of symbol
    }
}
