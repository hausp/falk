
#include "SymbolMap.hpp"

stx::Node* SymbolMap::make_declaration(Type type) {
    last_type = type;
    auto node = new stx::Node(std::make_unique<stx::PreOrderTraversal>());
    auto content = utils::to_string(type);
    content += " var: ";
    node->set_content(content);
    return node;
}

stx::Node* SymbolMap::retrive(const std::string& name) const {
    if (symbols.count(name)) {
        auto node = new stx::Node();
        node->set_content(name);
        return node;
    } else {
        // TODO: use of undeclared variable
        return nullptr;
    }
}

stx::Node* SymbolMap::declare(const std::string& name) {
    auto node = new stx::Node();
    node->set_content(name);

    if (symbols.count(name)) {
        // TODO: return what?
        return nullptr;
    }
    symbols[name] = last_type;
    
    return node;
}
