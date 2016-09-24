#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <string>
#include <unordered_map>
#include "utils.hpp"

class SymbolMap {
public:
    static SymbolMap& instance();

    template<typename T>
    bool declare(Type, const std::string&, const T&);
    bool declare(Type, const std::string&);
    bool var_exists(const std::string&) const;
    Type typeof(const std::string&) const;

private:
    std::unordered_map<std::string, Type> symbols;
    SymbolMap() = default;
};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
