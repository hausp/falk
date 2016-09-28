#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <list>
#include <string>
#include <unordered_map>
#include "utils.hpp"

class SymbolMap {
    using Table = std::unordered_map<std::string, Type>;
public:
    static SymbolMap& instance();

    template<typename T>
    bool declare(Type, const std::string&, const T&);
    bool declare(Type, const std::string&);
    bool var_exists(const std::string&) const;
    Type typeof(const std::string&) const;
    void open_scope();
    void close_scope();

private:
    std::list<Table> scopes;
    SymbolMap() = default;

};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
