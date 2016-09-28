
template<typename... Params>
bool SymbolMap::declare_function(Type type, const std::string& name, Params&&... params) {
    static constexpr auto size = sizeof...(params);
    auto funct = Function<size>();
    funct.name = name;
    funct.type = type;
    funct.params = {{params.type...}};
}

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
    scope.insert(symbol);
    return true;
}
