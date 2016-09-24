#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <string>
#include <unordered_map>
#include "utils.hpp"

class SymbolMap {
public:
    template<typename T>
    bool declare(Type, const std::string&, const T&, size_t);
    bool declare(Type, const std::string&, size_t);
    void retrieve(Type, const std::string&, size_t) const;
    void make_declaration(Type);

private:
    std::unordered_map<std::string, Type> symbols;
};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
