
#include "ev/symbol_mapper.hpp"

namespace {
    auto invalid_function = falk::ev::function(true);
    auto invalid_variable = falk::ev::variable(true);
}

falk::ev::symbol_mapper::symbol_mapper() {
    auto scp = scope{};
    scp.symbol_table["res"] = symbol::type::VARIABLE;
    scp.variables["res"] = variable();
    scopes.emplace_front(std::move(scp));
}

void falk::ev::symbol_mapper::update_result(variable var) {
    auto& scope = scopes.back();
    scope.variables["res"] = std::move(var);
}

void falk::ev::symbol_mapper::declare_function(const std::string& id,
                                               function fn) {
    auto& scope = scopes.front();
    if (!scope.symbol_table.count(id)) {
        scope.symbol_table[id] = symbol::type::FUNCTION;
        scope.functions[id] = std::move(fn);
    } else {
        err::semantic<Error::REDECLARATION_OF_SYMBOL>(id);
    }
}

void falk::ev::symbol_mapper::declare_variable(const std::string& id,
                                               variable var) {
    auto& scope = scopes.front();
    if (!scope.symbol_table.count(id)) {
        scope.symbol_table[id] = symbol::type::VARIABLE;
        scope.variables[id] = std::move(var);
    } else {
        err::semantic<Error::REDECLARATION_OF_SYMBOL>(id);
    }
}


falk::ev::function&
falk::ev::symbol_mapper::retrieve_function(const std::string& id) {
    if (is_declared(id)) {
        auto& scope = scope_of(id);
        if (scope.symbol_table.at(id) == symbol::type::FUNCTION) {
            return scope.functions.at(id);
        } else {
            err::semantic<Error::NOT_A_FUNCTION>(id);
            return invalid_function;
            // TODO: return what?
        }
    } else {
        err::semantic<Error::UNDECLARED_FUNCTION>(id);
        return invalid_function;
        // TODO: return what?
    }
}

falk::ev::variable&
falk::ev::symbol_mapper::retrieve_variable(const std::string& id) {
    if (is_declared(id)) {
        auto& scope = scope_of(id);
        if (scope.symbol_table.at(id) == symbol::type::VARIABLE) {
            return scope.variables.at(id);
        } else {
            err::semantic<Error::NOT_A_VARIABLE>(id);
            return invalid_variable;
            // TODO: return what?
        }
    } else {
        err::semantic<Error::UNDECLARED_VARIABLE>(id);
        return invalid_variable;
        // TODO: return what?
    }
}

void falk::ev::symbol_mapper::open_scope() {
    scopes.emplace_front();
}

void falk::ev::symbol_mapper::close_scope() {
    scopes.pop_front();
}

bool falk::ev::symbol_mapper::is_declared(const std::string& id) const {
    for (auto& scope : scopes) {
        if (scope.symbol_table.count(id)) {
            return true;
        }
    }
    return false;
}

scope& falk::ev::symbol_mapper::scope_of(const std::string& id) {
    for (auto& scope : scopes) {
        if (scope.symbol_table.count(id)) {
            return scope;
        }
    }
    // TODO: return what?
    throw -1; // Hu3
}

falk::symbol::type
falk::ev::symbol_mapper::type_of(const std::string& id) const {
    for (auto& scope : scopes) {
        if (scope.symbol_table.count(id)) {
            return scope.symbol_table.at(id);
        }
    }
    return symbol::type::UNDECLARED;
}