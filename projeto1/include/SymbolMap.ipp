
template<typename T>
bool SymbolMap::declare(Type type, const std::string& name, const T& value, size_t line) {
    // TODO: check if value matches with type
    if (symbols.count(name)) {
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(line, name);
        return false;
    }
    symbols[name] = type;
    return true;
}
