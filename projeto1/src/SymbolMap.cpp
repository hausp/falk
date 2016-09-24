
#include "SymbolMap.hpp"
#include "macros.hpp"

SymbolMap& SymbolMap::instance() {
    static SymbolMap inst;
    return inst;
}

bool SymbolMap::declare(Type type, const std::string& name, size_t line) {
    if (symbols.count(name)) {
        // TODO
        utils::semantic_error<Error::MULTIPLE_DEFINITION>(line, name);
        return false;
    }
    symbols[name] = type;
    return true;
}

// void SymbolMap::retrieve(Type type, const std::string& name, size_t line) const {
//     if (symbols.count(name)) {
//         // TODO
//         // ECHO("Achei o " + name);
//         // auto node = new stx::Node();
//         // node->set_content(name);
//         // return node;
//     } else {
//         // TODO
//         utils::semantic_error<Error::UNDECLARED_VARIABLE>(line, name);
//         // return nullptr;
//     }
// }

bool SymbolMap::var_exists(const std::string& name) const {
    return symbols.count(name);
}
