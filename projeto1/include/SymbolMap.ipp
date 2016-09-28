
template<typename T>
bool SymbolMap::declare(Type type, const std::string& name, const T& value) {
    auto& scope = scopes.back();
    if (scope.count(name)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    if (!utils::type_matches(type, value.type())) {
    	utils::semantic_error<Error::INCOMPATIBLE_ASSIGNMENT>(type, value.type());
    	return false;
    }
    scope[name] = type;
    return true;
}
