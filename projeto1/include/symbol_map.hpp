#ifndef SYMBOL_MAP_HPP
#define SYMBOL_MAP_HPP

#include <string>
#include <unordered_map>
#include "Types.hpp"

class symbol_map {
public:
    void declare(const std::string&, const Type&);

private:
    std::unordered_map<std::string, Type> vars;
};

#endif /* SYMBOL_MAP_HPP */
