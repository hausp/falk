
template<typename T>
stx::Node* SymbolMap::declare(const std::string& name, const T& value) {
    // TODO: check if value matches with type
    auto node = new stx::Node();
    node->set_content(name);

    if (symbols.count(name)) {
        // TODO: return what?
        return nullptr;
    }
    symbols[name] = last_type;
    
    return node;
}
