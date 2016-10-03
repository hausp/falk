
// template<typename... Params>
// bool SymbolMap::declare_function(Type type, const std::string& name, Params&&... params) {
//     static constexpr auto size = sizeof...(params);
//     auto funct = Function<size>();
//     funct.name = name;
//     funct.type = type;
//     funct.params = {{params.type...}};
// }
#include "macros.hpp"

template<typename T>
bool SymbolMap::declare(Type type, const std::string& name, const T& value) {
    auto& scope = scopes.back();
    auto symbol = Symbol{name, type};
    if (scope.count(symbol)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    if (!utils::type_matches(type, value.type())) {
    	utils::semantic_error<Error::INCOMPATIBLE_ASSIGNMENT>(type, value.type());
    	return false;
    }
    scope.vars.insert(symbol);
    return true;
}

inline bool SymbolMap::is_array(const std::string& name) const {
    for (auto& scope : scopes) {
        if (scope.arrays.count(Array(name, Type::ANY))) {
            return true;
        }
    }
    return false;
}

inline bool SymbolMap::is_function(const std::string& name) const {
    for (auto& scope : scopes) {
        if (scope.functions.count(Array(name, Type::ANY))) {
            return true;
        }
    }
    return false;
}

inline bool SymbolMap::is_variable(const std::string& name) const {
    for (auto& scope : scopes) {
        if (scope.vars.count(Array(name, Type::ANY))) {
            return true;
        }
    }
    return false;
}
