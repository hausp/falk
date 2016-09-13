#include "symbol_map.hpp"

void symbol_map::declare(const std::string& name, const Type& type) {
	vars[name] = type;
}
