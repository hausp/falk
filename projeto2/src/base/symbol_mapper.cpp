
#include "base/symbol_mapper.hpp"

namespace {
    auto invalid_function = falk::function(true);
    auto invalid_variable = falk::variable(true);
}

falk::symbol_mapper::symbol_mapper() {
    auto scp = scope{};
    scp.symbol_table["res"] = symbol::type::VARIABLE;
    scp.variables["res"] = variable();
    scopes.emplace_front(std::move(scp));
}

void falk::symbol_mapper::update_result(variable var) {
    auto& scope = scopes.back();
    scope.variables["res"] = std::move(var);
}

void falk::symbol_mapper::declare_function(const std::string& id,
                                               function fn) {
    auto& scope = scopes.front();
    if (!scope.symbol_table.count(id)) {
        scope.symbol_table[id] = symbol::type::FUNCTION;
        scope.functions[id] = std::move(fn);
    } else {
        err::semantic<Error::REDECLARATION_OF_SYMBOL>(id);
    }
}

void falk::symbol_mapper::declare_variable(const std::string& id,
                                               variable var) {
    auto& scope = scopes.front();
    if (!scope.symbol_table.count(id)) {
        scope.symbol_table[id] = symbol::type::VARIABLE;
        scope.variables[id] = std::move(var);
    } else {
        err::semantic<Error::REDECLARATION_OF_SYMBOL>(id);
    }
}

void falk::symbol_mapper::undefine_function(const std::string& id) {
    if (is_declared(id)) {
        auto& scope = scope_of(id);
        if (scope.symbol_table.at(id) == symbol::type::FUNCTION) {
            scope.symbol_table.erase(id);
        } else {
            err::semantic<Error::NOT_A_FUNCTION>(id);
        }
    } else {
        err::semantic<Error::UNDECLARED_FUNCTION>(id);
    }
}

falk::function&
falk::symbol_mapper::retrieve_function(const std::string& id) {
    if (is_declared(id)) {
        auto& scope = scope_of(id);
        if (scope.symbol_table.at(id) == symbol::type::FUNCTION) {
            return scope.functions.at(id);
        } else {
            err::semantic<Error::NOT_A_FUNCTION>(id);
            return invalid_function;
        }
    } else {
        err::semantic<Error::UNDECLARED_FUNCTION>(id);
        return invalid_function;
    }
}

falk::variable&
falk::symbol_mapper::retrieve_variable(const std::string& id) {
    if (is_declared(id)) {
        auto& scope = scope_of(id);
        if (scope.symbol_table.at(id) == symbol::type::VARIABLE) {
            return scope.variables.at(id);
        } else {
            err::semantic<Error::NOT_A_VARIABLE>(id);
            return invalid_variable;
        }
    } else {
        err::semantic<Error::UNDECLARED_VARIABLE>(id);
        return invalid_variable;
    }
}

void falk::symbol_mapper::open_scope() {
    scopes.emplace_front();
}

void falk::symbol_mapper::close_scope() {
    scopes.pop_front();
}

bool falk::symbol_mapper::is_declared(const std::string& id) const {
    for (auto& scope : scopes) {
        if (scope.symbol_table.count(id)) {
            return true;
        }
    }
    return false;
}

scope& falk::symbol_mapper::scope_of(const std::string& id) {
    for (auto& scope : scopes) {
        if (scope.symbol_table.count(id)) {
            return scope;
        }
    }
    // TODO: return what?
    throw -1; // Hu3
}

falk::symbol::type
falk::symbol_mapper::type_of(const std::string& id) const {
    for (auto& scope : scopes) {
        if (scope.symbol_table.count(id)) {
            return scope.symbol_table.at(id);
        }
    }
    return symbol::type::UNDECLARED;
}