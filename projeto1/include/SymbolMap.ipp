
template<typename T>
bool SymbolMap::declare(Type type, const std::string& name, const T& value) {
    // TODO: check if value matches with type
    if (symbols.count(name)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(name);
        return false;
    }
    symbols[name] = type;
    return true;
}
