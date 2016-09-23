#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <string>
#include <unordered_map>
#include "SyntaxTree.hpp"
#include "utils.hpp"

class SymbolMap {
public:
    template<typename T>
    stx::Node* declare(const std::string&, const T&, size_t);
    // TODO: improve this solution
    stx::Node* declare(const std::string&, size_t);
    stx::Node* retrieve(const std::string&, size_t) const;
    stx::Node* make_declaration(Type);

private:
    std::unordered_map<std::string, Type> symbols;
    Type last_type;
};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
