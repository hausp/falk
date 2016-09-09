#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <string>
#include <unordered_map>

enum class Type {
    INT
};

template<Type type>
struct todo_impl;

template<>
struct todo_impl<Type::INT> {
    using type = int;
}

template<Type type>
using todo = typename todo_impl<type>::type;

template<Type type>
struct variable {
    todo<type> value;
    bool already_defined = false;
};

class symbol_map {
public:
    template<Type type>
    void declare(const std::string&);
    template<Type type>
    void assign(const std::string&, const todo<type>&);
private:
    std::unordered_map<std::string, std::pair<Type, unsigned>> vars;
    std::unordered_map<unsigned, variable<Type::INT>> int_vars;

    template<Type type>
    variable<type>& todo(const std::string& name);
};

#include "symbol_map.ipp"

#endif
