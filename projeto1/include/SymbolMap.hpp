#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <list>
#include <stack>
#include <string>
#include <unordered_set>
#include "utils.hpp"

class ParamList;
class Action;

struct Symbol {
    std::string name;
    Type type;
    bool is_fun;
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

    bool declare_function(Type, const std::string&, ParamList*);
    bool define_function(Type, const std::string&, ParamList*, Action*);
    template<typename T>
    bool declare(Type, const std::string&, const T&);
    bool declare(Type, const std::string&);
    bool var_exists(const std::string&) const;
    Type typeof(const std::string&) const;
    void open_scope();
    void close_scope();
    Type last_fun_type() const;

private:
    std::list<Table> scopes;
    std::stack<Type> fun_types;
    SymbolMap() = default;

};

struct Function : public Symbol {
    std::list<Symbol> params;
    bool defined = false;
};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
