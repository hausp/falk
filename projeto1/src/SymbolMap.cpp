
#include "SymbolMap.hpp"
#include "macros.hpp"

stx::Node* SymbolMap::make_declaration(Type type) {
    last_type = type;
    auto node = new stx::Node(stx::Node::PRE_ORDER);
    auto content = utils::to_string(type);
    content += "var:";
    node->set_content(content);
    return node;
}

stx::Node* SymbolMap::retrieve(const std::string& name) const {
    for (auto& s : symbols) {
        TRACE(s.first);
    }
    TRACE(symbols.size());
    if (symbols.count(name)) {
        ECHO("Achei o " + name);
        auto node = new stx::Node();
        node->set_content(name);
        return node;
    } else {
        // TODO: use of undeclared variable
        ECHO("Não achei o " + name);
        utils::semantic_error<Error::UNDECLARED_VARIABLE>(0, name);
        return nullptr;
    }
}

stx::Node* SymbolMap::declare(const std::string& name) {
    auto node = new stx::Node();
    node->set_content(name);

    if (symbols.count(name)) {
        // TODO: return what?
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(0, name);
        return nullptr;
    }
    symbols[name] = last_type;
    
    return node;
}
