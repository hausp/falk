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
};

struct Function : public Symbol {
    Function(const std::string& name, Type type)
     : Symbol{name, type} { }
    std::list<Symbol> params;
    mutable bool defined = false;
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

    template<>
    struct hash<Function> {
        inline auto operator()(Function fn) const {
            return hash<Symbol>()(fn);
        }
    };
}

class SymbolMap {
    struct Table {
        std::unordered_set<Symbol> vars;
        std::unordered_set<Function> functions;
        size_t count(const Symbol&) const;
    };
public:
    static SymbolMap& instance();

    bool declare_function(Type, const std::string&, ParamList*);
    bool define_function(Type, const std::string&, ParamList*);
    template<typename T>
    bool declare(Type, const std::string&, const T&);
    bool declare(Type, const std::string&);
    bool exists(const std::string&) const;
    Type typeof(const std::string&) const;
    std::list<Symbol> params(const std::string&) const;
    void open_scope();
    void close_scope();
    Type last_fun_type() const;

private:
    std::list<Table> scopes;
    SymbolMap() = default;

};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
