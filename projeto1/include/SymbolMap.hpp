/* Copyright 2016 Marleson Graf <aszdrick@gmail.com>
   Ghabriel Nunes <ghabriel.nunes@gmail.com> 
   Vinicius Marino Calvo Torres de Freitas <vinimmbb@gmail.com> */

/* 
 * Symbol related definitions
 *      This file defines structs to contain logical information about
 * declared symbols like variables, arrays and functions.
 *      The SymbolMap class acts as the symbols table of the compiler,
 * keeping track of declared symbols and notifying errors when redeclarations
 * are attempted.
 *      To achieve multiple scopes, it mantains a list of tables, each one
 * referencing a different scope. When a scope is opened, it creates a new table
 * on the back of the list, allowing redeclaration of symbols, since it
 * only considers the last scope when declaring symbols.
 *      On other hand, to verify the existence of a symbol, it iterates
 * over all scopes, stopping as soon as find the requested indentifier.
 * This way, a reference to a symbol will always match the declaration made
 * on the closest scope to the current one.
 *      The SymbolMap also allows to retrieve the type of a declared symbol,
 * as well verify if it is a variable, array or function. 
 */

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
     Function(const Symbol& sym) : Symbol(sym) { }
    std::list<Symbol> params;
    mutable bool defined = false;
};

struct Array : public Symbol {
    Array(const std::string& name, Type type, const std::string& size = "0")
     : Symbol{name, type}, size(size) { }
    Array(const Symbol& sym) : Symbol(sym) { }
     std::string size;
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

    template<>
    struct hash<Array> {
        inline auto operator()(Array arr) const {
            return hash<Symbol>()(arr);
        }
    };
}

class SymbolMap {
    struct Scope {
        std::unordered_set<Symbol> vars;
        std::unordered_set<Function> functions;
        std::unordered_set<Array> arrays;
        size_t count(const Symbol&) const;
    };
public:
    static SymbolMap& instance();

    bool declare_function(Type, const std::string&, ParamList*);
    bool define_function(Type, const std::string&, ParamList*);
    bool declare_array(Type, const std::string&, const std::string&);
    template<typename T>
    bool declare(Type, const std::string&, const T&);
    bool declare(Type, const std::string&);
    bool exists(const std::string&) const;
    bool is_array(const std::string&) const;
    bool is_function(const std::string&) const;
    bool is_variable(const std::string&) const;
    Type typeof(const std::string&) const;
    std::list<Symbol> params(const std::string&) const;
    void open_scope();
    void close_scope();
    Type last_fun_type() const;

private:
    std::list<Scope> scopes;
    SymbolMap() = default;

};

#include "SymbolMap.ipp"

#endif /* SYMBOL_MAP_HPP */
