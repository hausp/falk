
template<typename T>
stx::Node* SymbolMap::declare(const std::string& name, const T& value, size_t line) {
    // TODO: check if value matches with type
    auto node = new stx::Node();
    node->set_content(name);

    if (symbols.count(name)) {
        // TODO: return what?
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(line, name);
        throw utils::error();
    }
    symbols[name] = last_type;
    
    return node;
}
