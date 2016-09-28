#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <list>
#include <string>
#include <unordered_set>
#include "utils.hpp"

struct Symbol {
    std::string name;
    Type type;

};

inline bool operator==(const Symbol& lhs, const Symbol& rhs) {
    return lhs.name == rhs.name;
}

namespace std {
    template<>
    struct hash<Symbol> {
        inline auto operator()(Symbol symbol) const {
            static constexpr auto secret_hash = hash<string>();
            return secret_hash(symbol.name);
        }
    };
}

class SymbolMap {
    using Table = std::unordered_set<Symbol>;
public:
    static SymbolMap& instance();

    template<typename... Params>
    bool declare_function(Type, const std::string&, Params&&...);
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

template<size_t S>
struct Function : public Symbol {
    std::array<Symbol, S> params;
};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
